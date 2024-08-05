/* stdio.h
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

#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>	/* for va_list */
#include <stddef.h>	/* for NULL, size_t */

struct __FILE;
typedef struct __FILE FILE;

#define EOF (-1)

extern FILE __libc_stdout, __libc_stderr;
#define stdout (&__libc_stdout)
#define stderr (&__libc_stderr)

int fclose(FILE *stream);
int ferror(FILE *stream);
int fileno(FILE *stream);
int fflush(FILE *stream);
/*FILE *fopen(const char *pathname, const char *mode);*/
int fprintf(FILE *stream, const char *format, ...);
int fputc(int c, FILE *stream);
int fputs(const char *s, FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int getc(FILE *stream);
int getchar(void);
void perror(const char *s);
int printf(const char *format, ...);
int putchar(int c);
int puts(const char *s);
int remove(const char *pathname);
int scanf(const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
int sprintf(char *str, const char *format, ...);
/*char *tmpnam(char *s);*/
int vfprintf(FILE *stream, const char *format, va_list ap);
int vprintf(const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *fmt, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);

#endif /* !_STDIO_H */
