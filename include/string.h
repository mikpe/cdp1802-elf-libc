/* string.h
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

#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>	/* for size_t */

void *memchr(const void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
void *mempcpy(void *dst, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
char *strchr(const char *s, int c);
size_t strlen(const char *s);
char *strcat(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dst, const char *src);
char *strdup(const char *s);
int strncmp(const char *s1, const char *s2, size_t n);
char *strndup(const char *s, size_t n);
size_t strnlen(const char *s, size_t n);
char *strncat(char *dst, const char *src, size_t n);
char *strncpy(char *dst, const char *src, size_t n);
char *strrchr(const char *s, int c);
size_t strspn(const char *s, const char *accept);
char *strtok(char *str, const char *delim);

#endif /* !_STRING_H */
