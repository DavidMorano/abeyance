/* obuf HEADER */
/* lang=C++20 */

/* Output Buffer */
/* version %I% last-modified %G% */


/* revision history:

	= 2016-06-29, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2016 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	See the source support file ('obuf.cc') for a descruption
	of this object.

*******************************************************************************/

#ifndef	OBUF_INCLUDE
#define	OBUF_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>
#include	<cstring>		/* <- for |strlen(3c)| */
#include	<string>		/* <- C++ |string| */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<mkchar.h>
#include	<localmisc.h>


class obuf {
	std::string	b ;
	int		oi ;		/* output index */
public:
	obuf(const obuf &) = delete ;
	obuf &operator = (const obuf &) = delete ;
	obuf(cchar *sbuf = nullptr,int slen = -1) noex : oi(0) {
	    if (sbuf) {
	        if (slen < 0) slen = strlen(sbuf) ;
	        for (int i = 0 ; sbuf[i] ; i += 1) {
		    b.push_back(sbuf[i]) ;
	        }
	    } /* end if (non-null) */
	} ;
	int operator [] (int i) const noex {
	    cint	n = b.size() ;
	    int		rch = 0 ;
	    if ((oi+i) < n) rch = mkchar(b[oi+i]) ;
	    return rch ;
	} ;
	obuf &operator += (int ch) noex {
	    b.push_back(ch) ;
	    return *this ;
	} ;
	int add(int ch) noex {
	    b.push_back(ch) ;
	    return (b.size() - oi) ;
	} ;
	int add(cchar *sp,int sl = -1) noex {
	    if (sl < 0) sl = strlen(sp) ;
	    for (int i = 0 ; i < sl ; i += 1) {
		b.push_back(sp[i]) ;
	    }
	    return (b.size() - oi) ;
	} ;
	int count() const noex {
	    return (b.size() - oi) ;
	} ;
	int len() const noex {
	    return (b.size() - oi) ;
	} ;
	int at(int i) const noex {
	    cint	n = b.size() ;
	    int		rch = 0 ;
	    if ((oi+i) < n) rch = mkchar(b[oi+i]) ;
	    return rch ;
	} ;
	int adv(int) noex ;
	operator int () const noex ;
} ; /* end class (obuf) */


#endif /* __cplusplus */
#endif /* OBUF_INCLUDE */


