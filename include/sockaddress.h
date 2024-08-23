/* sockaddress HEADER */
/* lang=C20 */

/* manipulate socket addresses */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-01-13, David A­D­ Morano
	This object module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SOCKADDRESS_INCLUDE
#define	SOCKADDRESS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<sys/un.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<usystem.h>
#include	<localmisc.h>	/* |MAXPATHLEN| */


#define	SOCKADDRESS		union sockaddress_head
#define	SOCKADDRESS_PA		struct sockaddress_path
#define	SOCKADDRESS_IN4		struct sockaddress_inet4
#define	SOCKADDRESS_IN6		struct sockaddress_inet6

#define	SOCKADDRESS_LEN		sizeof(union sockaddress_head)
#define	SOCKADDRESS_NAMELEN	sizeof(union sockaddress_head)
#define	SOCKADDRESS_MAXPATH	MAXPATHLEN


struct sockaddress_path {
	ushort	naf ;			/* address space */
	char	fpath[SOCKADDRESS_MAXPATH + 1] ;
} ;

struct sockaddress_inet4 {
	ushort	naf ;			/* address space */
	ushort	nport ;			/* port */
	uchar	a[4] ;			/* 32-bit address */
} ;

struct sockaddress_inet6 {
	ushort	naf ;			/* address space */
	ushort	nport ;			/* port */
	uint	nflow ;			/* flow label */
	uchar	a[16] ;			/* 128-bit address */
	uint	scope ;			/* scope crap */
	uchar	dummy[4] ;		/* implementation defined */
} ;

union sockaddress_head {
	SOCKADDR		a_unspec ;
	SOCKADDR_UN		a_unix ;
	SOCKADDR_IN4		a_in ;
	SOCKADDR_IN6		a_in6 ;
	SOCKADDRESS_PA		a_path ;
	SOCKADDRESS_IN4		a_inet4 ;
	SOCKADDRESS_IN6		a_inet6 ;
	unsigned char		str[32] ; /* general future */
} ;

typedef	SOCKADDRESS		sockaddress ;
typedef	SOCKADDRESS_PA		sockaddress_pa ;
typedef	SOCKADDRESS_IN4		sockaddress_in4 ;
typedef	SOCKADDRESS_IN6		sockaddress_in6 ;

EXTERNC_begin

extern int sockaddress_start(sockaddress *,int,cvoid *,int,int) noex ;
extern int sockaddress_startaddr(sockaddress *,int,cvoid *,int,int,int) noex ;
extern int sockaddress_getlen(sockaddress *) noex ;
extern int sockaddress_getaddrlen(sockaddress *) noex ;
extern int sockaddress_gethex(sockaddress *,char *,int) noex ;
extern int sockaddress_getaf(sockaddress *) noex ;
extern int sockaddress_getport(sockaddress *) noex ;
extern int sockaddress_getflow(sockaddress *,uint *) noex ;
extern int sockaddress_getaddr(sockaddress *,void *,int) noex ;
extern int sockaddress_getscope(sockaddress *,uint *) noex ;
extern int sockaddress_getextra(sockaddress *,uint *) noex ;
extern int sockaddress_putaf(sockaddress *,int) noex ;
extern int sockaddress_putport(sockaddress *,int) noex ;
extern int sockaddress_putaddr(sockaddress *,cvoid *) noex ;
extern int sockaddress_finish(sockaddress *) noex ;

EXTERNC_end


#endif /* SOCKADDRESS_INCLUDE */


