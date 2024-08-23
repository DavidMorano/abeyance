/* ucgetpr HEADER */
/* lang=C20 */

/* UNIX® C-language system database access (UCGET) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This program was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCGETPR_INCLUDE
#define	UCGETPR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<ucentpr.h>


EXTERNC_begin

extern int	uc_getprbegin(int) noex ;
extern int	uc_getprent(ucentpr *,char *,int) noex ;
extern int	uc_getprnam(ucentpr *,char *,int,cchar *) noex ;
extern int	uc_getprnum(ucentpr *,char *,int,int) noex ;
extern int	uc_getprend() noex ;

EXTERNC_end


#endif /* UCGETPR_INCLUDE */


