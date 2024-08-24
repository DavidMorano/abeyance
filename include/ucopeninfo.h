/* ucopeninfo HEADER */
/* lang=C20 */

/* additional UNIX® limits support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Additional support for the UNIX® OPEN facility.

*******************************************************************************/

#ifndef	UCOPENINFO_INCLUDE
#define	UCOPENINFO_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>
#include	<fcntl.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	UCOPENINFO	ucopeninfo_head


struct ucopeninfo_head {
	mainv		envv ;
	cchar		*fname ;
	int		clinks ;
	int		oflags ;
	int		to ;
	int		opts ;
	mode_t		operms ;
} ;

typedef UCOPENINFO	ucopeninfo ;

EXTERNC_begin

extern int	uc_openex(cchar *,int,mode_t,int,int) noex ;
extern int	uc_openinfo(ucopeninfo *) noex ;

EXTERNC_end


#endif /* UCOPENINFO_INCLUDE */


