/* -*- c -*- */
#ifndef __PROBLEM_CONFIG_H__
#define __PROBLEM_CONFIG_H__

/* Copyright (C) 2012-2021 Alexander Chernov <cher@ejudge.ru> */

/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#include "ejudge/ej_types.h"
#include "ejudge/parsecfg.h"

#include <time.h>

#ifndef META_ATTRIB
#if defined __RCC__
#undef __attribute__
#define META_ATTRIB(x) __attribute__(x)
#else
#define META_ATTRIB(x)
#endif /* __RCC__ */
#endif /* META_ATTRIB */

/* sizeof(struct problem_config_section) == 712 */
struct problem_config_section
{
  struct generic_section_config g META_ATTRIB((meta_hidden));

  ejintbool_t manual_checking;
  ejintbool_t check_presentation;
  ejintbool_t scoring_checker;
  ejintbool_t enable_checker_token;
  ejintbool_t interactive_valuer;
  ejintbool_t disable_pe;
  ejintbool_t disable_wtl;
  ejintbool_t wtl_is_cf;
  ejintbool_t use_stdin;
  ejintbool_t use_stdout;
  ejintbool_t combined_stdin;
  ejintbool_t combined_stdout;
  ejintbool_t binary_input;
  ejintbool_t binary;
  ejintbool_t ignore_exit_code;
  ejintbool_t olympiad_mode;
  ejintbool_t score_latest;
  ejintbool_t score_latest_or_unmarked;
  ejintbool_t score_latest_marked;
  ejintbool_t score_tokenized;
  ejintbool_t use_ac_not_ok;
  ejintbool_t ignore_prev_ac;
  ejintbool_t team_enable_rep_view;
  ejintbool_t team_enable_ce_view;
  ejintbool_t team_show_judge_report;
  ejintbool_t show_checker_comment;
  ejintbool_t ignore_compile_errors;
  ejintbool_t variable_full_score;
  ejintbool_t ignore_penalty;
  ejintbool_t use_corr;
  ejintbool_t use_info;
  ejintbool_t use_tgz;
  ejintbool_t accept_partial;
  ejintbool_t disable_user_submit;
  ejintbool_t disable_tab;
  ejintbool_t unrestricted_statement;
  ejintbool_t enable_submit_after_reject;
  ejintbool_t hide_file_names;
  ejintbool_t hide_real_time_limit;
  ejintbool_t enable_tokens;
  ejintbool_t tokens_for_user_ac;
  ejintbool_t disable_submit_after_ok;
  ejintbool_t disable_auto_testing;
  ejintbool_t disable_testing;
  ejintbool_t enable_compilation;
  ejintbool_t skip_testing;
  ejintbool_t hidden;
  ejintbool_t stand_hide_time;
  ejintbool_t advance_to_next;
  ejintbool_t disable_ctrl_chars;
  ejintbool_t enable_text_form;
  ejintbool_t stand_ignore_score;
  ejintbool_t stand_last_column;
  ejintbool_t disable_security;
  ejintbool_t enable_suid_run;
  ejintbool_t enable_container;
  ejintbool_t enable_multi_header;
  ejintbool_t use_lang_multi_header;
  ejintbool_t require_any;
  ejintbool_t valuer_sets_marked;
  ejintbool_t ignore_unmarked;
  ejintbool_t disable_stderr;
  ejintbool_t enable_process_group;
  ejintbool_t enable_kill_all;
  ejintbool_t enable_testlib_mode;
  ejintbool_t hide_variant;
  ejintbool_t enable_extended_info;
  ejintbool_t stop_on_first_fail;
  ejintbool_t enable_control_socket;

  int id;
  int real_time_limit;
  int time_limit;
  int time_limit_millis;
  int full_score;
  int full_user_score;
  int min_score_1;
  int min_score_2;
  int test_score;
  int run_penalty;
  int acm_run_penalty;
  int disqualified_penalty;
  int compile_error_penalty;
  int min_tests_to_accept;
  int checker_real_time_limit;
  int checker_time_limit_ms;
  int priority_adjustment;
  int score_multiplier;
  int prev_runs_to_show;
  int max_user_run_count;
  int interactor_time_limit;
  int interactor_real_time_limit;
  int max_open_file_count;
  int max_process_count;
  int tests_to_accept;

  time_t deadline;
  time_t start_date;

  size_t max_vm_size;
  size_t max_data_size;
  size_t max_stack_size;
  size_t max_rss_size;
  size_t max_core_size;
  size_t max_file_size;
  size_t checker_max_vm_size;
  size_t checker_max_stack_size;
  size_t checker_max_rss_size;

  unsigned char *type;
  unsigned char *short_name;
  unsigned char *long_name;
  unsigned char *long_name_en;
  unsigned char *stand_name;
  unsigned char *internal_name;
  unsigned char *test_dir;
  unsigned char *test_sfx;
  unsigned char *corr_sfx;
  unsigned char *info_sfx;
  unsigned char *tgz_sfx;
  unsigned char *tgzdir_sfx;
  unsigned char *input_file;
  unsigned char *output_file;
  unsigned char *test_score_list;
  unsigned char *score_tests;
  unsigned char *standard_checker;
  unsigned char *spelling;
  unsigned char *plugin_file;
  unsigned char *xml_file;
  unsigned char *stand_attr;
  unsigned char *source_header;
  unsigned char *source_footer;
  unsigned char *test_pat;
  unsigned char *corr_pat;
  unsigned char *info_pat;
  unsigned char *tgz_pat;
  unsigned char *tgzdir_pat;
  unsigned char *normalization;
  unsigned char *check_cmd;
  unsigned char *valuer_cmd;
  unsigned char *interactor_cmd;
  unsigned char *style_checker_cmd;
  unsigned char *test_checker_cmd;
  unsigned char *init_cmd;
  unsigned char *start_cmd;
  unsigned char *solution_src;
  unsigned char *solution_cmd;
  unsigned char *score_bonus;
  unsigned char *open_tests;
  unsigned char *final_open_tests;
  unsigned char *token_open_tests;
  unsigned char *extid;
  unsigned char *revision;
  unsigned char *tokens;
  unsigned char *umask;
  unsigned char *ok_status;
  unsigned char *header_pat;
  unsigned char *footer_pat;
  unsigned char *compiler_env_pat;
  unsigned char *uuid;
  unsigned char *container_options;

  char **test_sets;
  char **date_penalty;
  char **group_start_date;
  char **group_deadline;
  char **disable_language;
  char **enable_language;
  char **require;
  char **provide_ok;
  char **lang_time_adj;
  char **lang_time_adj_millis;
  char **lang_max_vm_size;
  char **lang_max_stack_size;
  char **lang_max_rss_size;
  char **personal_deadline;
  char **score_view;
  char **score_view_text;

  ejenvlist_t lang_compiler_env;
  ejenvlist_t checker_env;
  ejenvlist_t valuer_env;
  ejenvlist_t interactor_env;
  ejenvlist_t style_checker_env;
  ejenvlist_t test_checker_env;
  ejenvlist_t init_env;
  ejenvlist_t start_env;
  ejenvlist_t statement_env;
  ejenvlist_t lang_compiler_container_options;
};

void
problem_config_section_init(struct generic_section_config *gp);
struct problem_config_section *
problem_config_section_alloc(void);
void
problem_config_section_free(struct generic_section_config *gp);
struct problem_config_section *
problem_config_section_parse_cfg(const unsigned char *path, FILE *f);
struct problem_config_section *
problem_config_section_parse_cfg_str(const unsigned char *path, char *buf, size_t size);
void
problem_config_section_unparse_cfg(FILE *out_f, const struct problem_config_section *p);


#endif /* __PROBLEM_CONFIG_H__ */
