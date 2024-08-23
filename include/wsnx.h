/* wsnx HEADER */
/* lang=C20 */

/* counted wide-c-string operations */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	WSNX_INCLUDE
#define	WSNX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<stddef.h>		/* |wchar_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int wsncolstr(int,int,const wchar_t *,int) noex ;
extern int wsnwcpynarrow(wchar_t *,int,cchar *,int) noex ;

EXTERNC_end


#endif /* WSNX_INCLUDE */


