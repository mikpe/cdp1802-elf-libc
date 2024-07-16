/* free.c
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
#include "xmalloc.h"

void free(void *ptr)
{
    struct header *prev, *next, *block;

    if (ptr == NULL)
	return;

    block = (struct header *) ((char *) ptr - offsetof(struct header, u.data));

    prev = _malloc_freep;

    /* check if block should be inserted at the head of the free list */
    if (prev == NULL || block < prev) {
	block->u.next = prev;
	_malloc_freep = block;
	return;
    }

    for (;;) {
	/* INV: prev != NULL && prev < block */
	next = prev->u.next;
	if (next == NULL) {
	    /* end of free list, insert block after prev */
	    if ((char *) prev + prev->nrbytes == (char *) block) {
		/* merge prev and block */
		prev->nrbytes += block->nrbytes;
	    } else {
		/* link block after prev */
		block->u.next = NULL;
		prev->u.next = block;
	    }
	    return;
	}
	if (next > block) {
	    /* insert block between prev and next */
	    if ((char *) prev + prev->nrbytes == (char *) block) {
		if ((char *) block + block->nrbytes == (char *) next) {
		    /* merge prev, block, and next */
		    prev->nrbytes += block->nrbytes + next->nrbytes;
		    prev->u.next = next->u.next;
		} else {
		    /* merge prev and block */
		    prev->nrbytes += block->nrbytes;
		}
	    } else if ((char *) block + block->nrbytes == (char *) next) {
		/* merge block and next */
		block->nrbytes += next->nrbytes;
		block->u.next = next->u.next;
		prev->u.next = block;
	    } else {
		/* link block between prev and next */
		block->u.next = next;
		prev->u.next = block;
	    }
	    return;
	}
	prev = next;
    }
}
