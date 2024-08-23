/* sysusernames HEADER */
/* lang=C20 */

/* thread-safe enumeration of a system data-base */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSUSERNAMES_INCLUDE
#define	SYSUSERNAMES_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<filemap.h>


#define	SYSUSERNAMES		struct sysusernames_head
#define	SYSUSERNAMES_MAGIC	0x88776218
#define	SYSUSERNAMES_FNAME	"/sysdb/usernames"


struct sysusernames_head {
	filemap		*fmp ;
	uint		magic ;
} ;

typedef SYSUSERNAMES	sysusernames ;

EXTERNC_begin

extern int sysusernames_open(sysusernames *,cchar *) noex ;
extern int sysusernames_close(sysusernames *) noex ;
extern int sysusernames_readent(sysusernames *,char *,int) noex ;
extern int sysusernames_reset(sysusernames *) noex ;

EXTERNC_end


#endif /* SYSUSERNAMES_INCLUDE */


