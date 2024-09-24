/* connection HEADER */
/* lang=C20 */

/* manipulate INET connection information */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CONNECTION_INCLUDE
#define	CONNECTION_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vecstr.h>
#include	<sockaddress.h>
#include	<localmisc.h>		/* various constants (see below) */


#define	CONNECTION		struct connection_head
#define	CONNECTION_FL		struct connection_flags
#define	CONNECTION_PEERNAMELEN	MAX(MAXPATHLEN,MAXHOSTNAMELEN)


struct connection_flags {
	uint		inet:1 ;
	uint		trans:1 ;
	uint		sa:1 ;
	uint		addr:1 ;
	uint		inetdomain:1 ;	/* allocated */
} ;

struct connection_head {
	cchar		*inetdomain ;	/* local domain name */
	cchar		*peername ;	/* dynamically allocated */
	cchar		*pr ;		/* dynamically allocated */
	sockaddress	*sap ;
	INADDR		netipaddr ;
	CONNECTION_FL	f ;
	int		sal ;
	int		s ;
} ;

typedef	CONNECTION	connection ;
typedef	CONNECTION_FL	connection_fl ;

EXTERNC_begin

extern int connection_start(connection *,cchar *) noex ;
extern int connection_socklocname(connection *,char *,int,int) noex ;
extern int connection_sockremname(connection *,char *,int,int) noex ;
extern int connection_peername(connection *,sockaddress *,int,char *,int) noex ;
extern int connection_mknames(connection *,vecstr *) noex ;
extern int connection_finish(connection *) noex ;

EXTERNC_end


#endif /* CONNECTION_INCLUDE */


