# _exit.S
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

/* void _exit(int status); */

BEGINF	_exit
	glo	ARG0	; fetch low byte of exit status
	dec	SP
	str	SP	; .. and push it
	out	6	; pop exit status and latch it
	sex	PC
	out	7	; issue command, immediate
	.byte	0x00	; code for HALT
ENDF	_exit
