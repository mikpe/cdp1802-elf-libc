/* malloc.c
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
#include <stddef.h>
#include <stdint-gcc.h>
#include "xmalloc.h"

extern char _end[];	/* linker symbol for end of BSS */
static char *cur_brk = _end;

/* void *sbrk(ptrdiff_t increment);
 *
 * As this runs on bare metal it simply maintains a high water mark for
 * the heap.  It rejects shrinking the heap as that would break malloc(),
 * and it tries to avoid the heap growing too close to the stack.
 */

static void *sbrk(ptrdiff_t increment)
{
    uintptr_t old_brk, new_brk, max_brk;

    if (increment < 0) {
	errno = EINVAL;
	return (void *) -1;
    }

    old_brk = (uintptr_t) cur_brk;
    new_brk = old_brk + increment;
    if (new_brk < old_brk) {	/* wraparound? */
	errno = ENOMEM;
	return (void *) -1;
    }

    max_brk = (uintptr_t) __builtin_stack_address() - 1024;
    if (new_brk > max_brk) {
	errno = ENOMEM;
	return (void *) -1;
    }

    cur_brk = (char *) new_brk;
    return (void *) old_brk;
}

struct header *_malloc_freep;

static void *morecore(size_t nrbytes)
{
    struct header *hp;

    hp = sbrk(nrbytes);
    if (hp == (void *) -1)
	return NULL;

    hp->nrbytes = nrbytes;
    return &hp->u.data;
}

void *malloc(size_t nrbytes)
{
    struct header **pblock, *block;

    if (nrbytes < sizeof(struct header))
	nrbytes = sizeof(struct header);

    for (pblock = &_malloc_freep; (block = *pblock) != NULL; pblock = &block->u.next) {
	if (block->nrbytes >= nrbytes) {
	    /* we'll allocate from this block */
	    size_t split_nrbytes = block->nrbytes - nrbytes;
	    if (split_nrbytes < sizeof(struct header)) {
		/* block too small to split, unlink it */
		*pblock = block->u.next;
	    } else {	/* allocate tail end */
		/* split block, return tail */
		block->nrbytes = split_nrbytes;
		block = (struct header *) ((char *) block + split_nrbytes);
		block->nrbytes = nrbytes;
	    }
	    return &block->u.data;
	}
    }
    return morecore(nrbytes);
}
