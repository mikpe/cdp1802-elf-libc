/* fseek.c
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

int fseek(FILE *stream, long offset, int whence)
{
    /* Our files are non-seekable and we don't track current offset.
       Allow offset 0 with any value for whence.  */
    if (offset == 0) {
	stream->flags = 0;	/* clear eof, error, and ungetc flags */
	return 0;
    }
    errno = ESPIPE;
    return -1;
}
