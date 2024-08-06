/* qsort.c
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

#include <stddef.h>
#include <stdint.h>
#include "xlibc.h"

/* FIXME: rewrite in assembler */

static void swap(unsigned char *a, unsigned char *b, size_t nrbytes)
{
    do {
	unsigned char tmp = *a;
	*a++ = *b;
	*b++ = tmp;
    } while (--nrbytes != 0);
}

/* This is bubble sort, with an optimization suggested by its Wikipedia article.
 */
void qsort(void *base, size_t nelts, size_t eltsz, int (*compar)(const void *, const void *))
{
    unsigned char *prev, *here;
    size_t count, count_at_last_swap;
    struct mulovf mulovf;

    if (nelts == 0 || eltsz == 0)
	return;

    mulovf = _mulovf(nelts, eltsz);
    if (mulovf.overflow)
	return;

    while (nelts != 0) {
	count_at_last_swap = nelts;
	prev = (unsigned char *) base;

	for (count = nelts; --count != 0;) {
	    here = prev + eltsz;
	    if ((*compar)(prev, here) > 0) {
		swap(prev, here, eltsz);
		count_at_last_swap = count;
	    }
	    prev = here;
	}

	nelts -= count_at_last_swap;
    }
}
