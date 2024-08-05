/* assert.h
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

#ifndef _ASSERT_H
#define _ASSERT_H

#undef assert

#ifdef NDEBUG

#define assert(expr)	((void) 0)

#else /* !NDEBUG */

void _assert(const char *);

#define _ASSERT_STR2(x) #x
#define _ASSERT_STR(x) _ASSERT_STR2(x)

#define assert(expr) ((expr) ? (void) 0 : _assert(__FILE__ ":" _ASSERT_STR(__LINE__) " " #expr))

#endif /* !NDEBUG */

#endif /* !_ASSERT_H */
