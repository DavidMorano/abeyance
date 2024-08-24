/* tmpmailboxes HEADER */
/* lang=C20 */

/* do something w/ temporary mailboxes */
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
	I do something w/ temporary mailboxes.  I am sure that this
	has some purpose someplace.

	Synopsis:
	int getsrcname(char *rbuf,int rlen) noex

	Arguments:
	rbuf		result buffer pointer
	rlen		result buffer length

	Returns:
	>=0		0=BSD, 1=SYSV
	<0		error (system-return)

*******************************************************************************/

#ifndef	TMPMAILBOXES_INCLUDE
#define	TMPMAILBOXES_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin
extern int	tmpmailboxes(char *,int) noex ;
EXTERNC_end


#endif /* TMPMAILBOXES_INCLUDE */


