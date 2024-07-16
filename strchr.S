# strchr.S
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

BEGINF	strchr
	sex	S

0:	;; if (*S == C) return S
	glo	C
	xor
	lbz	1f

	;; if (*S++ != 0) goto 0b
	lda	S
	lbnz	0b

	;; return NULL
	plo	ARG0
	phi	ARG1

1:	RET
ENDF	strchr
