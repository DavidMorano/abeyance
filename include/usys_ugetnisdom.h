/* usys_ugetnisdom HEADER */
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
	ugetnisdom

	Description:
	This provides a means to get the NIS domain-name from the
	operating system in an OS-independent way by regualr callers.

	Synosis:
	int ugetnisdom(char *rbuf,int rlen) noex

	Arguments:
	rbuf		result buffer pointer
	rlen		result buffer length

	Returns:
	>=0		length of result
	<0		error code (system-return)

*******************************************************************************/

#ifndef	USYSUGETNISDOM_INCLUDE
#define	USYSUGETNISDOM_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


namespace libu {
    extern sysret_t ugetnisdom(char *,int) noex ;
}


#endif /* __cplusplus */
#endif /* USYSUGETNISDOM_INCLUDE */


