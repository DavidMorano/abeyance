/* unameo HEADER */
/* lang=C20 */

/* UNIX® information (a cache for |uname(2)| and sisters) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UNAMEO_INCLUDE
#define	UNAMEO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<utypedefs.h>
#include	<clanguage.h>


#define	UNAMEO		struct unameo_head


struct unameo_head {
	cchar		*sysname ;
	cchar		*nodename ;
	cchar		*release ;
	cchar		*version ;
	cchar		*machine ;
	cchar		*a ;		/* the memory-allocation */
} ;

typedef UNAMEO		unameo ;

EXTERNC_begin

extern int unameo_start(unameo *) noex ;
extern int unameo_finish(unameo *) noex ;

EXTERNC_end


#endif /* UNAMEO_INCLUDE */


