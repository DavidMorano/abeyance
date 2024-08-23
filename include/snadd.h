/* snadd HEADER */
/* lang=C20 */

/* append a c-string to a given counted c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

	Ths object is used to concatenate a new c-string to
	an existing counted c-string.

******************************************************************************/

#ifndef	SNADD_INCLUDE
#define	SNADD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<snaddw.h>


EXTERNC_begin

extern int snaddx(char *,int,int,int,...) noex ;

static inline int snadd(char *dbuf,int dlen,int dl,cchar *sp) noex {
	return snaddw(dbuf,dlen,dl,sp,-1) ;
}

EXTERNC_end

#ifdef	__cplusplus

template<typename ... Args>
inline int snadd(char *dbuf,int dlen,int dl,Args ... args) noex {
	cint		na = npack(Args) ;
	return snaddx(dbuf,dlen,dl,na,args ...) ;
}

#endif /* __cplusplus */


#endif /* SNADD_INCLUDE */


