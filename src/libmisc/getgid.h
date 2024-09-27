/* getgid HEADER */
/* lang=C20 */

/* get the GID for a given group-name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-08-20, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright (c) 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETGID_INCLUDE
#define	GETGID_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |gid_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int getgid_name(cchar *,int) noex ;
extern int getgid_group(cchar *,int) noex ;
extern int getgid_def(cchar *,gid_t) noex ;

EXTERNC_end


#endif /* GETGID_INCLUDE */


