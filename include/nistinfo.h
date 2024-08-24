/* nistinfo HEADER */
/* lang=C++20 */

/* NIST information */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NISTINFO_INCLUDE
#define	NISTINFO_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>		/* |TIMEBUFLEN| */


#define	NISTINFO		struct nistinfo
#define	NISTINFO_BUFLEN		TIMEBUFLEN
#define	NISTINFO_ORGLEN		16


struct nistinfo {
	int		tt ;
	int		l ;
	int		h ;
	int		adv ;
	char		org[NISTINFO_ORGLEN+1] ;
} ;


#endif /* NISTINFO_INCLUDE */


