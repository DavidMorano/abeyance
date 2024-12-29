/* inetdomainname HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 */

/* get the local node name and INET domain name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	inetdomainname

	Description:
	This file contains some support for the UNIX® INETDOMAINNAME related
	operations.

*******************************************************************************/

#ifndef	INETDOMAINNAME_INCLUDE
#define	INETDOMAINNAME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern uint	inetdomainname(char *,int,cchar *,cchar *) noex ;

EXTERNC_end


#endif /* INETDOMAINNAME_INCLUDE */


