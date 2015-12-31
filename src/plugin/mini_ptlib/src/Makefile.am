# Makefile.am
# Automake file for mini_ptlib
#
# $Id: Makefile.am,v 1.31 2000/09/19 17:22:09 gram Exp $
#
# Ethereal - Network traffic analyzer
# By Gerald Combs <gerald@zing.org>
# Copyright 1998 Gerald Combs
#
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


ACLOCAL_AMFLAGS = `../aclocal-flags`

INCLUDES = $(all_includes) -I/usr/lib/glib/include -I../.. -D MINI_PTLIB -D HAVE_SYS_TIME_H 

#LDFLAGS = -shared -Wl,-soname,
# gcc -shared -Wl,-soname,$(LIB_BASENAME).1 -o $(LIBDIR)/$(LIBNAME_PAT) $(OBJS)    

CXX = g++

noinst_LIBRARIES = libmini_ptlib.a

CLEANFILES = \
	libmini_ptlib.a		\
	*~

libmini_ptlib_a_SOURCES = \
	args.cxx  \
	asner.cxx  \
	assert.cxx  \
	collect.cxx  \
	contain.cxx  \
	object.cxx  \
	mini_ptlib.h \
	args.h \
	args.h \
	asner.h \
	contain.inl \
	lists.h  \
	osutil.inl \
	array.h  \
	contain.h  \
	dict.h   \
	object.h \
	pstring.h 


