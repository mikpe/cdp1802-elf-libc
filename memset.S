# memset.S
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

/* void *memset(void *s, int c, size_t n);
 */

#define S	ARG0
#define C	ARG1
#define N	ARG2
#define TMP	ARG3

/* This sets up a pointer to the end of the destination area and
   writes to it backwards using STXD, for a cost of 13 instructions
   in the setup and 7 instructions per loop iteration.

   The alternative of writing forwards would require 5 instructions
   in the setup and 8 instructions per loop iteration.

   So this version wins for N > 8.  */

BEGINF	memset
	;; TMP = &S[N] - 1
	glo	N
	str	SP
	glo	S
	add
	plo	TMP
	ghi	N
	str	SP
	ghi	S
	adc
	phi	TMP
	dec	TMP

	sex	TMP
	lbr	1f

0:	;; *TMP-- = C, --N
	glo	C
	stxd
	dec	N

1:	;; if (N != 0) goto 0b
	glo	N
	lbnz	0b
	ghi	N
	lbnz	0b

	;; return with S still in ARG0
	RET
ENDF	memset
