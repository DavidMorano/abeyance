/* ulogerror HEADER */
/* lang=C20 */

/* log an error */
/* version %I% last-modified %G% */


/* revision history:

	= 2023-10-08, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ULOGERROR_INCLUDE
#define	ULOGERROR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#ifdef	__cplusplus

extern "C" {
    extern int ulogerror(cchar *,int,cchar * = nullptr) noex ;
}

#else /* __cplusplus */

extern int ulogerror(cchar *,int,cchar *) noex ;

#endif /* __cplusplus */


#endif /* ULOGERROR_INCLUDE */


