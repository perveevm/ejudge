/* -*- mode: c; c-basic-offset: 4 -*- */
#ifndef __VARIANT_PLUGIN_H__
#define __VARIANT_PLUGIN_H__

/* Copyright (C) 2022 Alexander Chernov <cher@ejudge.ru> */

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

#include "ejudge/common_plugin.h"

#include <stdio.h>

#define VARIANT_PLUGIN_IFACE_VERSION 1

// the plugin state
struct variant_plugin_data
{
    struct common_plugin_data b;
};

struct variant_plugin_iface;

// the contest-specific plugin state
struct variant_cnts_plugin_data
{
    struct variant_plugin_iface *vt;
};

struct ejudge_cfg;
struct contest_desc;
struct section_global_data;
struct serve_state;

struct variant_plugin_iface
{
    struct common_plugin_iface b;
    int variant_version;

    struct variant_cnts_plugin_data * (*open)(
        struct common_plugin_data *data,
        FILE *log_f,
        const struct ejudge_cfg *config,
        const struct contest_desc *cnts,
        const struct serve_state *state,
        int flags);
    struct variant_cnts_plugin_data * (*close)(
        struct variant_cnts_plugin_data *data);
    int (*find_variant)(
        struct variant_cnts_plugin_data *data,
        const struct serve_state *state,
        int user_id,
        int prob_id,
        int *p_virtual_variant);
    int (*find_user_variant)(
        struct variant_cnts_plugin_data *data,
        const struct serve_state *state,
        int user_id,
        int *p_virtual_variant);
    int (*get_entry_count)(
        struct variant_cnts_plugin_data *data);
    int (*get_keys)(
        struct variant_cnts_plugin_data *data,
        int *p_count,
        int64_t **p_keys);
    unsigned char *(*get_login)(
        struct variant_cnts_plugin_data *data,
        int64_t key);
    int (*get_user_variant)(
        struct variant_cnts_plugin_data *data,
        int64_t key,
        int *p_virtual_variant);
    int (*get_problem_ids)(
        struct variant_cnts_plugin_data *data,
        int *p_count,
        int **p_ids);
    int (*get_variant)(
        struct variant_cnts_plugin_data *data,
        int64_t key,
        int prob_id);
    int (*upsert_user_variant)(
        struct variant_cnts_plugin_data *data,
        const unsigned char *login,
        int variant,
        int virtual_variant,
        int64_t *p_key);
    int (*upsert_variant)(
        struct variant_cnts_plugin_data *data,
        const unsigned char *login,
        int prob_id,
        int variant);
};

struct variant_cnts_plugin_data *
variant_plugin_open(
        FILE *log_f,
        const struct ejudge_cfg *config,
        const struct contest_desc *cnts,
        const struct serve_state *state,
        const unsigned char *plugin_name,
        int flags);

#endif /* __VARIANT_PLUGIN_H__ */
