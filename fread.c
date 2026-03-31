/* fread.c
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

#include <stdio.h>
#include "xlibio.h"

size_t fread(void *ptr, size_t size, size_t n, FILE *stream)
{
    /* If not stdin, error.  */
    if (stream != &__libc_stdin) {
	stream->flags |= F_ERR;
	return 0;
    }

    /* If we'd read 0 bytes, return 0.  */
    if (size == 0 || n == 0)
	return 0;

    /* If we have a byte of pushback, consume it.  If the item size
       is 1, we will have read one item.  */
    if (stream->flags & F_UNGETC) {
	stream->flags &= ~F_UNGETC;
	*(unsigned char*)ptr = stream->ungetc;
	if (size == 1) {
	    if (n != 1)
		stream->flags |= F_EOF;
	    return 1;
	}
    }

    /* EOF before the first complete item.  */
    stream->flags |= F_EOF;
    return 0;
}
