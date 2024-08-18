# strnlen.S
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

/* size_t strnlen(const void *s, size_t n);
 */

#define S	ARG0
#define N	ARG1
#define LEN	ARG2

BEGINF	strnlen
	ldi	0
	plo	LEN
	phi	LEN
	lbr	1f

0:	;; if (*S++ == 0) goto 9f
	lda	S
	lbz	9f

	inc	LEN
	dec	N

1:	;; if (N != 0) goto 0b
	glo	N
	lbnz	0b
	ghi	N
	lbnz	0b

9:	;; return LEN
	glo	LEN
	plo	ARG0
	ghi	LEN
	phi	ARG0
	RET
ENDF	strnlen
