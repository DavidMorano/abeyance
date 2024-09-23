/* getfname HEADER */
/* lang=C20 */

/* get a file name according to rules */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-03, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETFNAME_INCLUDE
#define	GETFNAME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#ifndef	GETFNAME_TYPELOCAL
#define	GETFNAME_TYPEUNKNOWN	-1
#define	GETFNAME_TYPELOCAL	0
#define	GETFNAME_TYPEROOT	1
#endif


#ifdef	__cplusplus

extern "C" {
    extern int getfname(cchar *,char *,int,cchar *,int = 0) noex ;
}

#else /* __cplusplus */

extern int getfname(cchar *,char *,int,cchar *,int) noex ;

#endif /* __cplusplus */


#endif /* GETFNAME_INCLUDE */


