/* fcntl.h
   Copyright (C) 2024-2026  Mikael Pettersson <mikpelinux@gmail.com>

   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef _FCNTL_H
#define _FCNTL_H

#include <sys/cdefs.h>

__BEGIN_DECLS

#define O_ACCMODE	0003
#define O_RDONLY	00
#define O_WRONLY	01
#define O_RDWR		02
#define O_CREAT		00100
#define O_EXCL		00200
#define O_TRUNC		01000

#define F_SETFD		2	/* get/clear close_on_exec */

int fcntl(int fd, int op, ...);

__END_DECLS

#endif /* !_FCNTL_H */
