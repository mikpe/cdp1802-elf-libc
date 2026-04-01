/* setlocale.c
   Copyright (C) 2026  Mikael Pettersson <mikpelinux@gmail.com>

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

#include <locale.h>
#include <stddef.h>

char *setlocale(int category, const char *locale)
{
    if ((unsigned int) category > LC_TIME)
	return NULL;
    if (locale == NULL ||
	locale[0] == '\0' ||
	(locale[0] == 'C' && locale[1] == '\0'))
	return (char*) "C";
    return NULL;
}
