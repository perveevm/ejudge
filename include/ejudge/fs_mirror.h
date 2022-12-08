/* -*- mode: c; c-basic-offset: 4 -*- */

#ifndef __FS_MIRROR_H__
#define __FS_MIRROR_H__

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

struct fs_mirror_state;
struct AgentClient;

struct fs_mirror_state *fs_mirror_create(void);
struct fs_mirror_state *fs_mirror_free(struct fs_mirror_state *ms);

void
fs_mirror_set_mirror_dir(
        struct fs_mirror_state *ms,
        const unsigned char *dir);
void
fs_mirror_set_agent_client(struct AgentClient *ac);

#endif /* __FS_MIRROR_H__ */
