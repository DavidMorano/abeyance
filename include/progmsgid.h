/* progmsgid HEADER */
/* lang=C++20 */

/* create a mail message ID */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-09-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	progmsgid

	Description:
	This subroutine is used to create a mail message ID for
	certain PCS programs.

	Synopsis:
	int progmsgid(proginfo *pip,char *mbuf,int mlen,int serial) noex

*******************************************************************************/

#ifndef	PROGMSGID_INCLUDE
#define	PROGMSGID_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* must be before others */
#include	<stdarg.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<userinfo.h>

#include	<proginfo.hh>


EXTERNC_begin

extern int progmsgid(proginfo *,char *,int,int) noex ;

EXTERNC_end


#endif /* __cplusplus */
#endif /* PROGMSGID_INCLUDE */


