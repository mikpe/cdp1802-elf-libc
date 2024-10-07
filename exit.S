# exit.S
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

/* void exit(int status);
 *
 * Eventually this should close stdio streams and call atexit handlers,
 * but for now just run destructors and tailcall _exit().
 */

BEGINF	exit
	glo	ARG0
	stxd
	ghi	ARG0
	stxd
	sep	CALL
	.hword	__libc_fini_array
	inc	SP
	lda	SP
	phi	ARG0
	ldn	SP
	plo	ARG0
	lbr	_exit
ENDF	exit
