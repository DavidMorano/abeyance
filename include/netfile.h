/* netfile HEADER */
/* lang=C20 */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NETFILE_INCLUDE
#define	NETFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<vecitem.h>


#define	NETFILE		VECITEM
#define	NETFILE_ENT	struct netfile_entry


struct netfile_entry {
	cchar		*machine ;		/* machine name */
	cchar		*login ;		/* login name */
	cchar		*password ;
	cchar		*account ;		/* account name */
} ;

typedef	NETFILE		netfile ;
typedef	NETFILE_ENT	netfile_ent ;

EXTERNC_begin

extern int netfile_open(netfile *,cchar *) noex ;
extern int netfile_get(netfile *,int,NETFILE_ENT **) noex ;
extern int netfile_close(netfile *) noex ;

EXTERNC_end


#endif /* NETFILE_INCLUDE */


