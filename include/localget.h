/* localget HEADER */
/* lang=C20 */

/* LOCAL get values */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LOCALGET_INCLUDE
#define	LOCALGET_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int localgetnetload(cchar *,char *,int) noex ;
extern int localgetorg(cchar *,char *,int,cchar *) noex ;
extern int localgetorgcode(cchar *,char *,int,cchar *) noex ;
extern int localgetorgloc(cchar *,char *,int,cchar *) noex ;
extern int localgetsystat(cchar *,char *,int) noex ;

EXTERNC_end


#endif /* LOCALGET_INCLUDE */


