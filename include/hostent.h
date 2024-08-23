/* hostent HEADER */
/* lang=C20 */

/* manipulate host entry structures */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	HOSTENT_INCLUDE
#define	HOSTENT_INCLUDE 


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<string.h>
#include	<usystem.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>		/* extra typedefs */


#define	HOSTENT		struct hostent
#define	HOSTENT_CUR	struct hostent_cursor


struct hostent_cursor {
	int		i ;
} ;

typedef HOSTENT_CUR	hostent_cur ;

EXTERNC_begin

extern int hostent_getofficial(HOSTENT *,cchar **) noex ;
extern int hostent_getcanonical(HOSTENT *,cchar **) noex ;
extern int hostent_getaf(HOSTENT *) noex ;
extern int hostent_getalen(HOSTENT *) noex ;
extern int hostent_curbegin(HOSTENT *,hostent_cur *) noex ;
extern int hostent_curend(HOSTENT *,hostent_cur *) noex ;
extern int hostent_enumname(HOSTENT *,hostent_cur *,cchar **) noex ;
extern int hostent_enumaddr(HOSTENT *,hostent_cur *,const uchar **) noex ;
extern int hostent_size(HOSTENT *) noex ;
extern int hostent_load(HOSTENT *,char *,int,const HOSTENT *) noex ;

EXTERNC_end


#endif /* HOSTENT_INCLUDE */


