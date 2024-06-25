# asm-macros.h
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

#define SP	2
#define PC	3
#define CALL	4
#define RETN	5
#define LINK	6
#define ARG0	7
#define ARG1	8
#define ARG2	9

.macro	BEGINF	name
	.text
	.global	\name
	.type	\name, @function
\name:
.endm

.macro	ENDF	name
	.size	\name, .-\name
.endm

.macro	RET
	sep	RETN
.endm
