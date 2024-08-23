/* bufprintf HEADER */
/* lang=C20 */

/* subroutine to process a format-string into a buffer */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	BUFPRINTF_INCLUDE
#define	BUFPRINTF_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stdarg.h>		/* |va_list| */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int bufprintf(char *,int,cchar *,...) noex ;
extern int bufvprintf(char *,int,cchar *,va_list) noex ;

EXTERNC_end


#endif /* BUFPRINTF_INCLUDE */


