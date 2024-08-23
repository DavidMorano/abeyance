/* usys_ugetdents HEADER */
/* lang=C20 */

/* operating support for retrieving the NIS domain-name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	ugetdents

	Description:
	This provides a means to get the NIS domain-name from the
	operating system in an OS-independent way by regualr callers.

	Synosis:
	int ugetdents(int fd,dirent *rbuf,int rlen) noex

	Arguments:
	fd		file-descriptor
	rbuf		result buffer pointer
	rlen		result buffer length

	Returns:
	>=0		length of result
	<0		error (system-return)

*******************************************************************************/

#ifndef	USYSUGETDENTS_INCLUDE
#define	USYSUGETDENTS_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<dirent.h>		/* |dirent| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usys_typedefs.h>	/* |dirent_t| */


namespace usys {
    extern sysret_t ugetdents(int,dirent_t *,int) noex ;
}


#endif /* __cplusplus */
#endif /* USYSUGETDENTS_INCLUDE */


