/* sys/stat.h
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

#ifndef _SYS_STAT_H
#define _SYS_STAT_H

#include <sys/cdefs.h>

__BEGIN_DECLS

struct stat {
    int st_dev;
    int st_ino;
    int st_nlink;
    int st_mode;
    int st_size;
    int st_mtime;
};

#define S_IWUSR		0200	/* Write by owner.  */

int fstat(int fd, struct stat *statbuf);
int stat(const char *pathname, struct stat *statbuf);

__END_DECLS

#endif /* !_SYS_STAT_H */
