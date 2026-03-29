/* unistd.h
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

#ifndef _UNISTD_H
#define _UNISTD_H

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <sys/types.h>
#include <stddef.h>

int dup(int oldfd);
void _exit(int status) __attribute__((__noreturn__));
int close(int fd);
int getpid(void);
int isatty(int fd);
off_t lseek(int fd, off_t offset, int whence);
int open(const char *path, int flags, ...);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

__END_DECLS

#endif /* !_UNISTD_H */
