/* ucsyssv HEADER */
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

#ifndef	UCSYSSV_INCLUDE
#define	UCSYSSV_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<netdb.h>		/* <- the money shot */


#ifndef	SERVENT
#define	SERVENT		struct servent
#endif

#ifndef	CSERVENT
#define	CSERVENT	const struct servent
#endif

EXTERNC_begin

extern SERVENT	*getsvent() noex ;
extern SERVENT	*getsvnam(cchar *,cchar *) noex ;
extern SERVENT	*getsvpor(int,cchar *) noex ;

extern int	getsvent_rp(SERVENT *,char *,int) noex ;
extern int	getsvnam_rp(SERVENT *,char *,int,cchar *,cchar *) noex ;
extern int	getsvpor_rp(SERVENT *,char *,int,int,cchar *) noex ;

EXTERNC_end


#endif /* UCSYSSV_INCLUDE */


