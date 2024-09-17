/* clusterdb HEADER */
/* lang=C20 */

/* manage a database of cluster names */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CLUSTERDB_INCLUDE
#define	CLUSTERDB_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<limits.h>
#include	<netdb.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<kvsfile.h>


#define	CLUSTERDB	struct clusterdb_head
#define	CLUSTERDB_CUR	struct clusterdb_cursor


struct clusterdb_cursor {
	kvsfile_cur	*kcurp ;
} ;

struct clusterdb_head {
	kvsfile		*ctp ;
	uint		magic ;
} ;

typedef CLUSTERDB	clusterdb ;
typedef CLUSTERDB_CUR	clusterdb_cur ;

EXTERNC_begin

extern int clusterdb_open(clusterdb *,cchar *) noex ;
extern int clusterdb_fileadd(clusterdb *,cchar *) noex ;
extern int clusterdb_curbegin(clusterdb *,clusterdb_cur *) noex ;
extern int clusterdb_curend(clusterdb *,clusterdb_cur *) noex ;
extern int clusterdb_curenumcluster(clusterdb *,clusterdb_cur *,
		char *,int) noex ;
extern int clusterdb_curenum(clusterdb *,clusterdb_cur *,
		char *,int,char *,int) noex ;
extern int clusterdb_curfetch(clusterdb *,cchar *,clusterdb_cur *,
		char *,int) noex ;
extern int clusterdb_curfetchrev(clusterdb *,cchar *,clusterdb_cur *,
		char *,int) noex ;
extern int clusterdb_check(clusterdb *,time_t) noex ;
extern int clusterdb_close(clusterdb *) noex ;

EXTERNC_end


#endif /* CLUSTERDB_INCLUDE */


