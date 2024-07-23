/* divu10.c
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

#include <stdint.h>

/*
 * Divide an unsigned integer by 10, using only shifts and adds.
 * Algorithm based on Hacker's Delight, Figure 10-10.
 *
 * Assume bytes per word is BPW (1, 2, 4, 8).
 *
 * Runtime costs on the CDP1802:
 *
 * Step 1 costs 4 x BPW operations (downshift, copy, downshift, add).
 * Step 2 costs 5 x BPW operations (4 x downshifts, add).
 * Step 3 costs 1 x BPW operations (add with next higher byte as 2nd operand).
 * Step 4 costs 1 x BPW operations (add with next higher word as 2nd operand).
 * Step 5 costs 3 x BPW operations (3 x downshifts).
 * Step 6 costs 5 operations (shift, shift, add, shift. sub).
 * Step 7 costs 2 (sub, lbdf) plus 0 or 1 x BPW operations (add).
 *
 * Total cost 7 + (14 or 15) x BPW operations.
 * With 0 or 1 more operations (r -= 10 if r > 9) we can also compute and return r,
 * eliminating the equivalent of step 6 in the caller.
 */

uint32_t divu10(uint32_t n)
{
    uint32_t q;
    uint8_t r;

    /* Compute an approximation of the quotient.
     * It may be 1 smaller than the correct value.
     */
    q  = (n >> 1) + (n >> 2);				/* 1. */
    q += (q >> 4);					/* 2. */
    q += (q >> 8);					/* 3. */
    q += (q >> 16);					/* 4. */
    q >>= 3;						/* 5. */

    /* Compute the remainder: r = n - 10*q.
     * It will be bounded by [0,20[.
     * We do not need full precision to compute it.
     */
#if 0
    r = n - (((q << 2) + q) << 1);
#else
    r = (uint8_t)n - (uint8_t)(((q << 2) + q) << 1);	/* 6. */
#endif

    /* Correct quotient and return it. */
#if 1
    return q + (r > 9);					/* 7. */
#else
    return q + ((r + 6) >> 4);
#endif
}

#ifdef TEST
#include <stdio.h>

unsigned int test(uint32_t n)
{
    uint32_t q;
    uint8_t r;

    if ((n & ((1 << 20) - 1)) == ((1 << 20) - 1))
	fputc('.', stderr);

    q = divu10(n);
    if (q > n || (r = n - 10*q) >= 10) {
	fprintf(stderr, "\ndivu10(%u) returned %u\n", n, q);
	return 1;
    }
    return 0;
}

int main(void)
{
    uint32_t n = 0;
    unsigned int errors = 0;

    do {
	errors += test(n);
    } while (++n != 0);

    printf("%u errors\n", errors);
    return !!errors;
}
#endif
