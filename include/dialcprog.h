/* dialcprog HEADER */
/* lang=C20 */

/* set options on dialer file-descriptor */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DIALCPROG_INCLUDE
#define	DIALCPROG_INCLUDE


#include	<envstandards.h>	/* first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<dialopts.h>


EXTERNC_begin

extern int dialcprog(cchar *,cchar *,cchar *,mainv,mainv,int,int,int *) noex ;

EXTERNC_end


#endif /* DIALCPROG_INCLUDE */


