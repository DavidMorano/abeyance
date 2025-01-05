/* strtoxlonglong SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* conversion of a decimal c-sting to the type |longlong| */
/* version %I% last-modified %G% */


/*	$OpenBSD: strtol.c,v 1.7 2005/08/08 08:05:37 espie Exp $ */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* revision history:

	= 2023-05-14, David A­D­ Morano
	I adapted this to serve the |xlonglong| types.

*/

/* Copyright © 2023 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This code converts a c-string of decimal digits into the
	integer type |longlong|.  It is obviously a derivative work
	of the original |strtol(3c)| from the Berkley BSD edition
	of its UNIX® variant.  I am forced to do this since I have
	lost my own conversion-suite version from over forty years
	ago and also lost my other conversion-suite versions (two
	others) from some more recent years ago (all lost to coporate
	America now, which means they are gone).  I kind of have to
	laugh at having to make-shift code like this given I had
	coded things like this so long ago and thought that I would
	never have to do it again.
		-- David A.D. Morano, 2023-10-10

	Notes:
	1. This code is limited (by the coding used) to a maximum
	base of 36.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>
#include	<climits>		/* for |CHAR_BIT| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cctype>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<stdintx.h>

#include	"strtoxlonglong.h"


/* local defines */


/* local namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

constexpr int	maxbase = 36 ;		/* must be classic value */

struct llhelper {
	const longlong	one = 1 ;
	longlong	llmin = 0 ;
	longlong	llmax = 0 ;
	ulonglong	ullmax = 0 ;
	ulonglong	cutoff[maxbase+1] = {} ;
	int		cutlim[maxbase+1] = {} ;
	constexpr llhelper() noex {
	    cint	n = (CHAR_BIT * szof(longlong)) ;
	    ullmax = ~ullmax ;
	    llmin = (one << (n-1)) ;
	    llmax = longlong(ullmax >> 1) ;
	    for (uint b = 2 ; b <= maxbase ; b += 1) {
		cutoff[b] = (ullmax / b) ;
		cutlim[b] = (ullmax & b) ;
	    } /* end for */
	} ; /* end constructor */
} ; /* end subroutine (llhelper) */


/* local variables */

constexpr llhelper	llhelp ;


/* exported subroutines */

/*
 * Convert a string to a |longlong| integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */

longlong strtolonglong(cchar *nptr,char **endptr,int base) noex {
	longlong	acc, cutoff ;
	cchar		*s ;
	int 		c ;
	int 		neg, any, cutlim ;
	/*
	 * Skip white space and pick up leading +/- sign if any.
	 * If base is 0, allow 0x for hex and 0 for octal, else
	 * assume decimal; if base is already 16, allow 0x.
	 */
	s = nptr;
	do {
		c = (unsigned char) *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else {
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0) {
		base = ((c == '0') ? 8 : 10) ;
	}
	/*
	 * Compute the cutoff value between legal numbers and illegal
	 * numbers.  That is the largest legal value, divided by the
	 * base.  An input number that is greater than this value, if
	 * followed by a legal input character, is too big.  One that
	 * is equal to this value may be valid or not; the limit
	 * between valid and invalid numbers is then based on the last
	 * digit.  For instance, if the range for longs is
	 * [-2147483648..2147483647] and the input base is 10,
	 * cutoff will be set to 214748364 and cutlim to either
	 * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
	 * a value > 214748364, or equal but the next digit is > 7 (or 8),
	 * the number is too big, and we will return a range error.
	 *
	 * Set 'any' if any `digits' consumed; make it negative to indicate
	 * overflow.
	 */
	cutoff = neg ? llhelp.llmin : llhelp.llmax ;
	cutlim = cutoff % base;
	cutoff /= base;
	if (neg) {
		if (cutlim > 0) {
			cutlim -= base;
			cutoff += 1;
		}
		cutlim = -cutlim;
	}
	for (acc = 0, any = 0 ; ; c = (unsigned char) *s++) {
		if (isdigit(c)) {
			c -= '0';
		} else if (isalpha(c)) {
			c -= isupper(c) ? ('A' - 10) : ('a' - 10) ;
		} else
			break;
		if (c >= base)
			break;
		if (any < 0)
			continue;
		if (neg) {
			if (acc < cutoff || (acc == cutoff && c > cutlim)) {
				any = -1;
				acc = llhelp.llmin ;
				errno = ERANGE;
			} else {
				any = 1;
				acc *= base;
				acc -= c;
			}
		} else {
			if (acc > cutoff || (acc == cutoff && c > cutlim)) {
				any = -1;
				acc = llhelp.llmax ;
				errno = ERANGE;
			} else {
				any = 1;
				acc *= base;
				acc += c;
			}
		}
	}
	if (endptr != nullptr) {
	    *endptr = (char *) (any ? (s - 1) : nptr) ;
	}
	return (acc);
}
/* end subroutine (strtolonglong) */

/*
 * Convert a string to a |ulonglong|.
 *
 * Ignores 'locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */

ulonglong strtoulonglong(cchar *nptr, char **endptr, int base) noex {
	ulonglong	acc, cutoff;
	cchar		*s;
	int c;
	int neg, any, cutlim;
	/*
	 * See strtoq for comments as to the logic used.
	 */
	s = nptr;
	do {
		c = (unsigned char) *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else { 
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0) {
		base = ((c == '0') ? 8 : 10) ;
	}

        /* BIONIC: avoid division and modulo for common cases */
#define  CASE_BASE(x)                            \
            case x: cutoff = llhelp.ullmax / x;    \
	            cutlim = llhelp.ullmax % x;    \
		    break

#ifdef	COMMENT
        switch (base) {
        CASE_BASE(8);
	CASE_BASE(10);
	CASE_BASE(16);
	default:
	    cutoff = llhelp.ullmax / base;
	    cutlim = llhelp.ullmax % base;
	    break ;
	} /* end switch */
#else /* COMMENT */
	    cutoff = llhelp.cutoff[base] ;
	    cutlim = llhelp.cutlim[base] ;
#endif /* COMMENT */
	
	for (acc = 0, any = 0 ; ; c = (unsigned char) *s++) {
		if (isdigit(c)) {
			c -= '0';
		} else if (isalpha(c)) {
			c -= isupper(c) ? ('A' - 10) : ('a' - 10) ;
		} else
			break;
		if (c >= base)
			break;
		if (any < 0)
			continue;
		if (acc > cutoff || (acc == cutoff && c > cutlim)) {
			any = -1;
			acc = llhelp.ullmax ;
			errno = ERANGE;
		} else {
			any = 1;
			acc *= base ;
			acc += c ;
		}
	}
	if (neg && any > 0) {
	    acc = (-acc) ;
	}
	if (endptr != nullptr) {
	    *endptr = (char *) (any ? (s - 1) : nptr) ;
	}
	return (acc);
}
/* end subroutine (strtoulonglong) */


