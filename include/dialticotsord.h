/* dialticotsord HEADER */
/* lang=C20 */

/* dial out to a TI-CO-TS-ORD service */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	dialticotsord

	Origin:
	-Dial
	-Transport
	-Interface
	-Connection
	-Oriented
	-Transport
	-Service
	-Orderly
	-Release

*******************************************************************************/

#ifndef	DIALTICOTSORD_INCLUDE
#define	DIALTICOTSORD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<dialopts.h>
#include	<dialtcpnls.h>


EXTERNC_begin

extern int dialticotsord(cchar,int,int,int) noex ;
extern int dialticotsordnls(cc *,int,cc *,int,int) noex ;
extern int dialticotsordmux(cc *,int,cc *,mainv,int,int) noex ;

EXTERNC_end


#endif /* DIALTICOTSORD_INCLUDE */


