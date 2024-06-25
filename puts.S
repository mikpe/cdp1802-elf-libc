# puts.S
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

/* int puts(const char *s);
 *
 * TODO: rewrite this in C once gcc generates good enough code.
 */

BEGINF	puts
	;; s is in ARG0
	lbr	1f

0:	;; [X=ARG0] putchar(*s++)
	sex	ARG0
	out	6	; latch *s++
	sex	PC
	out	7	; issue command, immediate
	.byte	0xE0	; code for PUTCHAR

1:	;; if (*s != '\0') goto 0b
	ldn	ARG0
	lbnz	0b

	;; putchar('\n')
	sex	PC
	out	6	; latch character, immediate
	.byte	'\n'
	out	7	; issue command, immediate
	.byte	0xE0	; code for PUTCHAR

	;; return with a non-negative value in ARG0
	phi	ARG0	; D is zero, clear ARG0 upper half
	RET
ENDF	puts
