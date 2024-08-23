/* mailmsgmathdr HEADER */
/* lang=C20 */

/* match on a message header (returns the key-name) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSGMATHDR_INCLUDE
#define	MAILMSGMATHDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


EXTERNC_begin

extern int mailmsgmathdr(cchar *,int,int *) noex ;

EXTERNC_end


#endif /* MAILMSGMATHDR_INCLUDE */


