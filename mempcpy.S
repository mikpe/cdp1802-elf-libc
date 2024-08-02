# mempcpy.S
# Copyright (C) 2024  Mikael Pettersson <mikpelinux@gmail.com>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.

#include "asm-macros.h"

/* void *mempcpy(void *dst, const void *src, size_t n);
 */

#define DST	ARG0
#define SRC	ARG1
#define N	ARG2

BEGINF	mempcpy
	lbr	1f

0:	;; *DST++ = *SRC++, --N
	lda	SRC
	str	DST
	inc	DST
	dec	N

1:	;; if (N != 0) goto 0b
	glo	N
	lbnz	0b
	ghi	N
	lbnz	0b

	;; return with final DST in ARG0
	RET
ENDF	mempcpy
