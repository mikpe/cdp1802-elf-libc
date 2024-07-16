# strrchr.S
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

/* char *strchr(const char *s, int c);
 */

#define S	ARG0
#define C	ARG1
#define P	ARG2

BEGINF	strrchr
	ldi	0	; set P = NULL
	plo	P
	phi	P

	sex	S

0:	;; if (*S == C) P = S
	glo	C
	xor
	lbnz	1f
	glo	S
	plo	P
	ghi	S
	phi	P

1:	;; if (*S++ != 0) goto 0b
	lda	S
	lbnz	0b

	;; return P
	glo	P
	plo	ARG0
	ghi	P
	phi	ARG0
	RET
ENDF	strrchr
