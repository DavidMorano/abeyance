/* ddb HEADER (unneeded, unfinished) */
/* charset=ISO8859-1 */
/* lang=C20 */

/* domain data-base */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DDB_INCLUDE
#define	DDB_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<time.h>
#include	<vecstr.h>
#include	<hdb.h>


#define	DDB		struct ddb_head


struct ddb_head {
	cchar		*fname ;
	vecstr		*klp ;
	hdb		*dbp ;
	time_t		mtime ;
} ;

typedef	DDB		ddb_head ;

EXTERNC_begin

extern int ddb_open(DDB *,cchar *,cchar *) noex ;
extern int ddb_search(DDB *,cchar *,char *) noex ;
extern int ddb_close(DDB *) noex ;

EXTERNC_end


#endif /* DDB_INCLUDE */


