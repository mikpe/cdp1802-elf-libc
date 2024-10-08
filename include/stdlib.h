/* stdlib.h
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

#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>	/* for size_t */

typedef int ssize_t;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 32767

typedef struct {
    int quot;
    int rem;
} div_t;

void abort(void);
int atoi(const char *nptr);
void *calloc(size_t nmemb, size_t size);
div_t div(int num, int den);
void exit(int status) __attribute__((__noreturn__));
void free(void *ptr);
void *malloc(size_t size);
int posix_memalign(void **memptr, size_t alignment, size_t size);
int putenv(char *string);
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
int rand(void);
void *realloc(void *ptr, size_t size);
void srand(unsigned int seed);

#endif /* !_STDLIB_H */
