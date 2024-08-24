/* getpwd HEADER */
/* lang=C20 */

/* get the Present-Working-Directory (PWD) of the process */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETPWD_INCLUDE
#define	GETPWD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int	getpwd(char *,int) noex ;
extern int	getpwds(USTAT *,char *,int) noex ;

EXTERNC_end


#endif /* GETPWD_INCLUDE */


