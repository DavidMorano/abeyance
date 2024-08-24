/* mailaddr EADPER */
/* lang=C20 */

/* parse email route addresses into host and local parts */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILADDR_INCLUDE
#define	MAILADDR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>		/* |MAILADDRLEN| */


/* mail address */
#ifndef	MAILADDRLEN
#define	MAILADDRLEN		(3 * MAXHOSTNAMELEN)
#endif

#define	MAILADDRTYPE_NOHOST	-1
#define	MAILADDRTYPE_LOCAL	0
#define	MAILADDRTYPE_UUCP	1
#define	MAILADDRTYPE_ARPA	2
#define	MAILADDRTYPE_ARPAROUTE	3

#define	MAILADDR_LOCALHOST	"*LOCAL*"
#define	LOCALHOSTPART		"*LOCAL*"


enum mailaddrs {
	mailaddrtype_local,
	mailaddrtype_uucp,
	mailaddrtype_arpa,
	mailaddrtype_arparoute,
	mailaddrtype_overlast
} ;

EXTERNC_begin

extern int mailaddrparse(cchar *,int,char *,char *) noex ;
extern int mailaddrjoin(char *,int,cchar *,cchar *,int) noex ;
extern int mailaddrarpa(char *,int,cchar *,cchar *,int) noex ;

EXTERNC_end


#endif /* MAILADDR_INCLUDE */


