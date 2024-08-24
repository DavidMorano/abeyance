/* mkutmpid HEADER */
/* lang=C20 */

/* make a UTMPX entry ID (c_string) */
/* version %I% last-modified %G% */


/* revision history:

	= 2003-10-09, David A­D­ Morano
	I finally made this because so many programs have difficulty
	in creating UTMP ID values.

*/

/* Copyright (c) 2003 David A­D­ Morano.  All rights reserved. */

#ifndef	MKUTMPID_INCLUDE
#define	MKUTMPID_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

int mkutmpid(char *,int,cchar *,int) noex ;

EXTERNC_end


#endif /* MKUTMPID_INCLUDE */


