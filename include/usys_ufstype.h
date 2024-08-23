/* usys_ufstype HEADER */
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
	ufstype

	Description:
	This provides a means to retrieve the file-system type-string
	from the underlying operating system.

	Synosis:
	int ufstype(char *rbuf,int rlen,int fd) noex

	Arguments:
	rbuf		result buffer pointer
	rlen		result buffer length
	fd		file-descriptor

	Returns:
	>=0		length of result
	<0		error code (system-return)

*******************************************************************************/

#ifndef	USYSUFSTYPE_INCLUDE
#define	USYSUFSTYPE_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


namespace libu {
    extern sysret_t ufstype(char *,int,int) noex ;
}


#endif /* __cplusplus */
#endif /* USYSUFSTYPE_INCLUDE */


