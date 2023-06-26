/* -*- c -*- */
#ifndef __RUNLOG_STATE_H__
#define __RUNLOG_STATE_H__

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

#include "ejudge/ej_types.h"

#include <stdint.h>

#define RUNLOG_MAX_SIZE    15625000         // 2000000000 bytes

struct user_flags_info_s
{
  int nuser;
  int *flags;
};

struct run_entry_extra
{
  int prev_user_id;            /* previous run with the same user_id, -1, if none*/
  int next_user_id;            /* next run with the same user_id, -1, if none */
};

struct uuid_hash_entry
{
  int       run_id;            /* < 0, if the entry is empty */
  ej_uuid_t uuid;
};

struct rldb_plugin_iface;
struct rldb_plugin_data;
struct rldb_plugin_cnts;

#if !defined RUNS_ACCESS
#define RUNS_ACCESS const
#endif /* RUNS_ACCESS */

struct user_run_header_info
{
  int user_id;
  int duration;
  unsigned char is_virtual;
  unsigned char run_id_valid;
  unsigned char has_db_record;
  unsigned char is_checked;
  int run_id_first;
  int run_id_last;
  int last_change_user_id;
  ej_time64_t start_time;
  ej_time64_t stop_time;
  ej_time64_t last_change_time;
  unsigned char pad2[16];
};

_Static_assert(sizeof(struct user_run_header_info) == 64, "user_run_header_info must have size 64");

struct user_run_header_state
{
  // range of users
  int low_user_id;
  int high_user_id;
  uint32_t *umap;    // indices in infos array
  int size;          // number of users
  int reserved;      // reserved in infos
  struct user_run_header_info *infos; // user infos
};

struct runlog_state
{
  RUNS_ACCESS struct run_header  head;
  RUNS_ACCESS struct run_entry  *runs;
  RUNS_ACCESS int                run_f;  // first run loaded, runs[0] is information for run run_f
  RUNS_ACCESS int                run_u;
  RUNS_ACCESS int                run_a;
  teamdb_state_t     teamdb_state;

  // timestamp of the last change with microsecond precision
  long long last_update_time_us;

  struct user_flags_info_s user_flags; // banned/invisible/locked flags for users

  int max_user_id;
  int user_count;

  int run_extra_f;  // first index offset, i.e. run_extras[0] is actually index for run id run_extra_f, see also run_f
  int run_extra_u, run_extra_a;
  struct run_entry_extra *run_extras; /* run indices */

  // UUID hash information
  int uuid_hash_state; // -1 - disabled, 0 - not built, 1 - ok
  int uuid_hash_size;  // the size of the hash table
  int uuid_hash_used;  // the number of entries in the table
  struct uuid_hash_entry *uuid_hash;
  int uuid_hash_last_added_run_id;
  int uuid_hash_last_added_index;

  // userrunheader information
  struct user_run_header_state urh;

  // the managing plugin information
  struct rldb_plugin_iface *iface;
  struct rldb_plugin_data *data;
  struct rldb_plugin_cnts *cnts;
};

void
run_extend_user_run_header_map(
        runlog_state_t state,
        int user_id);

struct user_run_header_info *
run_get_user_run_header(
        runlog_state_t state,
        int user_id,
        int *p_is_created);

struct user_run_header_info *
run_try_user_run_header(
        runlog_state_t state,
        int user_id);

#endif /* __RUNLOG_STATE_H__ */
