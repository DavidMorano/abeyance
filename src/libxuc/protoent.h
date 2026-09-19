/* protoent HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	PROTOENT_INCLUDE
#define	PROTOENT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<string.h>
#include	<usystem.h>
#include	<localmisc.h>		/* extra typedefs */


#define	PROTOENT	struct protoent
#define	PROTOENT_CUR	struct protoent_cursor


struct protoent_curosor {
	int		i ;
} ;

typedef PROTOENT_CUR	protoent_cur ;

EXTERNC_begin

extern int uc_getprotobyname(PROTOENT *,char *,int,cchar *) noex ;
extern int uc_getprotobynumber(PROTOENT *,char *,int,int,int) noex ;
extern int uc_getprotoent(PROTOENT *,char *,int) noex ;

EXTERNC_end


#endif /* PROTOENT_INCLUDE */


