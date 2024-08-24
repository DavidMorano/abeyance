/* sysusershells HEADER */
/* lang=C20 */

/* thread-safe enumeration of a system data-base */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSUSERSHELLS_INCLUDE
#define	SYSUSERSHELLS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<filemap.h>


#define	SYSUSERSHELLS		struct sysusershells_head
#define	SYSUSERSHELLS_MAGIC	0x88776229
#define	SYSUSERSHELLS_FNAME	"/sysdb/shells"


struct sysusershells_head {
	filemap		*fmp ;
	uint		magic ;
} ;

typedef SYSUSERSHELLS	sysusershells ;

EXTERNC_begin

extern int sysusershells_open(sysusershells *,cchar *) noex ;
extern int sysusershells_close(sysusershells *) noex ;
extern int sysusershells_readent(sysusershells *,char *,int) noex ;
extern int sysusershells_reset(sysusershells *) noex ;

EXTERNC_end


#endif /* SYSUSERSHELLS_INCLUDE */


