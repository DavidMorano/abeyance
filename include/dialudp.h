/* dialudp HEADER */
/* lang=C20 */

/* dial out to a TCP port */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DIALUDP_INCLUDE
#define	DIALUDP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<dialopts.h>


EXTERNC_begin

extern int dialudp(cchar *,cchar *,int,int,int) noex ;

EXTERNC_end


#endif /* DIALUDP_INCLUDE */


