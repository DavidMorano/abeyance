/* ucgetsv HEADER */
/* lang=C20 */

/* UNIX® C-language system database access (UCGET) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This program was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCGETSV_INCLUDE
#define	UCGETSV_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<ucentsv.h>


EXTERNC_begin

extern int	uc_getsvbegin(int) noex ;
extern int	uc_getsvent(ucentsv *,char *,int) noex ;
extern int	uc_getsvnam(ucentsv *,char *,int,cchar *,cchar *) noex ;
extern int	uc_getsvnum(ucentsv *,char *,int,int,cchar *) noex ;
extern int	uc_getsvend() noex ;

EXTERNC_end


#endif /* UCGETSV_INCLUDE */


