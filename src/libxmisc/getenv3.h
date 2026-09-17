/* getenv3 HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* get the value of an environment variable */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This was written from scratch.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	getenv3

	Description:
	This subroutine searches for an environment variable (by
	key) and returns the value if the variable (key-value pair)
	is found.

	Synopsis:
	cchar *getenv3(cchar *,int,cchar **) noex

	Arguments:

	Returns:
	>=0		0=BSD, 1=SYSV
	<0		error (system-return)

*******************************************************************************/

#ifndef	GETENV3_INCLUDE
#define	GETENV3_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */


EXTERNC_begin
extern int	getenv3(cchar *,int,cchar **) noex ;
EXTERNC_end


#endif /* GETENV3_INCLUDE */


