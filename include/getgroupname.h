/* getgroupname HEADER */
/* lang=C20 */

/* get a group name (from the system account database) for current process */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETGROUPNAME_INCLUDE
#define	GETGROUPNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |gid_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getgroupname(char *,int,gid_t) noex ;

EXTERNC_end


#endif /* GETGROUPNAME_INCLUDE */


