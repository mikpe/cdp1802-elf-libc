/* xmalloc.h
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

/* Internal declarations shared by malloc-related components. */

/*
 * A simple malloc() somewhat inspired by K&R's:
 *
 * - Every block records its size as meta-data, stored before the data.
 * - Every free block links to the next free block, using a pointer stored
 *   at the start of the data.
 * - The free list is sorted by address.
 * - malloc() uses a first-fit search to find a free block.
 * - The heap is grown by sbrk().
 * - free() finds the appropriate place to insert the freed block,
 *   merging it with the lower or higher neighbour if possible.
 */

struct header {
    size_t nrbytes;		/* size of block in bytes, minimum sizeof(struct header) */
    union {
	struct header *next;	/* pointer to next free block (when freed) */
	char data[1];		/* user's data (when in use) */
    } u;
};

extern struct header *_malloc_freep;
