/* mktmp HEADER */
/* lang=C20 */

/* make a temporary file of a certain type */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKTMP_INCLUDE
#define	MKTMP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int mktmpdir(char *,cchar *,mode_t) noex ;
extern int mktmpusers(char *) noex ;
extern int mktmpuser(char *) noex ;
extern int mktmpuserx(char *,cchar *) noex ;
extern int mktmpuserdir(char *,cchar *,cchar *,mode_t) noex ;
extern int mktmpfile(char *,cchar *,mode_t) noex ;
extern int mktmplock(char *,cchar *,mode_t) noex ;

EXTERNC_end


#endif /* MKTMP_INCLUDE */


