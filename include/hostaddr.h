/* hostaddr HEADER */
/* lang=C20 */

/* manipulate host entry structures */
/* version %I% last-modified %G% */


/* Copyright © 2005 David A­D­ Morano.  All rights reserved. */

#ifndef	HOSTADDR_INCLUDE
#define	HOSTADDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<usystem.h>


#define	HOSTADDR_MAGIC		0x73625196
#define	HOSTADDR		struct hostaddr_head
#define	HOSTADDR_CUR		struct hostaddr_cursor


struct hostaddr_head {
	ADDRINFO	*aip ;
	ADDRINFO	**resarr ;
	cchar		*ehostname ;
	uint		magic ;
	int		n ;
} ;

struct hostaddr_cursor {
	int		i ;
} ;

typedef HOSTADDR		hostaddr ;
typedef HOSTADDR_CUR		hostaddr_cur ;

EXTERNC_begin

extern int hostaddr_start(hostaddr *,cchar *,cchar *,ADDRINFO *) noex ;
extern int hostaddr_getcanonical(hostaddr *,cchar **) noex ;
extern int hostaddr_curbegin(hostaddr *,hostaddr_cur *) noex ;
extern int hostaddr_curend(hostaddr *,hostaddr_cur *) noex ;
extern int hostaddr_curenum(hostaddr *,hostaddr_cur *,ADDRINFO **) noex ;
extern int hostaddr_finish(hostaddr *) noex ;

EXTERNC_end


#endif /* HOSTADDR_INCLUDE */


