/* ucsysnw HEADER */
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

#ifndef	UCSYSNW_INCLUDE
#define	UCSYSNW_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<stdint.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<netdb.h>		/* <- the money shot */


#ifndef	NETENT
#define	NETENT		struct netent
#endif

#ifndef	CNETENT
#define	CNETENT		const struct netent
#endif

EXTERNC_begin

extern NETENT	*getnwent() noex ;
extern NETENT	*getnwnam(cchar *) noex ;
extern NETENT	*getnwnum(int,uint32_t) noex ;

extern int	getnwent_rp(NETENT *,char *,int) noex ;
extern int	getnwnam_rp(NETENT *,char *,int,cchar *) noex ;
extern int	getnwnum_rp(NETENT *,char *,int,int,uint32_t) noex ;

EXTERNC_end


#endif /* UCSYSNW_INCLUDE */


