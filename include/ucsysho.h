/* ucsysho HEADER */
/* lang=C20 */

/* additional operaring-system support for PEOJECT-DB access */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the MacOS operating system.

*******************************************************************************/

#ifndef	UCSYSHO_INCLUDE
#define	UCSYSHO_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<netdb.h>		/* <- the money shot */


#ifndef	HOSTENT
#define	HOSTENT		struct hostent
#endif

#ifndef	CHOSTENT
#define	CHOSTENT	const struct hostent
#endif

EXTERNC_begin

extern HOSTENT	*gethoent() noex ;
extern HOSTENT	*gethonam(cchar *) noex ;
extern HOSTENT	*gethoadd(int,cvoid *,int) noex ;

extern int	gethoent_rp(HOSTENT *,char *,int) noex ;
extern int	gethonam_rp(HOSTENT *,char *,int,cchar *) noex ;
extern int	gethoadd_rp(HOSTENT *,char *,int,int,cvoid *,int) noex ;

EXTERNC_end


#endif /* UCSYSHO_INCLUDE */


