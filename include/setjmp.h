/* setjmp.h
   Copyright (C) 2024  Mikael Pettersson <mikpelinux@gmail.com>

   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef _SETJMP_H
#define _SETJMP_H

#define _JB_SIZE 7	/* SP, previous LINK, LINK, r12-r15 */

typedef unsigned int jmp_buf[_JB_SIZE];

void longjmp(jmp_buf env, int val);
int setjmp(jmp_buf env);

#endif /* !_SETJMP_H */
