/* dial HEADER */
/* lang=C20 */

/* dial out to a TCP port */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DIAL_INCLUDE
#define	DIAL_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<dialopts.h>
#include	<dialuss.h>
#include	<dialudp.h>
#include	<dialtcp.h>
#include	<dialcprog.h>


EXTERNC_begin

extern int dialprog(cchar *,int,mainv,mainv,int *) noex ;
extern int dialuss(cchar *,int,int) noex ;
extern int dialusd(cchar *,int,int) noex ;
extern int dialussmux(cchar *,cchar *,mainv,int,int) noex ;
extern int dialussnls(cchar *,cchar *,int,int) noex ;
extern int dialpass(cchar *,int,int) noex ;
extern int dialticotsord(cchar *,int,int,int) noex ;
extern int dialticotsordmux(cc *,int,cc *,mainv,int,int) noex ;
extern int dialticotsordnls(cc *,int,cc *,int,int) noex ;

EXTERNC_end


#endif /* DIAL_INCLUDE */


