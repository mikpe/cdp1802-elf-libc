/* _num2dec.c
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

/* Convert a number from binary to a decimal string.
 *
 * Mode of operation:
 *
 * - The caller provides the number to convert as an array of bytes in host-endian
 *   order, and an output buffer large enough to hold the resulting decimal string.
 *
 *   num: | 0x00 | 0x01 | 0xe2 | 0x40 | (123456 in big-endian)
 *   buf: | ???? | ???? | ???? | ???? | ???? | ???? |
 *
 * - First the number is converted to BCD using the Duble-Dabble or shift-and-add-3
 *   algorithm (https://en.wikipedia.org/wiki/Double_dabble). The BCD is stored with
 *   its least significant byte at the end of the buffer.
 *
 *   buf: | ???? | ???? | ???? | 0x12 | 0x34 | 0x56 |
 *
 * - Then the BCD is converted to ASCII decimal with the most significant digit
 *   at the start of the buffer.
 *
 *   buf: |  '1' |  '2' |  '3' |  '4' |  '5' |  '6' |
 *
 * Implementation notes:
 *
 * - The Double-Dabble algorithm is described as repeatedly shifting the input number
 *   left one bit. That would make the code word size specific, and would require
 *   O(word size / 8) operations per bit. Instead we treat the input number as an
 *   array of bytes, and extract its bits using a moving pointer and a byte-sized mask.
 *   This requires O(1) operations per bit, and is also word size agnostic.
 *
 * Benefits:
 *
 * - All arithmetic operations are simple (add, subtract, bitwise and, shift).
 * - All arithmetic operations are on bytes.
 * - All pointer operations are simple (load or store without offset, increment, decrement).
 * - The code handles different word sizes as-is.
 * - For a 16-bit number generating a 5-digit decimal, the code needs approximately
 *   16 * (1 + 5/2 + 1/2) + 16 == 80 operations, or 16 operations per decimal.
 */

#include <endian.h>
#include <stddef.h>
#include <stdint-gcc.h>
#include "xlibc.h"

/* FIXME: rewrite this in assembler */

static void bcd2dec(uint8_t *bcd, size_t nrdigits, char *str)
{
    size_t nrbytes = (nrdigits + 1) / 2;

    bcd -= nrbytes;

    if (nrdigits & 1) {
	*str++ = '0' + *bcd++;
	--nrbytes;
    }

    while (nrbytes) {
	uint8_t byte = *bcd++;
	*str++ = '0' + (byte >> 4);
	*str++ = '0' + (byte & 15);
	--nrbytes;
    }
}

static size_t num2bcd(const uint8_t *numptr, size_t nrbits, uint8_t *bcdend)
{
    size_t nrbytes = 0;
    size_t count;
    uint8_t *bcdptr;
    uint8_t mask;
    uint8_t byte;
    uint8_t carry;

    byte = 0;

    /* Iterate over num from most significant to least significant bit. */
    mask = 1 << 7;
#if BYTE_ORDER == LITTLE_ENDIAN
    numptr = numptr + (nrbits / 8) - 1;
#endif

    for (; nrbits; --nrbits) {

	/* Load next bit from num into the carry. */
	carry = (*numptr & mask) != 0;
	mask >>= 1;
	if (mask == 0) {
	    /* move to next less significant byte in num */
	    mask = 1 << 7;
#if BYTE_ORDER == LITTLE_ENDIAN
	    --numptr;
#else
	    ++numptr;
#endif
	}

	/* Each BCD digit >= 5 is incremented by 3. This cannot overflow.
	 * Then left-shift the BCD digits one bit with carry propagation.
	 */
	bcdptr = bcdend;
	for (count = nrbytes; count; --count) {
	    --bcdptr;

	    uint8_t obyte = *bcdptr;
	    if ((obyte & 0x0f) >= 0x05)
		obyte += 0x03;
	    if ((obyte & 0xf0) >= 0x50)
		obyte += 0x30;

	    byte = (obyte << 1) + carry;
	    *bcdptr = byte;
	    carry = (obyte & (1 << 7)) != 0;
	}

	/* If there is a carry-out from the last byte add another. */
	if (carry) {
	    byte = 0x01;
	    ++nrbytes;
	    *--bcdptr = byte;
	}
    }

    return (nrbytes * 2) - ((byte & 0xf0) ? 0 : 1);
}

size_t _num2dec(const uint8_t *num, size_t nrbits, char *buf, size_t bufsz)
{
    size_t nrdigits;

    nrdigits = num2bcd(num, nrbits, (unsigned char*)buf + bufsz);
    bcd2dec((unsigned char*)buf + bufsz, nrdigits, buf);
    return nrdigits;
}

#ifdef TEST

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NRBCDBYTES 6 /* for uint32_t */

void test(const char *nptr)
{
    char *end;
    union {
	unsigned long val;
	uint8_t num[32/8];
    } u;
    unsigned char buf[2*NRBCDBYTES];
    size_t nrdigits;

    errno = 0;
    u.val = strtoul(nptr, &end, 0);
    if (errno || *nptr == '\0' || *end != '\0' || (uint32_t)u.val != u.val) {
	printf("invalid number: '%s'\n", nptr);
	return;
    }

    memset(buf, 0, sizeof buf); /* avoid garbage in debug printouts */

    nrdigits = _num2dec(u.num, 32, buf, sizeof buf);
    printf("%s: nrdigits %u %.*s\n", nptr, (int)nrdigits, (int)nrdigits, buf);
}

int main(int argc, char **argv)
{
    int i;

    for (i = 1; i < argc; ++i) {
	test(argv[i]);
    }
    return 0;
}
#endif
