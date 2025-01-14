/* nifinfo HEADER (Network-InterFace) */
/* encoding=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* manage Network-InterFace information */
/* version %I% last-modified %G% */


/* Copyright © 1994 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	nifinfo

	Description: 
	These subroutines form the public calling interface for
	accessing Network-InterFace information.

*******************************************************************************/

#ifndef	NIFINFO_INCLUDE
#define	NIFINFO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<net/if.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<string.h>
#include	<usystem.h>
#include	<localmisc.h>		/* |REALNAMELEN| */


#define	NIFINFO_MAGIC		0x73638196
#define	NIFINFO			struct nifinfo_head
#define	NIFINFO_ENT		struct nifinfo_e
#define	NIFINFO_CUR		struct nifinfo_c
#define	NIFINFO_ADDR		union nifinfo_addr
#define	NIFINFO_NSZ		REALNAMELEN


union nifinfo_address {
	struct in6_addr	a6 ;
	struct in_addr	a4 ;
} ;

struct nifinfo_entry {
	uint64_t	flags ;		/* interface flags */
	NIFINFO_ADDR	addr ;		/* interface address */
	int		index ;		/* interface index */
	int		af ;		/* address family */
	int		alen ;		/* address length */
	char		inter[NIFINFO_NSZ + 1] ; /* interface name */
} ;

struct nifinfo_head {
	NIFINFO_ENT	*a ;
	uint		magic ;
	int		n ;
} ;

struct nifinfo_cursor {
	int		i ;
} ;

typedef	NIFINFO			nifinfo ;
typedef	NIFINFO_ENT		nifinfo_ent ;
typedef	NIFINFO_CUR		nifinfo_cur ;
typedef	NIFINFO_ADDR		nifinfo_addr ;

EXTERNC_begin

extern int nifinfo_start(nifinfo *) noex ;
extern int nifinfo_get(nifinfo *,int,nifinfo_ent **) noex ;
extern int nifinfo_match(nifinfo *,int,void *,int) noex ;
extern int nifinfo_finish(nifinfo *) noex ;

EXTERNC_end


#endif /* NIFINFO_INCLUDE */


