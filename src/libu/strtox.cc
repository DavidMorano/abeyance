/* strtox SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* conversion of a decimal c-string to the type |longlong| */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* debuging */

/* revision history:

	= 1998-09-03, David A­D­ Morano
	This code was written to provide string-to-integer conversions
	in the style (similar function signatiures and semantics)
	of the existing UNIX® standard-C library subroutines like
	|strtol(3c)| and |strtoul(3c)|.  But the idea was to provide
	subroutines that can perform 128-bit (and larger) conversions
	for the types |{x}longlong| (signed and unsigned).  This
	code is partially modeled after some very old previous
	subroutines that I wrote first in assembly and then in C
	language.  See my description below for more on why I wrote
	these subroutines here.

	= 2020-05-24, David A­D­ Morano
	I added some code to make constant-expression compile-time
	computations.

*/

/* Copyright © 1998,2020 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Group:
	strto{x}

	Names:
	strtoxi
	strtoxui
	strtoxl
	strtoxul
	strtoxll
	strtoxull

	Synopsis:
	{x} strtox{x}(cchar *sp,char **endp,int base) noex

	Arguments:
	{x}		one of: i, l, ll
	sp		c-string to convert
	endp		returned pointer last character considered
	base		base to convert, 2-36

	Returns:
	typeof({x})	resulting value in destired integer type
	errno		set on error (UNIX® error number)

	Description:
	This code converts a c-string of decimal digits into the
	integer types |longlong| and |ulonglong|.  The API and
	semantics of this code is intentionally moduled after the
	API and semantics of the existing UNIX® conversion subroutines
	|strtol(3c)| and |strtoul(3c)|.  See the notes below for
	more information on the necessity for these.

	Notes:
	1. This code is limited (by the coding used) to a maximum
	base of 36.

	Question-Answers:

	Q. Why are you using these old weirdo UNIX® standard
	C-language library subroutine function signatures?

	A. Because before the CTX subroutines (in the LIBUC) lobrary
	are available, I need some local subroutines (here within
	the LIBU library) to perform some of these conversions.
	Although |strtol(3c)| and |strtoul(3c)| are generally
	available across all UNIXi implementation (and are called
	directly below for much of the provided interfaces), the
	standard C-language library does not supply any of: |strtoi|,
	|strtoui|, |strtoll|, |strtoull|, |strtoim| or |strtouim|.
	I leverage the fact that |strtol| and |strtou| were already
	written to provide conversion for types smaller than a
	|long| and |ulong|.  But for the integers sized larger than
	that (128-bit and larger), I had to write compatible (similar
	function signature and semantic) subroutines from scratch,
	since there are no simple standard lirbary calls that are
	avilable in regular C-language that could be used.

	Q. Are subroutine converters availble now for 256-bit and
	512-bit integers?

	A. No.  I kind-of think they are not needed here (in LIBU)
	because there are currently no required use cases for
	integers larger than 128-bit.  Larger integers are used
	after LIBUC is loaded and there the CTX and CFX subroutines
	provide for the larger integer types (also up to 128-bit
	but beyond also).

	Q. Why are the names of these subroutine prefixed with |strtox|
	rather than simply |strto| like the standard C-language
	subroutine are?  
	
	A. Because the standard C-language library aready provdes
	subroutines named |strtoll| and |strtoull|, but they do the
	wrong thing.  The 'll' postfix in the subroutine name
	indicates (or is suppoed to indicate) that the 'long long'
	type is being used.  But the 'long long' type on most systems
	today is still only 64 bits, where I wanted the 'll' postfix
	to mean conversion to a 128-bit integer.  Further, I want
	the postix 'im' or 'imax' to indicate a conversion to a
	256-bit integer (not yet implemented).

	Q. What is the basic alforithm used below for conversions 
	(signed and unsigned)?

	A. I use the "cutoff-curlim" alforithm; the same as almost all
	(known) UNIXi (or POSIXi) uses.

	Q. Do you optimize even-power-of-two bases for faster
	conversions.

	A. No.  Often (usually), the fastest algorithms (for anything)
	is not in this library (LIBU) but rather in higher-level
	libraries (LIBUC and higher).

	Q. Do you provide conversions for intger types smaller than
	a 32-bit integer?

	A. No.  Use a conversion foe a 32-bit integer and cast the
	result as you like.

	Q. What number bases are supported?

	A. Bases 2 through 36 are supported (the old standard).

	Q. Have you written enough of thse "number conversion"
	functions?

	A. Apparently not.  It does seem like writing these are a
	major part of getting onto a new platorm.  Especially when
	you have total bare metal and you need to write a new ROM
	monitor.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cerrno>
#include	<climits>		/* |CHAR_BIT| + |strtol(3c)| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |strtol(3c)| */
#include	<bitset>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<stdintx.h>
#include	<localmisc.h>
#include	<dprintf.hh>		/* debugging */

#include	"strtox.h"

import bitmanip ;			/* LIBU bit-manipulations */
import ischx ;				/* LIBU character classes */

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debuging */
#endif


/* imported namespaces */

using std::bitset ;			/* type */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

constexpr int	maxbase = 36 ;		/* must be classic value */
constexpr int   chtablen = (UCHAR_MAX + 1) ;

namespace {
    struct llhelper {
	longlong	llmin = 0 ;
	longlong	llmax = 0 ;
	ulonglong	ullmax = 0 ;
	ulonglong	cutoff[maxbase+1] = {} ;
	int		cutlim[maxbase+1] = {} ;
	constexpr llhelper() noex {
	    clonglong	one = 1 ;
	    cint	nb = nbits<longlong> ;
	    ullmax = (compl ullmax) ;
	    llmin = (one << (nb - 1)) ;
	    llmax = longlong(ullmax >> 1) ;
	    for (uint b = 2 ; b <= uint(maxbase) ; b += 1) {
		cutoff[b] = (ullmax / b) ;
		cutlim[b] = int(ullmax % b) ;
	    } /* end for */
	} ; /* end ctor */
    } ; /* end subroutine (llhelper) */
} /* end namespace */

namespace {
    struct charbase {
	bitset<chtablen>	isbase ;
	consteval void mkisbase() noex {
	    const uchar bases[] = { 'B', 'D', 'O', 'X' } ;
	    for (cauto &ch : bases) {
		isbase.set(ch,true) ;
		isbase.set((ch + 0x20),true) ;
	    } /* end for */
	} /* end method */
	consteval charbase() noex {
	    mkisbase() ;
	} ; /* end ctor */
    } ; /* end struct (charbase) */
} /* end namespace */


/* forward references */

template<typename T>
local inline void strtox(cchar *,char **,int,T *rp) noex {
	*rp = 0 ;
}

template<>
inline void strtox(cchar *sp,char **epp,int b,int *rp) noex {
	clong	v = strtol(sp,epp,b) ;
	*rp = int(v) ;
	if (errno == 0) {
	    cint nb = nbits<long> ;
	    {
	        cbool	fneg = bit(v,(nb - 1)) ;
		if (fneg) {	/* test negative value */
	    	    ulong	uv = ulong(v) ;
		    uv = (~ uv) ;
	            uv >>= (nb / 2) ;
		    if (uv || (! bit(v,((nb / 2) - 1)))) {
			errno = ERANGE ;
		    }
		} else {	/* test poitive value */
		    ulong	uv = ulong(v) ;
	            uv >>= (nb / 2) ;
		    if (uv || bit(v,((nb / 2) - 1))) {
			errno = ERANGE ;
		    }
		} /* end if */
	    } /* end block */
	} /* end if (no error so far) */
} /* end subroutine-template (strtox) */

template<>
inline void strtox(cchar *sp,char **epp,int b,uint *rp) noex {
	ulong	uv = strtoul(sp,epp,b) ;
	*rp = uint(uv) ;
	if (errno == 0) {
	    cint nb = nbits<ulong> ;
	    uv >>= (nb / 2) ;
	    if (uv) {
		errno = ERANGE ;
	    }
	} /* end if (no-error) */
} /* end subroutine-template (strtox) */

local inline bool ischbase(int ch_bl,int ch) noex {
    	cint ch_bu = (ch_bl - 0x20) ;
    	return (ch == ch_bl) || (ch == ch_bu) ;
}

local inline int conbase(int) noex ;
 

/* local variables */

constexpr llhelper	llhelp ;

constexpr charbase	chbase ;

cbool			f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int strtoxi(cchar *sp,char **epp,int b) noex {
	int	v{} ;
	if (sp) {
	    strtox(sp,epp,b,&v) ;
	} else {
	    errno = ERANGE ;
	}
	return v ;
}
/* end subroutine (strtoxi) */

long strtoxl(cchar *sp,char **epp,int b) noex {
    	long	res{} ;
	if (sp) {
	    res = strtol(sp,epp,b) ;
	} else {
	    errno = ERANGE ;
	}
	return res ;
}
/* end subroutine (strtoxl) */

longlong strtoxll(cchar *startp,char **endpp,int base) noex {
	longlong	acc = 0 ; /* return-value */
	DPRINTF("ent b=%d\n",base) ;
	if (startp) {
            int		verr = 0 ;
            int		cutlim ;
            int		ch ;
            cchar	*sp = startp ;
            bool	fneg = false ;
	    DPRINTF("str=>%s<\n",startp) ;
            while (ischwhite(ch = uchar(*sp))) {
		sp += 1 ;
            } /* end while */
            if (ch == '-') {
                fneg = true ;
                ch = *++sp ;
            } else {
                fneg = false ;
                if (ch == '+') {
                    ch = *++sp ;
                }
            } /* end if */
	    DPRINTF("fneg=%u\n",uint(fneg)) ;
	    DPRINTF("ch=%c (%02X)\n",uchar(ch),ch) ;
            if ((base == 0 || base == 16) && ch == '0') {
	        DPRINTF("possible base adjustment\n") ;
		if (cint b = conbase(sp[1]) ; b > 0) {
                    base = b ;
                    ch = sp[2] ;
                    sp += 2 ;
		} /* end if (conbase) */
            } /* end if */
	    DPRINTF("ch=%c (%02X)\n",uchar(ch),ch) ;
            if (base == 0) {
                base = ((ch == '0') ? 8 : 10) ;
            }
	    DPRINTF("adjusted-base=%d\n",base) ;
	    DPRINTF("ch=%c (%02X)\n",uchar(ch),ch) ;
            if ((base >= 2) && (base <= maxbase)) {
                longlong    cutoff = fneg ? llhelp.llmin : llhelp.llmax ;
                cutlim = int(cutoff % base) ;
                cutoff /= base ;
                if (fneg) {
                    if (cutlim > 0) {
                        cutlim -= base ;
                        cutoff += 1 ;
                    }
                    cutlim = (- cutlim) ;
                } /* end if (negative) */
                while ((ch = uchar(*sp++)) != '\0') {
                    int val{} ;
	    	    DPRINTF("ch=%c (%02X)\n",uchar(ch),ch) ;
                    if (ischdigit(ch)) {
                        val = (ch - '0' + 0) ;
                    } else if (ischalpha(ch)) {
                        if (ischupper(ch)) {
                            val = (ch - 'A' + 10) ;
                        } else {
                            val = (ch - 'a' + 10) ;
                        }
                    } else {
                        break ;
                    }
	    	    DPRINTF("val=%d\n",val) ;
                    if (val >= base) break ;
                    if (verr < 0) continue ;
                    if (fneg) {
                        if ((acc < cutoff) || (acc == cutoff && val > cutlim)) {
                            verr = -1 ;
                            acc = llhelp.llmin ;
                            errno = ERANGE ;
                        } else {
                            verr = +1 ;
                            acc *= base ;
                            acc -= val ;
                        } /* end if */
                    } else {
                        if ((acc > cutoff) || (acc == cutoff && ch > cutlim)) {
                            verr = -1 ;
                            acc = llhelp.llmax ;
                            errno = ERANGE ;
                        } else {
                            verr = +1 ;
                            acc *= base ;
                            acc += val ;
                        } /* end if */
                    } /* end if */
                } /* end while */
            } else {
                errno = ENOTSUP ;
            } /* end if (valid base) */
            if (endpp) {
                *endpp = charp(verr ? (sp - 1) : startp) ;
            }
	} else {
	    errno = EFAULT ;
	}
	DPRINTF("ret errno=%d\n",errno) ;
	return acc ;
}
/* end subroutine (strtoxll) */

uint strtoxui(cchar *sp,char **epp,int b) noex {
	uint	uv{} ;
	if (sp) {
	    strtox(sp,epp,b,&uv) ;
	} else {
	    errno = ERANGE ;
	}
	return uv ;
}
/* end subroutine (strtoxui) */

ulong strtoxul(cchar *sp,char **epp,int b) noex {
    	ulong	res{} ;
	if (sp) {
	    res = strtoul(sp,epp,b) ;
	} else {
	    errno = ERANGE ;
	}
	return res ;
}
/* end subroutine (strtouxl) */

ulonglong strtoxull(cchar *startp,char **endpp,int base) noex {
	ulonglong	acc = 0 ; /* return-value */
	DPRINTF("ent b=%d\n",base) ;
	if (startp) {
            int		verr = 0 ;
            int		cutlim ;
            int		ch ;
            cchar	*sp = startp ;
            bool	fneg = false ;
            while (ischwhite(ch = uchar(*sp))) {
		sp += 1 ;
            } /* end while */
            if (ch == '-') {
                fneg = true ;
                ch = *++sp ;
            } else { 
                fneg = false ;
                if (ch == '+') {
                    ch = *++sp ;
                }
            }
            if ((base == 0 || base == 16) && ch == '0') {
		if (cint b = conbase(sp[1]) ; b > 0) {
                    ch = sp[2] ;
                    sp += 2 ;
                    base = 16 ;
		} /* end if (conbase) */
            } /* end if */
            if (base == 0) {
                base = ((ch == '0') ? 8 : 10) ;
            }
	    DPRINTF("adjusted-base=%d\n",base) ;
            if ((base >= 2) && (base <= maxbase)) {
                ulonglong   cutoff = llhelp.cutoff[base] ;
                cutlim = llhelp.cutlim[base] ;
                while ((ch = uchar(*sp++)) != '\0') {
                    int val{} ;
                    if (ischdigit(ch)) {
                        val = (ch - '0' + 0) ;
                    } else if (ischalpha(ch)) {
                        if (ischupper(ch)) {
                            val = (ch - 'A' + 10) ;
                        } else {
                            val = (ch - 'a' + 10) ;
                        }
                    } else {
                        break ;
                    }
                    if (val >= base) break ;
                    if (verr < 0) continue ;
                    if ((acc > cutoff) || (acc == cutoff && val > cutlim)) {
                        verr = -1 ;
                        acc = llhelp.ullmax ;
                        errno = ERANGE ;
                    } else {
                        verr = +1 ;
                        acc *= base ;
                        acc += val ;
                    } /* end if */
                } /* end while */
                if (fneg && verr > 0) {
                    acc = (- acc) ;
                }
            } else {
                errno = ENOTSUP ;
            } /* end if (valid base) */
            if (endpp) {
                *endpp = charp(verr ? (sp - 1) : startp) ;
            }
	} else {
	    errno = EFAULT ;
	}
	DPRINTF("ret errno=%d\n",errno) ;
	return acc ;
}
/* end subroutine (strtoxull) */


/* local subroutines */

local inline int conbase(int ch) noex {
    	int b = 0 ;
	if (chbase.isbase[ch] & UCHAR_MAX) {
	    if (ischbase('x',ch)) {
	        b = 16 ;
	    } else if (ischbase('b',ch)) {
		b = 2 ;
	    } else if (ischbase('o',ch)) {
		b = 8 ;
	    } else if (ischbase('d',ch)) {
		b = 10 ;
	    }
	} /* end if (was special base) */
    	return b ;
} /* end subroutine (conbase) */
 

