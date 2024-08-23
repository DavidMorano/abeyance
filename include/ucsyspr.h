/* ucsyspr HEADER */
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

#ifndef	UCSYSPR_INCLUDE
#define	UCSYSPR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<netdb.h>		/* <- the money shot */


#ifndef	PROTOENT
#define	PROTOENT	struct protoent
#endif

#ifndef	CPROTOENT
#define	CPROTOENT	const struct protoent
#endif

EXTERNC_begin

extern PROTOENT	*getprent() noex ;
extern PROTOENT	*getprnam(cchar *) noex ;
extern PROTOENT	*getprnum(int) noex ;

extern int	getprent_rp(PROTOENT *,char *,int) noex ;
extern int	getprnam_rp(PROTOENT *,char *,int,cchar *) noex ;
extern int	getprnum_rp(PROTOENT *,char *,int,int) noex ;

EXTERNC_end


#endif /* UCSYSPR_INCLUDE */


