/* -*- mode: c -*- */

/* Copyright (C) 2006-2023 Alexander Chernov <cher@ejudge.ru> */

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

#include "ejudge/config.h"
#include "ejudge/ej_types.h"
#include "ejudge/version.h"
#include "ejudge/startstop.h"
#include "ejudge/pathutl.h"
#include "ejudge/errlog.h"

#include "ejudge/xalloc.h"
#include "ejudge/osdeps.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>

static path_t self_exe;
static char **self_argv;
static sigset_t init_sigmask;

void
start_set_self_args(int argc, char *argv[])
{
  int n;

  if ((n = readlink("/proc/self/exe", self_exe, sizeof(self_exe))) <= 0) {
    fprintf(stderr, "%s: cannot access /proc/self/exe: %s\n",
            argv[0], os_ErrorMsg());
    snprintf(self_exe, sizeof(self_exe), "%s", argv[0]);
  } else {
    self_exe[n] = 0;
  }
  self_argv = argv;
  self_argv[0] = self_exe;
  sigprocmask(SIG_SETMASK, 0, &init_sigmask);
}

int
start_switch_user(const unsigned char *user, const unsigned char *group)
{
  struct passwd *pwinfo = 0;
  struct group *grinfo = 0;

  if (user && !*user) user = 0;
  if (group && !*group) group = 0;

  if (!user && !getuid()) {
    fprintf(stderr,
            "Error: user is not specified\n"
            "Note: since you've invoked program as the root user, you must\n"
            "  specify an unprivileged user login and group to run as.\n"
            "  The program will not run with the root privileges!\n");
    return -1;
  }
  if (!group) group = user;
  if (user && !(pwinfo = getpwnam(user))) {
    fprintf(stderr, "Error: no such user: %s\n", user);
    return -1;
  }
  if (group && !(grinfo = getgrnam(group))) {
    fprintf(stderr, "Error: no such group: %s\n", group);
    return -1;
  }
  if (group && setgid(grinfo->gr_gid) < 0) {
    fprintf(stderr, "Error: cannot change gid: %s\n", os_ErrorMsg());
    return -1;
  }
  if (user && setuid(pwinfo->pw_uid) < 0) {
    fprintf(stderr, "Error: cannot change uid: %s\n", os_ErrorMsg());
    return -1;
  }
  return 0;
}

int
start_prepare(const unsigned char *user, const unsigned char *group,
              const unsigned char *workdir)
{
  if (start_switch_user(user, group) < 0) return -1;

  if (workdir && *workdir) {
    if (chdir(workdir) < 0) {
      fprintf(stderr, "Error: cannot change directory to %s\n", workdir);
      return -1;
    }
  }
  return 0;
}

void
start_restart(void)
{
  sigprocmask(SIG_SETMASK, &init_sigmask, 0);
  execv(self_exe, self_argv);
}

void
start_set_args(char *argv[])
{
  self_argv = argv;
  self_argv[0] = self_exe;
}

static int
get_process_name(unsigned char *buf, size_t size, int pid)
{
  unsigned char path[PATH_MAX];
  if (snprintf(path, sizeof(path), "/proc/%d/cmdline", pid) >= (int) sizeof(path)) {
    return -1;
  }
  int fd = open(path, O_RDONLY, 0);
  if (fd < 0) {
    return -1;
  }
  unsigned char cmdbuf[PATH_MAX];
  int r = read(fd, cmdbuf, sizeof(cmdbuf));
  if (r < 0 || r == sizeof(cmdbuf)) {
    close(fd);
    return -1;
  }
  cmdbuf[r] = 0;
  unsigned char *p = strrchr(cmdbuf, '/');
  if (p) {
    ++p;
  } else {
    p = cmdbuf;
  }
  r = snprintf(buf, size, "%s", p);
  close(fd);
  return r;
}

int
start_find_process(const unsigned char *name, int *p_uid)
{
  DIR *d = 0;
  struct dirent *dd;
  char *eptr;
  int pid, mypid;
  int retval = -1;
  unsigned char cmdname[PATH_MAX];

  mypid = getpid();

  if (!(d = opendir("/proc"))) goto cleanup;
  retval = 0;
  while ((dd = readdir(d))) {
    eptr = 0; errno = 0;
    pid = strtol(dd->d_name, &eptr, 10);
    if (errno || *eptr || eptr == dd->d_name || pid <= 0 || pid == mypid)
      continue;
    if (get_process_name(cmdname, sizeof(cmdname), pid) <= 0)
      continue;
    if (!strcmp(name, cmdname)) {
      retval = pid;
      // FIXME: get the actual uid
      if (p_uid) *p_uid = getuid();
      goto cleanup;
    }
  }
  closedir(d); d = 0;

 cleanup:
  if (d) closedir(d);
  return retval;
}

int
start_find_all_processes(const unsigned char *name, int **p_pids)
{
  DIR *d = 0;
  struct dirent *dd;
  char *eptr;
  int pid, mypid;
  int a = 0, u = 0;
  int *pids = NULL;
  unsigned char cmdname[PATH_MAX];

  mypid = getpid();

  if (!(d = opendir("/proc"))) return -1;
  while ((dd = readdir(d))) {
    eptr = 0; errno = 0;
    pid = strtol(dd->d_name, &eptr, 10);
    if (errno || *eptr || eptr == dd->d_name || pid <= 0 || pid == mypid)
      continue;
    if (get_process_name(cmdname, sizeof(cmdname), pid) <= 0)
      continue;
    if (!strcmp(name, cmdname)) {
      if (u >= a) {
        if (!a) a = 4;
        XREALLOC(pids, a);
      }
      pids[u++] = pid;
    }
  }
  closedir(d); d = 0;

  *p_pids = pids;
  return u;
}

int
start_kill(int pid, int op)
{
  int signum = 0;
  switch (op) {
  case START_RESTART: signum = SIGHUP; break;
  case START_STOP: signum = SIGTERM; break;
  case START_ROTATE: signum = SIGUSR1; break;
  }
  return kill(pid, signum);
}

int
start_daemon(const unsigned char *log_path)
{
  int pid;

  if (start_open_log(log_path) < 0)
    return -1;

  if ((pid = fork()) < 0) return -1;
  if (pid > 0) _exit(0);
  if (setsid() < 0) return -1;

  return 0;
}

int
start_open_log(const unsigned char *log_path)
{
  int log_fd = -1;

  if (!log_path) log_path = "/dev/null";
  if ((log_fd = open(log_path, O_WRONLY | O_CREAT | O_APPEND | O_LARGEFILE, 0600)) < 0) {
    err("cannot open log file `%s'", log_path);
    return -1;
  }
  close(0);
  if (open("/dev/null", O_RDONLY) < 0) return -1;
  close(1);
  if (open("/dev/null", O_WRONLY) < 0) return -1;
  close(2); dup(log_fd); close(log_fd);
  return 0;
}

void
start_shutdown(const unsigned char *command)
{
  execlp(command, command, NULL);
  err("cannot execute shutdown command '%s'", command);
  exit(1);
}

int
start_stop_and_wait(
        const unsigned char *program_name,
        const unsigned char *process_name,
        const unsigned char *signame,
        int signum,
        long long timeout_us)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  long long t1 = tv.tv_sec * 1000000LL + tv.tv_usec;
  int signals_sent = 0;
  while (1) {
    int *pids = NULL;
    int pid_count = start_find_all_processes(process_name, &pids);
    if (pid_count < 0) {
      fprintf(stderr, "%s: cannot get the list of processes from /proc\n",
              program_name);
      return -1;
    }
    if (!pid_count) {
      break;
    }
    if (!signals_sent) {
      fprintf(stderr, "%s: %s is running as pids", program_name, process_name);
      for (int i = 0; i < pid_count; ++i) {
        fprintf(stderr, " %d", pids[i]);
      }
      fprintf(stderr, "\n");
      fprintf(stderr, "%s: sending the %s signal\n", program_name, signame);
      for (int i = 0; i < pid_count; ++i) {
        start_kill(pids[i], signum);
      }
      signals_sent = 1;
    }
    free(pids); pids = NULL;
    gettimeofday(&tv, NULL);
    long long t2 = tv.tv_sec * 1000000LL + tv.tv_usec;
    if (timeout_us > 0 && t1 + timeout_us <= t2) {
      fprintf(stderr, "%s: wait timed out\n", program_name);
      return -1;
    }
    usleep(100000);
  }
  return 0;
}

