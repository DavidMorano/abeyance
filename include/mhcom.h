/* mhcom HEADER */
/* lang=C20 */

/* comment-parse (for RFC822) small strings (like for stupid RFC822 date) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MHCOM_INCLUDE
#define	MHCOM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	MHCOM_MAGIC	0x98638451
#define	MHCOM		struct mhcom_head


struct mhcom_head {
	char		*a ;
	char		*value ;
	char		*comment ;
	uint		magic ;
	int		vlen ;
	int		clen ;
} ;

typedef MHCOM		mhcom ;

EXTERNC_begin

extern int mhcom_start(MHCOM *,cchar *,int) noex ;
extern int mhcom_getval(MHCOM *,cchar **) noex ;
extern int mhcom_getcom(MHCOM *,cchar **) noex ;
extern int mhcom_finish(MHCOM *) noex ;

EXTERNC_end


#endif /* MHCOM_INCLUDE */


