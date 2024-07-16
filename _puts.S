# _puts.S
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

/* void _puts(const char *s);
 *
 * Output the string S to the console, without trailing newline.
 */

#define S ARG0

BEGINF	_puts
	lbr	1f

0:	;; [X=S] putchar(*s++)
	sex	S
	out	6	; latch *s++
	sex	PC
	out	7	; issue command, immediate
	.byte	0xE0	; code for PUTCHAR

1:	;; if (*s != '\0') goto 0b
	ldn	S
	lbnz	0b

	RET
ENDF	_puts
