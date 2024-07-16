# strlen.S
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

/* size_t strlen(const char *s);
 */

#define S	ARG0
#define N	ARG1

BEGINF	strlen
	;; N = -1
	ldi	0xff
	plo	N
	phi	N

	;; do N++ while (*S++ != 0)
0:	inc	N
	lda	S
	lbnz	0b

	;; return N
	glo	N
	plo	ARG0
	ghi	N
	phi	ARG0
	RET
ENDF	strlen
