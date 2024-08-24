/* ucuserattr HEADER */
/* lang=C20 */

/* UNIX® C-language system database access (UCGET) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCUSERATTR_INCLUDE
#define	UCUSERATTR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<userattr.h>		/* <- the money shot */


EXTERNC_begin

extern int	uc_userattrbegin() noex ;
extern int	uc_userattrent(userattr **) noex ;
extern int	uc_userattrnam(userattr **,cchar *) noex ;
extern int	uc_userattruid(userattr **,uid_t) noex ;
extern int	uc_userattrfree(userattr *) noex ;
extern int	uc_userattrend() noex ;

EXTERNC_end


#endif /* UCUSERATTR_INCLUDE */


