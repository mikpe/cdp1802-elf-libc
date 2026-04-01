/* stdio.h
   Copyright (C) 2024-2026  Mikael Pettersson <mikpelinux@gmail.com>

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

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <stdarg.h>	/* for va_list */
#include <stddef.h>	/* for NULL, size_t */

struct __FILE;
typedef struct __FILE FILE;

#define _IONBF 2

#define EOF (-1)

#define BUFSIZ 1

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

extern FILE __libc_stdin, __libc_stdout, __libc_stderr;
#define stdin (&__libc_stdin)
#define stdout (&__libc_stdout)
#define stderr (&__libc_stderr)

typedef struct {
    unsigned long __pos;
} fpos_t;

void clearerr(FILE *stream);
int fclose(FILE *stream);
int feof(FILE *stream);
FILE *fdopen(int fd, const char *mode);
int ferror(FILE *stream);
int fflush(FILE *stream);
int fileno(FILE *stream);
int fgetc(FILE *stream);
int fgetpos(FILE *stream, fpos_t *pos);
int fgets(char *s, int size, FILE *stream);
FILE *fopen(const char *pathname, const char *mode);
int fprintf(FILE *stream, const char *format, ...);
int fputc(int c, FILE *stream);
int fputs(const char *s, FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
FILE *freopen(const char *pathname, const char *mode, FILE *stream);
int fscanf(FILE *stream, const char *format, ...);
int fseek(FILE *stream, long offset, int whence);
int fsetpos(FILE *stream, const fpos_t *pos);
long ftell(FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int getc(FILE *stream);
int getchar(void);
void perror(const char *s);
int printf(const char *format, ...);
int putc(int c, FILE *stream);
int putchar(int c);
int puts(const char *s);
int remove(const char *pathname);
int rename(const char *oldpath, const char *newpath);
void rewind(FILE *stream);
int scanf(const char *format, ...);
void setbuf(FILE *stream, char *buf);
int setvbuf(FILE *stream, char *buf, int mode, size_t size);
int snprintf(char *str, size_t size, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int sscanf(const char *str, const char *format, ...);
FILE *tmpfile(void);
int ungetc(int c, FILE *stream);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vprintf(const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *fmt, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);

__END_DECLS

#endif /* !_STDIO_H */
