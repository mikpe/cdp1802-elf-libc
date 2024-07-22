/* xlibio.h
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

/* Internal declarations shared by stdio-related components. */

#include <stdbool.h>

/* A stdio running on bare metal:
 * - input can only come from strings, never files
 * - external output can only go to the console
 * - buffering is not needed
 *
 * printf() et al:
 * - output can go to the console (stdout or stderr) or a string
 * - output generation continues after output string is full
 */

struct __FILE {		/* only the address of the FILE is significant */
    char _filler;
};

/* true if the FILE is stdout or stderr, false otherwise */
bool _is_console(const FILE *);

struct odev {
    char *s;	/* write position in string, NULL if console */
    size_t n;	/* remaining size if string, > 0 if console */
};

void _putc(struct odev *, char c);
void _write(struct odev *, const char *s, size_t n);
