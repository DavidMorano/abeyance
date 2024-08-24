/* getmailgid HEADER */
/* lang=C20 */

/* get the mail-spool-area GID */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-08-20, David A­D­ Morano
	This was written to provide this function in a single
	subroutine.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETMAILGID_INCLUDE
#define	GETMAILGID_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |gid_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getmailgid(cchar *,gid_t) noex ;

EXTERNC_end


#endif /* GETMAILGID_INCLUDE */


