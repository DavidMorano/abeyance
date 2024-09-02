/* ucgetpid HEADER */
/* lang=C20 */

/* slightly tuned UNIX® look-alike for |getpid(2)| */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCGETPID_INCLUDE
#define	UCGETPID_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* system types */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	uc_getpid() noex ;
extern int	uc_setpid(pid_t) noex ;

EXTERNC_end


#endif /* UCGETPID_INCLUDE */


