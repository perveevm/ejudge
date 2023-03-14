/* -*- c -*- */
#ifndef __SUPER_HTML_H__
#define __SUPER_HTML_H__

/* Copyright (C) 2004-2023 Alexander Chernov <cher@ejudge.ru> */

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

#include "ejudge/ej_types.h"
#include "ejudge/opcaps.h"

#include <stdio.h>

struct ejudge_cfg;
struct sid_state;

int super_html_serve_probe_run(FILE *f,
                               int priv_level,
                               int user_id,
                               int contest_id,
                               const unsigned char *login,
                               ej_cookie_t session_id,
                               const ej_ip_t *ip_address,
                               int ssl,
                               struct ejudge_cfg *config,
                               const unsigned char *self_url,
                               const unsigned char *hidden_vars,
                               const unsigned char *extra_args);

struct userlist_clnt;
int super_html_commit_contest(FILE *f,
                              int priv_level,
                              int user_id,
                              const unsigned char *login,
                              ej_cookie_t session_id,
                              const ej_ip_t *ip_address,
                              struct ejudge_cfg *config,
                              struct userlist_clnt *us_conn,
                              struct sid_state *sstate,
                              int cmd,
                              const unsigned char *self_url,
                              const unsigned char *hidden_vars,
                              const unsigned char *extra_args);

int
super_html_commit_contest_2(
        FILE *log_f,
        int user_id,
        const unsigned char *login,
        const ej_ip_t *ip_address,
        const struct ejudge_cfg *config,
        struct userlist_clnt *us_conn,
        struct sid_state *sstate);

struct contest_desc;
struct sid_state;

int
super_html_edited_cnts_dialog(
        FILE *out_f,
        int priv_level,
        int user_id,
        const unsigned char *login,
        ej_cookie_t session_id,
        const ej_ip_t *ip_address,
        const struct ejudge_cfg *config,
        struct sid_state *sstate,
        const unsigned char *self_url,
        const unsigned char *hidden_vars,
        const unsigned char *extra_args,
        const struct contest_desc *new_cnts,
        int new_edit_mode);
struct sid_state;
int
super_html_locked_cnts_dialog(
        FILE *out_f,
        int priv_level,
        int user_id,
        const unsigned char *login,
        ej_cookie_t session_id,
        const ej_ip_t *ip_address,
        const struct ejudge_cfg *config,
        struct sid_state *sstate,
        const unsigned char *self_url,
        const unsigned char *hidden_vars,
        const unsigned char *extra_args,
        int contest_id,
        const struct sid_state *other_ss,
        int new_edit_mode);

int super_html_open_contest(struct contest_desc *cnts, int user_id,
                            const unsigned char *user_login,
                            const ej_ip_t *ip_address);
int super_html_close_contest(struct contest_desc *cnts, int user_id,
                             const unsigned char *user_login,
                             const ej_ip_t *ip_address);

int super_html_make_invisible_contest(struct contest_desc *cnts,
                                      int user_id,
                                      const unsigned char *user_login,
                                      const ej_ip_t *ip_address);
int super_html_make_visible_contest(struct contest_desc *cnts,
                                    int user_id,
                                    const unsigned char *user_login,
                                    const ej_ip_t *ip_address);

int super_html_serve_managed_contest(struct contest_desc *cnts, int user_id,
                                     const unsigned char *user_login,
                                     const ej_ip_t *ip_address);
int super_html_serve_unmanaged_contest(struct contest_desc *cnts, int user_id,
                                       const unsigned char *user_login,
                                       const ej_ip_t *ip_address);

int super_html_run_managed_contest(struct contest_desc *cnts, int user_id,
                                   const unsigned char *user_login,
                                   const ej_ip_t *ip_address);
int super_html_run_unmanaged_contest(struct contest_desc *cnts, int user_id,
                                     const unsigned char *user_login,
                                     const ej_ip_t *ip_address);

struct contest_desc *contest_tmpl_new(int contest_id,
                                      const unsigned char *login,
                                      const unsigned char *self_url,
                                      const unsigned char *ss_login,
                                      const ej_ip_t *pip,
                                      int ssl_flag,
                                      const struct ejudge_cfg *ejudge_config);
struct contest_desc *contest_tmpl_clone(struct sid_state *sstate,
                                        int contest_id, int orig_id,
                                        const unsigned char *login,
                                        const unsigned char *ss_login);

int super_html_set_contest_var(struct sid_state *sstate, int cmd,
                               int param1, const unsigned char *param2,
                               int param3, int param4, int param5);

int super_html_lang_cmd(struct sid_state *sstate, int cmd,
                        int param1, const unsigned char *param2,
                        int param3, int param4);

int super_html_prob_cmd(struct sid_state *sstate, int cmd,
                        int param1, const unsigned char *param2,
                        int param3, int param4);

int super_html_prob_param(struct sid_state *sstate, int cmd,
                          int param1, const unsigned char *param2,
                          int param3, int param4);

int super_html_report_error(FILE *f,
                            ej_cookie_t session_id,
                            const unsigned char *self_url,
                            const unsigned char *extra_args,
                            const char *format, ...);

int super_html_get_serve_header_and_footer(const unsigned char *path,
                                           unsigned char **p_header,
                                           unsigned char **p_footer);
int super_html_serve_unparse_and_save(const unsigned char *path,
                                      const unsigned char *tmp_path,
                                      const struct sid_state *sstate,
                                      const struct ejudge_cfg *config,
                                      const unsigned char *charset,
                                      const unsigned char *header,
                                      const unsigned char *footer,
                                      const unsigned char *audit);

int super_html_read_serve(FILE *flog,
                          const unsigned char *path,
                          const struct ejudge_cfg *config,
                          const struct contest_desc *cnts,
                          struct sid_state *sstate);
void super_html_load_serve_cfg(const struct contest_desc *cnts,
                               const struct ejudge_cfg *config,
                               struct sid_state *sstate);
void super_html_fix_serve(struct sid_state *sstate,
                          int orig_id, int contest_id);

int
super_html_new_check_tests(
        FILE *flog,
        const struct ejudge_cfg *config,
        struct sid_state *sstate);

int super_html_update_versions(struct sid_state *sstate);

int super_html_variant_param(struct sid_state *sstate, int cmd,
                             int param1, const unsigned char *param2,
                             int param3, int param4);
int super_html_variant_prob_op(struct sid_state *sstate, int cmd, int prob_id);

struct section_problem_data;
struct section_global_data;
int
super_html_update_variant_map(FILE *flog, int contest_id,
                              struct userlist_clnt *server_conn,
                              const struct contest_desc *cnts,
                              struct section_global_data *global,
                              int total_probs,
                              struct section_problem_data **probs);

struct http_request_info;
void
super_html_http_request(
        char **p_out_t,
        size_t *p_out_z,
        struct http_request_info *hr);

struct contest_access;
void
super_html_unparse_access_2(FILE *out_f, const struct contest_access *acc);
unsigned char *
super_html_unparse_access(const struct contest_access *acc);
struct contest_access *
super_html_copy_contest_access(const struct contest_access *p);
void
super_html_print_caps_table(
        FILE *out_f,
        opcap_t caps,
        const unsigned char *table_opts,
        const unsigned char *td_opts);
void
html_numeric_select(FILE *f, const unsigned char *param,
                    int val, int min_val, int max_val);

int
super_load_cs_languages(
        const struct ejudge_cfg *config,
        struct sid_state *sstate,
        char **extra_compile_dirs,
        int check_version_flag,
        unsigned char *cs_conf_file_buf,
        int cs_conf_file_len);

void
super_html_lang_activate(
        struct sid_state *sstate,
        int cs_lang_id);
void
super_html_lang_deactivate(
        struct sid_state *sstate,
        int cs_lang_id);

struct std_checker_info
{
  unsigned char *name;
  unsigned char *desc;
};
extern struct std_checker_info super_html_std_checkers[];

void
ss_write_html_header(
        FILE *out_f,
        struct http_request_info *phr,
        const unsigned char *title);
void
ss_write_html_footer(FILE *out_f);

int
super_html_add_problem(
        struct sid_state *sstate,
        int prob_id);

int
super_html_add_abstract_problem(
        struct sid_state *sstate,
        const unsigned char *short_name);

const unsigned char *
super_html_get_standard_checker_description(const unsigned char *standard_checker);

struct serve_state;
int
super_serve_generate_makefile(
        FILE  *log_f,
        const struct contest_desc *cnts,
        struct serve_state *cs,
        struct sid_state *sstate,
        const struct section_global_data *global,
        const struct section_problem_data *prob,
        int variant);

void
problem_id_to_short_name(int num, unsigned char *buf);
struct section_problem_data *
super_html_create_problem(
        struct sid_state *sstate,
        int prob_id);
void
super_html_serve_unparse_serve_cfg(
        FILE *f,
        const struct ejudge_cfg *config,
        const struct sid_state *sstate);
int
super_html_get_contest_header_and_footer(
        const unsigned char *path,
        unsigned char **before_start,
        unsigned char **after_end);
int
super_html_set_cnts_file_perms(
        FILE *log_f,
        const unsigned char *path,
        const struct contest_desc *cnts);

void
html_select(FILE *f, int value, const unsigned char *param_name,
            const unsigned char * const *options);

void
super_html_activate_problem(struct sid_state *sstate, int prob_id);

int
ss_get_saved_auth(
        const unsigned char *ej_login,
        unsigned char **p_poly_login,
        unsigned char **p_poly_password,
        unsigned char **p_poly_url,
        unsigned char **p_poly_key,
        unsigned char **p_poly_secret);
int
ss_find_free_prob_id(
        const struct sid_state *ss);

int
ss_find_free_prob_id_and_name(
        const struct sid_state *ss,
        unsigned char *prob_buf,
        size_t buf_size);

int
ss_get_global_caps(
        const struct http_request_info *phr,
        opcap_t *pcap);
int
ss_get_contest_caps(
        const struct http_request_info *phr,
        const struct contest_desc *cnts,
        opcap_t *pcap);

struct ss_download_status
{
  unsigned char *key;
  unsigned char *status;
  unsigned char *polygon_id;
  unsigned char *polygon_name;
};
int
ss_read_download_status(
        FILE *log_f,
        const unsigned char *path,
        FILE *f,
        int *p_exit_code,
        int *p_count,
        struct ss_download_status **p_statuses);

struct ss_user_row_info
{
  int field_id;
  unsigned char *field_desc;
};

void
ss_find_elem_positions(
        unsigned char *text,
        int size,
        int *p_user_map_count,
        int *p_user_map_begin,
        int *p_user_map_end,
        int *p_caps_count,
        int *p_caps_begin,
        int *p_caps_end);

struct userlist_user;
struct userlist_user *
ss_get_user_info(
        struct http_request_info *phr,
        int user_id,
        int contest_id);

int
ss_is_globally_privileged(
        const struct http_request_info *phr,
        const struct userlist_user *u);
int
ss_is_contest_privileged(
        const struct contest_desc *cnts,
        const struct userlist_user *u);

struct bitset_s;
unsigned char *
ss_collect_marked_set(
        struct http_request_info *phr,
        struct bitset_s *pms);
int
ss_is_privileged(
        const struct http_request_info *phr,
        const struct contest_desc *cnts,
        const struct userlist_user *u);

void
ss_string_row(
        FILE *out_f,
        const unsigned char *tr_class,
        int is_hidden,
        const unsigned char *td_class,
        const unsigned char *legend,
        const unsigned char *param_suffix,
        const unsigned char *str);

#endif /* __SUPER_HTML_H__ */
