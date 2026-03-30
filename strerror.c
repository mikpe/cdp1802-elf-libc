/* strerror.c
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
#include <string.h>

char *strerror(int errnum)
{
    /* Buffer for "errno ", a 16-bit decimal integer
       with optional sign, and terminating NUL.  */
    static char buf[6 + 1 + 5 + 1];

    /* TODO: factor out conversion from _putint() and
       ensure its output always starts at given buf+0 */
    snprintf(buf, sizeof buf, "errno %d", errnum);
    return buf;
}
