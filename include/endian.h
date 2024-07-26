/* endian.h
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

#ifndef _ENDIAN_H
#define _ENDIAN_H

#define LITTLE_ENDIAN	1234
#define BIG_ENDIAN	4321
#define PDP_ENDIAN	3412

/* The RCA CDP1802 is big-endian.  */
#define BYTE_ORDER	BIG_ENDIAN

#endif /* !_ENDIAN_H */
