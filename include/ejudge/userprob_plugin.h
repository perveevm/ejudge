/* -*- mode: c; c-basic-offset: 4 -*- */
#ifndef __USERPROB_PLUGIN_H__
#define __USERPROB_PLUGIN_H__

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

#include <stdint.h>

#define USERPROB_PLUGIN_IFACE_VERSION 1

struct userprob_entry
{
    int64_t serial_id;
    int64_t create_time_us;
    int64_t last_change_time_us;
    unsigned char *lang_name;
    unsigned char *hook_id;
    unsigned char *gitlab_token;
    unsigned char *vcs_type;
    unsigned char *vcs_url;
    unsigned char *vcs_subdir;
    unsigned char *vcs_branch_spec;
    unsigned char *ssh_private_key;
    unsigned char *last_event;
    unsigned char *last_revision;
    unsigned char *message;
    int contest_id;
    int user_id;
    int prob_id;
};

struct userprob_plugin_iface;

struct userprob_plugin_data
{
    struct common_plugin_data b;
    struct userprob_plugin_iface *vt;
};

struct userprob_plugin_iface
{
    struct common_plugin_iface b;
    int userprob_version;

    int (*open)(
        struct userprob_plugin_data *data);
    struct userprob_entry *(*fetch_by_hook_id)(
        struct userprob_plugin_data *data,
        const unsigned char *hook_id);
    struct userprob_entry *(*fetch_by_serial_id)(
        struct userprob_plugin_data *data,
        int64_t serial_id);
    struct userprob_entry *(*fetch_by_cup)(
        struct userprob_plugin_data *data,
        int contest_id,
        int user_id,
        int prob_id);
    struct userprob_entry *(*create)(
        struct userprob_plugin_data *data,
        int contest_id,
        int user_id,
        int prob_id);
    int (*save)(
        struct userprob_plugin_data *data,
        int64_t serial_id,
        const struct userprob_entry *ue);
    int (*remove)(
        struct userprob_plugin_data *data,
        int64_t serial_id);
};

struct userprob_entry *
userprob_entry_free(struct userprob_entry *ue);

struct ejudge_cfg;
struct contest_desc;
struct serve_state;

struct userprob_plugin_data *
userprob_plugin_get(
        const struct ejudge_cfg *config,
        const unsigned char *plugin_name,
        int flags);

#endif /* __SUBMIT_PLUGIN_H__ */
