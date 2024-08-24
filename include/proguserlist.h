/* proguserlist HEADER */
/* lang=C++20 */

/* program-user-list-ing */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-03-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Manage a program user-list operation.

*******************************************************************************/

#ifndef	PROGUSERLIST_INCLUDE
#define	PROGUSERLIST_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* must be before others */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>

#include	<proginfo.hh>


EXTERNC_begin

extern int	proguserlist_begin(proginfo *) noex ;
extern int	proguserlist_end(proginfo *) noex ;
 
EXTERNC_end


#endif /* __cplusplus */
#endif /* PROGUSERLIST_INCLUDE */


