/* usys_usendfile HEADER */
/* lang=C20 */

/* operating support for the common |sendfile(3c)| subroutines */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	usendfile

	Description:
	This follows the version on both Linux and Solaris® (and
	its derivatives).

	Synosis:
	int usendfile(int fd,int s,off_t fo,size_t c) noex

	Arguments:
	fd		file-descriptor (to read from)
	s		socket (to write to)
	fo		starting file offset
	c		count of bytes to send

	Returns:
	>=0		length of result
	<0		error (system-return)

*******************************************************************************/

#ifndef	USYSUSENDFILE_INCLUDE
#define	USYSUSENDFILE_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<dirent.h>		/* |dirent| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


namespace usys {
    extern sysret_t usendfile(int,int,off_t,size_t) noex ;
}


#endif /* __cplusplus */
#endif /* USYSUSENDFILE_INCLUDE */


