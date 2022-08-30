/* -*- c -*- */

/* Copyright (C) 2014-2021 Alexander Chernov <cher@ejudge.ru> */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "ejudge/http_request.h"
#include "ejudge/contests.h"
#include "ejudge/l10n.h"
#include "ejudge/cJSON.h"

#include "ejudge/logger.h"

#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <libintl.h>

static const unsigned char * const *symbolic_action_table;
static const unsigned char * const *submit_button_labels;
static const unsigned char * const *help_urls;
static int symbolic_action_table_size;

const unsigned char*
hr_getenv(
        const struct http_request_info *phr,
        const unsigned char *var)
{
  int i;
  size_t var_len;

  if (!var) return 0;
  var_len = strlen(var);
  for (i = 0; i < phr->env_num; i++)
    if (!strncmp(phr->envs[i], var, var_len) && phr->envs[i][var_len] == '=')
      break;
  if (i < phr->env_num)
    return phr->envs[i] + var_len + 1;
  return 0;
}

int
hr_cgi_param(
        const struct http_request_info *phr,
        const unsigned char *param,
        const unsigned char **p_value)
{
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, param);
        if (jj) {
            if (jj->type == cJSON_NULL) {
                if (p_value) *p_value = NULL;
                return 1;
            } else if (jj->type == cJSON_String) {
                if (p_value) *p_value = jj->valuestring;
                return 1;
            } else {
                return -1;
            }
        } else {
            return 0;
        }
    } else {
        int i;

        if (!param) return -1;
        for (i = 0; i < phr->param_num; i++)
            if (!strcmp(phr->param_names[i], param))
                break;
        if (i >= phr->param_num) return 0;
        if (strlen(phr->params[i]) != phr->param_sizes[i]) return -1;
        *p_value = phr->params[i];
        return 1;
    }
}

int
hr_cgi_param_bin(
        const struct http_request_info *phr,
        const unsigned char *param,
        const unsigned char **p_value,
        size_t *p_size)
{
  int i;

  if (!param) return -1;
  for (i = 0; i < phr->param_num; i++)
    if (!strcmp(phr->param_names[i], param))
      break;
  if (i >= phr->param_num) return 0;
  *p_value = phr->params[i];
  *p_size = phr->param_sizes[i];
  return 1;
}

const unsigned char *
hr_cgi_nname(
        const struct http_request_info *phr,
        const unsigned char *prefix,
        size_t pflen)
{
  int i;

  if (!prefix || !pflen) return 0;
  for (i = 0; i < phr->param_num; i++)
    if (!strncmp(phr->param_names[i], prefix, pflen))
      return phr->param_names[i];
  return 0;
}

static int
json_to_int(cJSON *jj, int *p_val, int retval)
{
    if (jj->type == cJSON_False) {
        if (p_val) *p_val = 0;
        return retval;
    } else if (jj->type == cJSON_True) {
        if (p_val) *p_val = 1;
        return retval;
    } else if (jj->type == cJSON_NULL) {
        if (p_val) *p_val = 0;
        return 0;
    } else if (jj->type == cJSON_Number) {
        if (jj->valueint != jj->valuedouble) return -1;
        if (p_val) *p_val = jj->valueint;
        return retval;
    } else if (jj->type == cJSON_String) {
        const char *s = jj->valuestring;
        char *eptr = NULL;
        errno = 0;
        long x = strtol(s, &eptr, 10);
        if (errno || eptr == s || *eptr || (int) x != x) return -1;
        if (p_val) *p_val = x;
        return retval;
    } else {
        // invalid value
        return -1;
    }
}

int
hr_cgi_param_int(
        const struct http_request_info *phr,
        const unsigned char *name,
        int *p_val)
{
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, name);
        if (jj) {
            return json_to_int(jj, p_val, 0);
        } else {
            return -1;
        }
    } else {
        const unsigned char *s = 0, *p = 0;
        char *eptr = 0;
        int x;

        if (hr_cgi_param(phr, name, &s) <= 0) return -1;

        p = s;
        while (*p && isspace(*p)) p++;
        if (!*p) return -1;

        errno = 0;
        x = strtol(s, &eptr, 10);
        if (errno || *eptr) return -1;
        if (p_val) *p_val = x;
        return 0;
    }
}

/* returns -1 if invalid param, 0 if no param, 1 if ok */
int
hr_cgi_param_int_2(
        const struct http_request_info *phr,
        const unsigned char *name,
        int *p_val)
{
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, name);
        if (jj) {
            return json_to_int(jj, p_val, 1);
        } else {
            return 0;
        }
    } else {
        const unsigned char *s = 0, *p = 0;
        char *eptr = 0;
        int x, r;

        if ((r = hr_cgi_param(phr, name, &s)) <= 0) return r;

        p = s;
        while (*p && isspace(*p)) p++;
        if (!*p) return 0;

        errno = 0;
        x = strtol(s, &eptr, 10);
        if (errno || *eptr) return -1;
        if (p_val) *p_val = x;
        return 1;
    }
}

int
hr_cgi_param_int_opt(
        struct http_request_info *phr,
        const unsigned char *name,
        int *p_val,
        int default_value)
{
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, name);
        if (jj) {
            return json_to_int(jj, p_val, 0);
        } else {
            if (p_val) *p_val = default_value;
            return 0;
        }
    } else {
        const unsigned char *s = 0, *p;
        char *eptr = 0;
        int x;

        if (!(x = hr_cgi_param(phr, name, &s))) {
            if (p_val) *p_val = default_value;
            return 0;
        } else if (x < 0) return -1;
        p = s;
        while (*p && isspace(*p)) p++;
        if (!*p) {
            if (p_val) *p_val = default_value;
            return 0;
        }
        errno = 0;
        x = strtol(s, &eptr, 10);
        if (errno || *eptr) return -1;
        if (p_val) *p_val = x;
        return 0;
    }
}

int
hr_cgi_param_bool_opt(
        struct http_request_info *phr,
        const unsigned char *name,
        int *p_val,
        int default_value)
{
    int ret = hr_cgi_param_int_opt(phr, name, p_val, default_value);
    if (p_val) {
        if (*p_val != 1) *p_val = 0;
    }
    return ret;
}

int
hr_cgi_param_jsbool_opt(
        struct http_request_info *phr,
        const unsigned char *name,
        int *p_val,
        int default_value)
{
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, name);
        if (jj) {
            if (jj->type == cJSON_True) {
                if (p_val) *p_val = 1;
                return 1;
            } else if (jj->type == cJSON_False) {
                if (p_val) *p_val = 0;
                return 1;
            } else {
                return -1;
            }
        } else {
            if (p_val) *p_val = default_value;
            return 0;
        }
    } else {
        const unsigned char *s;
        int x;
        long v;
        char *eptr = NULL;

        x = hr_cgi_param(phr, name, &s);
        if (x < 0) {
            return -1;
        }
        if (!x) {
            if (p_val) *p_val = default_value;
            return 0;
        }
        if (!s || !*s) {
            if (p_val) *p_val = default_value;
            return 0;
        }
        if (!strcasecmp(s, "false")) {
            if (p_val) *p_val = 0;
            return 1;
        }
        if (!strcasecmp(s, "true")) {
            if (p_val) *p_val = 1;
            return 1;
        }
        errno = 0;
        v = strtol(s, &eptr, 10);
        if (errno || *eptr) {
            return -1;
        }
        if (v < 0) {
            v = default_value;
        } else if (v > 0) {
            v = 1;
        }
        if (p_val) *p_val = v;
        return 1;
    }
}

int
hr_cgi_param_int_opt_2(
        struct http_request_info *phr,
        const unsigned char *name,
        int *p_val,
        int *p_set_flag)
{
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, name);
        if (jj) {
            int r = json_to_int(jj, p_val, 0);
            if (r >= 0) *p_set_flag = 1;
            return r;
        } else {
            return 0;
        }
    } else {
        const unsigned char *s = 0, *p;
        char *eptr = 0;
        int x;

        ASSERT(p_val);
        ASSERT(p_set_flag);

        *p_val = 0;
        *p_set_flag = 0;

        if (!(x = hr_cgi_param(phr, name, &s))) return 0;
        else if (x < 0) return -1;

        p = s;
        while (*p && isspace(*p)) p++;
        if (!*p) return 0;

        errno = 0;
        x = strtol(s, &eptr, 10);
        if (errno || *eptr) return -1;
        *p_val = x;
        *p_set_flag = 1;
        return 0;
    }
}

#define SIZE_T (1024LL * 1024L * 1024L * 1024L)
#define SIZE_G (1024LL * 1024 * 1024)
#define SIZE_M (1024LL * 1024)
#define SIZE_K (1024LL)

int
hr_cgi_param_size64_opt(
        struct http_request_info *phr,
        const unsigned char *name,
        ej_size64_t *p_val,
        ej_size64_t default_value)
{
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, name);
        if (jj) {
            if (jj->type == cJSON_Number) {
                if (jj->valueint != jj->valuedouble) return -1;
                if (p_val) *p_val = jj->valueint;
                return 0;
            } else if (jj->type == cJSON_String) {
                long long current_size = 0;
                const unsigned char *pc = jj->valuestring;
                while (isspace(*pc)) ++pc;
                if (!*pc) {
                    if (p_val) *p_val = default_value;
                    return 0;
                }
                while (*pc) {
                    while (isspace(*pc)) ++pc;
                    if (!*pc) break;
                    if (*pc != '-' && *pc != '+' && !isdigit(*pc)) return -1;
                    long long cur = 0;
                    errno = 0;
                    char *eptr = NULL;
                    cur = strtoll(pc, &eptr, 10);
                    if (errno || (const unsigned char*) eptr == pc) return -1;
                    pc = eptr;
                    while (isspace(*pc)) ++pc;
                    if (!*pc) {
                        if (__builtin_add_overflow(current_size, cur, &current_size)) return -1;
                        break;
                    } else if (*pc == 'k' || *pc == 'K') {
                        if (__builtin_mul_overflow(cur, 1024LL, &cur)) return -1;
                        if (__builtin_add_overflow(current_size, cur, &current_size)) return -1;
                    } else if (*pc == 'm' || *pc == 'M') {
                        if (__builtin_mul_overflow(cur, 1048576LL, &cur)) return -1;
                        if (__builtin_add_overflow(current_size, cur, &current_size)) return -1;
                    } else if (*pc == 'g' || *pc == 'G') {
                        if (__builtin_mul_overflow(cur, 1073741824LL, &cur)) return -1;
                        if (__builtin_add_overflow(current_size, cur, &current_size)) return -1;
                    } else if (*pc == 't' || *pc == 'T') {
                        if (__builtin_mul_overflow(cur, 1099511627776LL, &cur)) return -1;
                        if (__builtin_add_overflow(current_size, cur, &current_size)) return -1;
                    } else {
                        return -1;
                    }
                    ++pc;
                }
                if (p_val) *p_val = current_size;
                return 0;
            } else {
                return -1;
            }
        } else {
            if (p_val) *p_val = default_value;
            return 0;
        }
    } else {
        const unsigned char *s = 0, *e;
        char *eptr = 0;
        long long x;
        int len;

        if (!(x = hr_cgi_param(phr, name, &s)) || !s) {
            if (p_val) *p_val = default_value;
            return 0;
        } else if (x < 0) return -1;

        len = strlen(s);
        while (len > 0 && isspace(s[len - 1])) --len;
        if (!len) {
            if (p_val) *p_val = default_value;
            return 0;
        }
        e = s + len;

        errno = 0;
        x = strtoll(s, &eptr, 10);
        if (errno) return -1;
        s = (const unsigned char *) eptr;
        if (s == e) {
            if (p_val) *p_val = x;
            return 0;
        }
        while (isspace(*s)) ++s;
        if (*s == 't' || *s == 'T') {
            if (x < -8388608LL || x > 8388607LL) return -1;
            x *= SIZE_T;
        } else if (*s == 'g' || *s == 'G') {
            if (x < -8589934592LL || x > 8589934591LL) return -1;
            x *= SIZE_G;
        } else if (*s == 'm' || *s == 'M') {
            if (x < -8796093022208LL || x > 8796093022207LL) return -1;
            x *= SIZE_M;
        } else if (*s == 'k' || *s == 'K') {
            if (x < -9007199254740992LL || x > 9007199254740991LL) return -1;
            x *= SIZE_K;
        } else {
            return -1;
        }
        ++s;
        if (s != e) return -1;
        if (p_val) *p_val = x;
        return 0;
    }
}

void
hr_master_url(
        FILE *out_f,
        const struct http_request_info *phr)
{
  if (phr->rest_mode > 0) {
    fprintf(out_f, "%s/master", phr->context_url);
  } else if (phr->cnts && phr->cnts->register_url) {
    fprintf(out_f, "%s", phr->cnts->register_url);
  } else {
#if defined CGI_PROG_SUFFIX
    fprintf(out_f, "%s/new-master%s", phr->context_url, CGI_PROG_SUFFIX);
#else
    fprintf(out_f, "%s/new-master", phr->context_url);
#endif
  }
}

void
hr_judge_url(
        FILE *out_f,
        const struct http_request_info *phr)
{
  if (phr->rest_mode > 0) {
    fprintf(out_f, "%s/judge", phr->context_url);
  } else if (phr->cnts && phr->cnts->register_url) {
    fprintf(out_f, "%s", phr->cnts->register_url);
  } else {
#if defined CGI_PROG_SUFFIX
    fprintf(out_f, "%s/new-judge%s", phr->context_url, CGI_PROG_SUFFIX);
#else
    fprintf(out_f, "%s/new-judge", phr->context_url);
#endif
  }
}

void
hr_register_url(
        FILE *out_f,
        const struct http_request_info *phr)
{
  if (phr->rest_mode > 0) {
    fprintf(out_f, "%s/register", phr->context_url);
  } else if (phr->cnts && phr->cnts->register_url) {
    fprintf(out_f, "%s", phr->cnts->register_url);
  } else {
#if defined CGI_PROG_SUFFIX
    fprintf(out_f, "%s/new-register%s", phr->context_url, CGI_PROG_SUFFIX);
#else
    fprintf(out_f, "%s/new-register", phr->context_url);
#endif
  }
}

void
hr_client_url(
        FILE *out_f,
        const struct http_request_info *phr)
{
  if (phr->rest_mode > 0) {
    fprintf(out_f, "%s/user", phr->context_url);
  } else if (phr->cnts && phr->cnts->team_url) {
    fprintf(out_f, "%s", phr->cnts->team_url);
  } else {
#if defined CGI_PROG_SUFFIX
    fprintf(out_f, "%s/new-client%s", phr->context_url, CGI_PROG_SUFFIX);
#else
    fprintf(out_f, "%s/new-client", phr->context_url);
#endif
  }
}

void
hr_set_symbolic_action_table(
        int table_size,
        const unsigned char * const *table,
        const unsigned char * const *submit_labels,
        const unsigned char * const * helps)
{
    symbolic_action_table = table;
    submit_button_labels = submit_labels;
    symbolic_action_table_size = table_size;
    help_urls = helps;
}

const unsigned char *
hr_url_2(
        FILE *out_f,
        const struct http_request_info *phr,
        int action)
{
    if (phr->rest_mode > 0 && symbolic_action_table) {
        if (action < 0 || action >= symbolic_action_table_size) action = 0;
        fprintf(out_f, "%s/%s", phr->self_url, symbolic_action_table[action]);
        if (phr->session_id) {
            fprintf(out_f, "/S%016llx", phr->session_id);
        }
        return "?";
    } else {
        const unsigned char *sep = "?";
        fprintf(out_f, "%s", phr->self_url);
        if (phr->session_id) {
            fprintf(out_f, "%sSID=%016llx", sep, phr->session_id);
            sep = "&amp;";
        }
        if (action > 0) {
            fprintf(out_f, "%saction=%d", sep, action);
            sep = "&amp;";
        }
        return sep;
    }
}

const unsigned char *
hr_url_3(
        FILE *out_f,
        const struct http_request_info *phr,
        int action)
{
    if (phr->rest_mode > 0 && symbolic_action_table) {
        if (action < 0 || action >= symbolic_action_table_size) action = 0;
        fprintf(out_f, "/%s", symbolic_action_table[action]);
        if (phr->session_id) {
            fprintf(out_f, "/S%016llx", phr->session_id);
        }
        return "?";
    } else {
        const unsigned char *sep = "?";
        if (phr->session_id) {
            fprintf(out_f, "%sSID=%016llx", sep, phr->session_id);
            sep = "&amp;";
        }
        if (action > 0) {
            fprintf(out_f, "%saction=%d", sep, action);
            sep = "&amp;";
        }
        return sep;
    }
}

const unsigned char *
hr_url_4(
        FILE *out_f,
        const struct http_request_info *phr,
        int action)
{
    if (phr->rest_mode > 0 && symbolic_action_table) {
        if (action < 0 || action >= symbolic_action_table_size) action = 0;
        fprintf(out_f, "/%s", symbolic_action_table[action]);
        return "?";
    } else {
        const unsigned char *sep = "?";
        if (action > 0) {
            fprintf(out_f, "%saction=%d", sep, action);
            sep = "&amp;";
        }
        return sep;
    }
}

const unsigned char *
hr_url_5(
        FILE *out_f,
        const struct http_request_info *phr,
        const unsigned char *action_str)
{
    if (phr->rest_mode > 0 && symbolic_action_table) {
        fprintf(out_f, "/%s", action_str);
        if (phr->session_id) {
            fprintf(out_f, "/S%016llx", phr->session_id);
        }
        return "?";
    } else {
        const unsigned char *sep = "?";
        if (phr->session_id) {
            fprintf(out_f, "%sSID=%016llx", sep, phr->session_id);
            sep = "&amp;";
        }
        if (action_str && *action_str) {
            fprintf(out_f, "%saction=%s", sep, action_str);
            sep = "&amp;";
        }
        return sep;
    }
}

void
hr_submit_button(
        FILE *out_f,
        const unsigned char *var_name,
        int action,
        const unsigned char *label)
{
    if (!var_name) var_name = "action";

    if (!label && submit_button_labels && action > 0 && action < symbolic_action_table_size)
        label = gettext(submit_button_labels[action]);
    if (!label) label = "Submit";

    fprintf(out_f, "<input type=\"submit\" name=\"%s", var_name);
    if (action > 0) {
        fprintf(out_f, "_%d", action);
    }
    fprintf(out_f, "\" value=\"%s\" />", label);
}

const unsigned char *
hr_redirect_2(
        FILE *out_f,
        const struct http_request_info *phr,
        int action)
{
    if (phr->rest_mode > 0 && symbolic_action_table) {
        if (action < 0 || action >= symbolic_action_table_size) action = 0;
        fprintf(out_f, "%s/%s", phr->self_url, symbolic_action_table[action]);
        if (phr->session_id) {
            fprintf(out_f, "/S%016llx", phr->session_id);
        }
        return "?";
    } else {
        const unsigned char *sep = "?";
        fprintf(out_f, "%s", phr->self_url);
        if (phr->session_id) {
            fprintf(out_f, "%sSID=%016llx", sep, phr->session_id);
            sep = "&";
        }
        if (action > 0) {
            fprintf(out_f, "%saction=%d", sep, action);
            sep = "&";
        }
        return sep;
    }
}

void
hr_register_redirect(
        FILE *out_f,
        const struct http_request_info *phr)
{
  if (phr->rest_mode > 0) {
    fprintf(out_f, "%s/register", phr->context_url);
  } else if (phr->cnts && phr->cnts->register_url) {
    fprintf(out_f, "%s", phr->cnts->register_url);
  } else {
#if defined CGI_PROG_SUFFIX
    fprintf(out_f, "%s/new-register%s", phr->context_url, CGI_PROG_SUFFIX);
#else
    fprintf(out_f, "%s/new-register", phr->context_url);
#endif
  }
}

void
hr_control_redirect(
        FILE *out_f,
        const struct http_request_info *phr)
{
    // hack
    int len = strlen(phr->context_url);
    if (len > 3 && phr->context_url[len - 1] == 'j'
        && phr->context_url[len - 2] == 'e'
        && phr->context_url[len - 3] == '/') {
        len -= 3;
    }
#if defined CGI_PROG_SUFFIX
    fprintf(out_f, "%.*s/serve-control%s", len, phr->context_url, CGI_PROG_SUFFIX);
#else
    fprintf(out_f, "%.*s/serve-control", len, phr->context_url);
#endif
}

const unsigned char *
hr_redirect_3(
        FILE *out_f,
        const struct http_request_info *phr,
        int action)
{
    if (phr->rest_mode > 0 && symbolic_action_table) {
        if (action < 0 || action >= symbolic_action_table_size) action = 0;
        fprintf(out_f, "/%s", symbolic_action_table[action]);
        if (phr->session_id) {
            fprintf(out_f, "/S%016llx", phr->session_id);
        }
        return "?";
    } else {
        const unsigned char *sep = "?";
        if (phr->session_id) {
            fprintf(out_f, "%sSID=%016llx", sep, phr->session_id);
            sep = "&";
        }
        if (action > 0) {
            fprintf(out_f, "%saction=%d", sep, action);
            sep = "&";
        }
        return sep;
    }
}

const unsigned char *
hr_redirect_5(
        FILE *out_f,
        const struct http_request_info *phr,
        const unsigned char *action_str)
{
    if (phr->rest_mode > 0) {
        fprintf(out_f, "/%s", action_str);
        if (phr->session_id) {
            fprintf(out_f, "/S%016llx", phr->session_id);
        }
        return "?";
    } else {
        const unsigned char *sep = "?";
        if (phr->session_id) {
            fprintf(out_f, "%sSID=%016llx", sep, phr->session_id);
            sep = "&";
        }
        if (action_str && *action_str) {
            fprintf(out_f, "%saction=%s", sep, action_str);
            sep = "&";
        }
        return sep;
    }
}

void
hr_print_help_url(FILE *f, int action)
{
  const unsigned char *help_url = 0;

  if (action > 0 && action < symbolic_action_table_size) {
    help_url = help_urls[action];
  }
  if (help_url) {
    fprintf(f, "<a target=\"_blank\" href=\"http://ejudge.ru/wiki/index.php/%s\">%s</a>", help_url, "Help");
  } else {
    fprintf(f, "&nbsp;");
  }
}

void
hr_print_help_url_2(FILE *f, const unsigned char *topic)
{
  if (topic) {
    fprintf(f, "<a target=\"_blank\" href=\"http://ejudge.ru/wiki/index.php/%s\">%s</a>", topic, "Help");
  } else {
    fprintf(f, "&nbsp;");
  }
}

int
hr_cgi_param_string(
        const struct http_request_info *phr,
        const unsigned char *param,
        unsigned char **p_value,
        const unsigned char *prepend_str)
{
    const unsigned char *str = NULL;
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, param);
        if (jj) {
            if (jj->type == cJSON_NULL) {
                *p_value = NULL;
                return 0;
            } else if (jj->type == cJSON_String) {
                str = jj->valuestring;
            } else {
                *p_value = NULL;
                return -1;
            }
        } else {
            *p_value = NULL;
            return 0;
        }
    } else {
        int r = hr_cgi_param(phr, param, &str);
        if (r <= 0) {
            *p_value = NULL;
            return r;
        }
        if (!str) {
            *p_value = NULL;
            return 0;
        }
    }
    int i = 0;
    while (str[i] && (str[i] <= ' ' || str[i] == 0x7f)) ++i;
    if (!str[i]) {
        *p_value = NULL;
        return 0;
    }
    int len = strlen(str);
    while (len > 0 && (str[len - 1] <= ' ' || str[len - 1] == 0x7f)) --len;
    if (len <= 0) {
        *p_value = NULL;
        return 0;
    }
    if (!prepend_str) prepend_str = "";
    int prepend_len = strlen(prepend_str);
    unsigned char *out = malloc(prepend_len + len + 1);
    memcpy(out, prepend_str, prepend_len);
    unsigned char *p = out + prepend_len;
    for (; i < len; ++i) {
        if (str[i] <= ' ' || str[i] == 0x7f) {
            *p++ = ' ';
        } else {
            *p++ = str[i];
        }
    }
    *p = 0;
    *p_value = out;
    return 1;
}

int
hr_cgi_param_string_2(
        const struct http_request_info *phr,
        const unsigned char *param,
        unsigned char **p_value,
        const unsigned char *prepend_str)
{
    const unsigned char *str = NULL;
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, param);
        if (jj) {
            if (jj->type == cJSON_NULL) {
                *p_value = strdup("");
                return 0;
            } else if (jj->type == cJSON_String) {
                str = jj->valuestring;
            } else {
                *p_value = strdup("");
                return -1;
            }
        } else {
            *p_value = strdup("");
            return 0;
        }
    } else {
        int r = hr_cgi_param(phr, param, &str);
        if (r <= 0) {
            *p_value = strdup("");
            return r;
        }
        if (!str) {
            *p_value = strdup("");
            return 0;
        }
    }
    int i = 0;
    while (str[i] && (str[i] <= ' ' || str[i] == 0x7f)) ++i;
    if (!str[i]) {
        *p_value = strdup("");
        return 0;
    }
    int len = strlen(str);
    while (len > 0 && (str[len - 1] <= ' ' || str[len - 1] == 0x7f)) --len;
    if (len <= 0) {
        *p_value = strdup("");
        return 0;
    }
    if (!prepend_str) prepend_str = "";
    int prepend_len = strlen(prepend_str);
    unsigned char *out = malloc(prepend_len + len + 1);
    memcpy(out, prepend_str, prepend_len);
    unsigned char *p = out + prepend_len;
    for (; i < len; ++i) {
        if (str[i] <= ' ' || str[i] == 0x7f) {
            *p++ = ' ';
        } else {
            *p++ = str[i];
        }
    }
    *p = 0;
    *p_value = out;
    return 1;
}

int
hr_cgi_param_h64(
        const struct http_request_info *phr,
        const unsigned char *name,
        unsigned long long *p_val)
{
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, name);
        if (jj) {
            if (jj->type == cJSON_String) {
                const char *s = jj->valuestring;
                char *eptr = NULL;
                errno = 0;
                unsigned long long x = strtoull(s, &eptr, 16);
                if (errno || eptr == s || *eptr) return -1;
                if (p_val) *p_val = x;
                return 0;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else {
        const unsigned char *s = NULL;
        if (hr_cgi_param(phr, name, &s) <= 0 || !s) return -1;
        char *eptr = NULL;
        errno = 0;
        unsigned long long x = strtoull(s, &eptr, 16);
        if (errno || (const unsigned char *) eptr == s || *eptr) return -1;
        if (p_val) *p_val = x;
        return 0;
    }
}

int
hr_cgi_param_i64_opt(
        const struct http_request_info *phr,
        const unsigned char *name,
        long long *p_val,
        long long default_value)
{
    if (phr->json) {
        cJSON *jj = cJSON_GetObjectItem(phr->json, name);
        if (jj) {
            if (jj->type == cJSON_False) {
                if (p_val) *p_val = 0;
                return 1;
            } else if (jj->type == cJSON_True) {
                if (p_val) *p_val = 1;
                return 1;
            } else if (jj->type == cJSON_NULL) {
                if (p_val) *p_val = 0;
                return 1;
            } else if (jj->type == cJSON_Number) {
                if (jj->valueint != jj->valuedouble) return -1;
                if (p_val) *p_val = jj->valueint;
                return 1;
            } else if (jj->type == cJSON_String) {
                const char *s = jj->valuestring;
                char *eptr = NULL;
                errno = 0;
                long long x = strtoll(s, &eptr, 10);
                if (errno || eptr == s || *eptr) {
                    return -1;
                }
                if (p_val) *p_val = x;
                return 1;
            } else {
                // invalid value
                return -1;
            }
        } else {
            if (p_val) *p_val = default_value;
            return 0;
        }
    } else {
        const unsigned char *s = NULL;
        int res = hr_cgi_param(phr, name, &s);
        if (!res || !s) {
            if (p_val) *p_val = default_value;
            return 0;
        }
        if (res < 0) {
            return -1;
        }
        char *eptr = NULL;
        errno = 0;
        long long x = strtoll(s, &eptr, 10);
        if (errno || (const unsigned char *) eptr == s || *eptr) {
            return -1;
        }
        if (p_val) *p_val = x;
        return 1;
    }
}

/*
 * Local variables:
 *  c-basic-offset: 4
 * End:
 */
