/* mkuix HEADER */
/* lang=C20 */

/* make some common names from USERINFO data */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKUIX_INCLUDE
#define	MKUIX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<userinfo.h>


EXTERNC_begin

extern int mkuiname(char *,int,userinfo *) noex ;
extern int mkuibang(char *,int,userinfo *) noex ;

EXTERNC_end


#endif /* MKUIX_INCLUDE */


