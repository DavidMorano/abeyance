/* isnot HEADER */
/* lang=C20 */

/* is an error code (per an integer) not part of a class of something? */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ISNOT_INCLUDE
#define	ISNOT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern bool isNotPresent(int) noex ;
extern bool isNotAccess(int) noex ;
extern bool isNotValid(int) noex ;
extern bool isNotLib(int) noex ;
extern bool isNotTerm(int) noex ;
extern bool isNotSupport(int) noex ;

static inline bool isInvalid(int rs) noex {
	return isNotValid(rs) ;
}

EXTERNC_end


#endif /* ISNOT_INCLUDE */


