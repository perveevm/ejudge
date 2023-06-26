/* -*- mode: c -*- */

/* Copyright (C) 2008-2023 Alexander Chernov <cher@ejudge.ru> */

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

static struct common_plugin_data *
init_func(void);

static int
finish_func(struct common_plugin_data *data);

static int
prepare_func(
        struct common_plugin_data *data,
        const struct ejudge_cfg *config,
        struct xml_tree *tree);

static struct rldb_plugin_cnts *
open_func(
        struct rldb_plugin_data *data,
        struct runlog_state *rl_state,
        const struct ejudge_cfg *config,
        const struct contest_desc *cnts,
        const struct section_global_data *global,
        struct metrics_contest_data *metrics,
        int flags,
        time_t init_duration,
        time_t init_sched_time,
        time_t init_finish_time);

static struct rldb_plugin_cnts *
close_func(struct rldb_plugin_cnts *cdata);

static int
reset_func(
        struct rldb_plugin_cnts *cdata,
        time_t init_duration,
        time_t init_sched_time,
        time_t init_finish_time);

static int
set_runlog_func(
        struct rldb_plugin_cnts *cdata,
        int id_offset,
        int total_entries,
        struct run_entry *entries);

static int
backup_func(struct rldb_plugin_cnts *cdata);

static int
flush_func(struct rldb_plugin_cnts *cdata);

static int
get_insert_run_id_func(
        struct rldb_plugin_cnts *cdata,
        time_t create_time,
        int user_id,
        int nsec);

static int
add_entry_func(
        struct rldb_plugin_cnts *cdata,
        int run_id,
        const struct run_entry *re,
        uint64_t mask,
        struct run_entry *ure);

static int
undo_add_entry_func(
        struct rldb_plugin_cnts *cdata,
        int run_id);

static int
change_status_func(
        struct rldb_plugin_cnts *cdata,
        int run_id,
        int new_status,
        int new_test,
        int new_passed_mode,
        int new_score,
        int judge_id,
        const ej_uuid_t *judge_uuid,
        unsigned int verdict_bits,
        struct run_entry *ure);

static int
start_func(
        struct rldb_plugin_cnts *cdata,
        time_t start_time);

static int
stop_func(
        struct rldb_plugin_cnts *cdata,
        time_t stop_time);

static int
set_duration_func(
        struct rldb_plugin_cnts *cdata,
        int duration);

static int
schedule_func(
        struct rldb_plugin_cnts *cdata,
        time_t sched_time);

static int
set_finish_time_func(
        struct rldb_plugin_cnts *cdata,
        time_t finish_time);

static int
save_times_func(struct rldb_plugin_cnts *cdata);

static int
set_status_func(
        struct rldb_plugin_cnts *cdata,
        int run_id,
        int new_status);

static int
clear_entry_func(
        struct rldb_plugin_cnts *cdata,
        int run_id);

static int
set_hidden_func(
        struct rldb_plugin_cnts *cdata,
        int run_id,
        int new_hidden,
        struct run_entry *ure);

static int
set_pages_func(
        struct rldb_plugin_cnts *cdata,
        int run_id,
        int new_pages,
        struct run_entry *ure);

static int
set_entry_func(
        struct rldb_plugin_cnts *cdata,
        int run_id,
        const struct run_entry *in,
        uint64_t mask,
        struct run_entry *ure);

static int
squeeze_func(struct rldb_plugin_cnts *cdata);

static int
put_entry_func(
        struct rldb_plugin_cnts *cdata,
        const struct run_entry *re);

static int
put_header_func(
        struct rldb_plugin_cnts *cdata,
        const struct run_header *rh);

static int
check_func(
        struct rldb_plugin_cnts *cdata,
        FILE *log_f);

static int
change_status_3_func(
        struct rldb_plugin_cnts *cdata,
        int run_id,
        int new_status,
        int new_test,
        int new_passed_mode,
        int new_score,
        int new_is_marked,
        int has_user_score,
        int user_status,
        int user_tests_passed,
        int user_score,
        unsigned int verdict_bits,
        struct run_entry *ure);

static int
change_status_4_func(
        struct rldb_plugin_cnts *cdata,
        int run_id,
        int new_status,
        struct run_entry *ure);

static int
user_run_header_set_start_time_func(
        struct rldb_plugin_cnts *cdata,
        int user_id,
        time_t start_time,
        int is_virtual,
        int last_change_user_id);

static int
user_run_header_set_stop_time_func(
        struct rldb_plugin_cnts *cdata,
        int user_id,
        time_t stop_time,
        int last_change_user_id);

static int
user_run_header_set_duration_func(
        struct rldb_plugin_cnts *cdata,
        int user_id,
        int duration,
        int last_change_user_id);

static int
user_run_header_set_is_checked_func(
        struct rldb_plugin_cnts *cdata,
        int user_id,
        int is_checked,
        int last_change_user_id);

static int
user_run_header_delete_func(
        struct rldb_plugin_cnts *cdata,
        int user_id);

static int
append_run_func(
        struct rldb_plugin_cnts *cdata,
        const struct run_entry *re,
        uint64_t mask,
        struct timeval *p_tv,
        int64_t *p_serial_id,
        ej_uuid_t *p_uuid,
        struct run_entry *ure);

static int
run_set_is_checked_func(
        struct rldb_plugin_cnts *cdata,
        int run_id,
        int is_checked);
