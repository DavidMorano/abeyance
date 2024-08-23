/* snwcpyxc HEADER */
/* lang=C20 */

/* copy a c-string to a given case */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SNWCPYXC_INCLUDE
#define	SNWCPYXC_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int snwcpybc(char *,int,cchar *,int) noex ;
extern int snwcpylc(char *,int,cchar *,int) noex ;
extern int snwcpyuc(char *,int,cchar *,int) noex ;
extern int snwcpyfc(char *,int,cchar *,int) noex ;

EXTERNC_end


#endif /* SNWCPYXC_INCLUDE */


