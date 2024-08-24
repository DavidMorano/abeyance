/* comsatmsg HEADER */
/* lang=C20 */

/* create and parse COMSAT messages */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	COMSATMSG_INCLUDE
#define	COMSATMSG_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<unistd.h>		/* |off_t| */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


#ifndef	USERNAMELEN
#define	USERNAMELEN	32
#endif

#define	COMSATMSG_MO	struct comsatmsg_mo


struct comsatmsg_mo {
	char		username[USERNAMELEN + 1] ;
	char		fname[MAXNAMELEN + 1] ;
	ulong		offset ;
} ;


/* message types */
enum comsatmsgtypes {
	comsatmsgtype_mo,
	comsatmsgtype_overlast
} ;


EXTERNC_begin

extern int comsatmsg_mo(COMSATMSG_MO *,int,char *,int) noex ;

EXTERNC_end


#endif /* COMSATMSG_INCLUDE */


