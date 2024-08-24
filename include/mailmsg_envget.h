/* mailmsg_envget HEADER */
/* lang=C++20 */

/* MAILMSG get-envelope */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSGENVGET_INCLUDE
#define	MAILMSGENVGET_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<mailmsg.h>


#define	MAILMSG_ENVDAT		struct mailmsg_envdata
#define	MAILMSG_ENVSTR		struct mailmsg_envstring


struct mailmsg_envstring {
	cchar		*ep ;
	int		el ;
} ;

struct mailmsg_envdata {
	MAILMSG_ENVSTR	a ;		/* address */
	MAILMSG_ENVSTR	d ;		/* ?? */
	MAILMSG_ENVSTR	r ;		/* route-address */
} ;

typedef MAILMSG_ENVSTR		mailmsg_envstr ;
typedef MAILMSG_ENVDAT		mailmsg_envdat ;

EXTERNC_begin

extern int	mailmsg_envget(mailmsg *,int,mailmsg_envdat *) noex ;

EXTERNC_end


#endif /* MAILMSGENVGET_INCLUDE */


