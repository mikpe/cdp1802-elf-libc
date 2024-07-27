/* fputs.c
   Copyright (C) 2024  Mikael Pettersson <mikpelinux@gmail.com>

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
#include "xlibc.h"
#include "xlibio.h"

int fputs(const char *s, FILE *stream)
{
    if (!_is_console(stream)) {
	errno = EINVAL;
	return EOF;
    }
    /* TODO: change _puts() to clear ARG0 upper half on return,
       then we could just tailcall it here */
    _puts(s);
    return 1;
}
