# strncpy.S
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

/* char *strncpy(char *dst, const char *src, size_t n);
 */

#define DST	ARG0
#define SRC	ARG1	/* first loop */
#define NUL	ARG1	/* second loop */
#define N	ARG2
#define TMP	ARG3

BEGINF	strncpy
	;; TMP = DST
	ghi	DST
	phi	TMP
	glo	DST
	plo	TMP
	lbr	1f

0:	;; C = *SRC++, *TMP++ = C, --N
	lda	SRC
	str	TMP
	inc	TMP
	dec	N

	;; if (C == '\0') goto 2f
	lbz	2f

1:	;; if (N != 0) goto 0b
	glo	N
	lbnz	0b
	ghi	N
	lbnz	0b

	;; N == 0 so skip nul-padding loop
	lbr	9f

2:	;; NUL = 0
	plo	NUL
	lbr	4f

3:	;; *TMP++ = NUL, --N
	glo	NUL	; this is smaller & cheaper than 'ldi 0'
	str	TMP
	inc	TMP
	dec	N

4:	;; if (N != 0) goto 3b
	glo	N
	lbnz	3b
	ghi	N
	lbnz	3b

9:	;; return with DST still in ARG0
	RET
ENDF	strncpy
