/* fdopen.c
   Copyright (C) 2026  Mikael Pettersson <mikpelinux@gmail.com>

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

#include <errno.h>
#include <stdio.h>
#include "xlibio.h"

/* We don't pretend to be POSIX, but libstdc++ requires some POSIX symbols.  */

FILE *fdopen(int fd, const char *mode)
{
    FILE *fp;

    /* Allow "rb?" for fd 0 and "[wa]b?" for fds 1/2.  */
    if (fd == 0 && mode[0] == 'r') {
	fp = &__libc_stdin;
    } else if ((fd == 1 || fd == 2) && (mode[0] == 'w' || mode[0] == 'a')) {
	fp = (fd == 1) ? &__libc_stdout : &__libc_stderr;
    } else {
	errno = EBADF;
	return NULL;
    }

    /* mode[0] is checked, now check that mode[1..] is "b?".  */
    if (mode[1] == '\0' || (mode[1] == 'b' && mode[2] == '\0')) {
	fp->flags = 0;	/* clear eof, err, and ungetc */
	return fp;
    }

    errno = EINVAL;
    return NULL;
}
