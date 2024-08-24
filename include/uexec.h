/* uexec HEADER (UNIX® file operations) */
/* lang=C20 */

/* translation layer interface for UNIX® equivalents */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	u_execve

	Description:
	All of the UNIX® system calls that use (operate on) a
	UNIX® process.

*******************************************************************************/

#ifndef	UEXEC_INCLUDE
#define	UEXEC_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>		/* system types */
#include	<unistd.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usupport.h>


EXTERNC_begin

extern int	u_execve(cchar *,mainv,mainv) noex ;
extern int	u_execv(cchar *,mainv) noex ;
extern int	u_execvp(cchar *,mainv) noex ;

EXTERNC_end


#endif /* UEXEC_INCLUDE */


