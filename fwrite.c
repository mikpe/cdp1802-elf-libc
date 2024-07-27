/* fwrite.c
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

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    struct mulovf res;
    struct odev o;

    res = _mulovf(nmemb, size);
    if (res.overflow) {
	errno = EINVAL;
	return 0;
    }

    if (!_is_console(stream)) {
	errno = EINVAL;
	return 0;
    }

    o.s = NULL;
    o.n = 1;

    _write(&o, ptr, res.product);

    return nmemb;
}
