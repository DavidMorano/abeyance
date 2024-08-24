/* getsrcname HEADER */
/* lang=C20 */

/* get the source (network) name of a network socket */
/* version %I% last-modified %G% */


/* revision history:

	= 2003-03-04, David A.D. Morano
	This was written from scratch.

*/

/* Copyright © 2003 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	getsrcname

	Description:
	This subroutine returns (if it can) the source network name
	associated with a network-connected socket.

	Synopsis:
	int getsrcname(char *rbuf,int rlen,int s) noex

	Arguments:
	rbuf		result buffer pointer
	rlen		result buffer length
	s		socket

	Returns:
	>=0		0=BSD, 1=SYSV
	<0		error (system-return)

*******************************************************************************/

#ifndef	GETSRCNAME_INCLUDE
#define	GETSRCNAME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin
extern int	getsrcname(char *,int,int) noex ;
EXTERNC_end


#endif /* GETSRCNAME_INCLUDE */


