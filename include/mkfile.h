/* mkfile HEADER */
/* lang=C20 */

/* make a file of a certain type */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKFILE_INCLUDE
#define	MKFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int mkjobfile(char *,cchar *,mode_t) noex ;
extern int mkartfile(char *,cchar *,cchar *,int,mode_t) noex ;
extern int mkdatefile(char *,cchar *,cchar *,mode_t) noex ;

EXTERNC_end


#endif /* MKFILE_INCLUDE */


