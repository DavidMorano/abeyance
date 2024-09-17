/* inetaddr HEADER */
/* lang=C20 */

/* object to manipulate INET adresses */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	INETADDR_INCLUDE
#define	INETADDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	INETADDR	union inetaddr_head


union inetaddr_head {
	struct in_addr	a ;
	char		straddr[sizeof(struct in_addr)] ;
} ;

typedef INETADDR	inetaddr ;

EXTERNC_begin

extern int inetaddr_start(inetaddr *,cvoid *) noex ;
extern int inetaddr_startstr(inetaddr *,cchar *,int) noex ;
extern int inetaddr_startdot(inetaddr *,cchar *,int) noex ;
extern int inetaddr_gethexaddr(inetaddr *,char *,int) noex ;
extern int inetaddr_getdotaddr(inetaddr *,char *,int) noex ;
extern int inetaddr_finish(inetaddr *) noex ;

EXTERNC_end


#endif /* INETADDR_INCLUDE */


