# -*- Makefile -*-

# Copyright (C) 2022 Alexander Chernov <cher@ejudge.ru> */

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

PLUGINDIR = $(libexecdir)/ejudge/plugins

AVATAR_MYSQL_CFILES = avatar_mysql.c

CFILES = $(AVATAR_MYSQL_CFILES)
HFILES =

CC = gcc
LD = gcc

CFLAGS = -I. -I../.. -I../../include $(MYSQL_INCL_OPT) $(EXPAT_INCL_OPT) $(CDEBUGFLAGS) $(CCOMPFLAGS) $(CEXTRAFLAGS) $(WPTRSIGN)
LDFLAGS = $(MYSQL_LIB_OPT) $(EXPAT_LIB_OPT) $(CDEBUGFLAGS) $(LDCOMPFLAGS) $(LDEXTRAFLAGS)
LDLIBS = $(EXTRALIBS) $(MYSQL_LIBS) -lexpat -lm

PLUGINS = avatar_mysql.so

all : $(PLUGINS)

install : $(PLUGINS)
	install -d "${DESTDIR}${PLUGINDIR}"
	install -m 0755 $(PLUGINS) "${DESTDIR}${PLUGINDIR}"

clean :
	-rm -f *.so *.o deps.make

distclean : clean
	-rm -f Makefile

deps.make : $(CFILES) $(HFILES)
	../../cdeps -v AVATAR_MYSQL_OFILES -I ../.. -I ../../include -g -c '$$(CC) $$(CFLAGS) -DPIC -fPIC' $(AVATAR_MYSQL_CFILES) > deps.make

include deps.make

avatar_mysql.so : $(AVATAR_MYSQL_OFILES)
	$(LD) -shared $(LDFLAGS) $^ -o $@ $(LDLIBS)
