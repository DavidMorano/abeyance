/* nodedb HEADER */
/* lang=C20 */

/* magement for the NODE-DB file */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NODEDB_INCLUDE
#define	NODEDB_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<limits.h>
#include	<netdb.h>
#include	<usystem.h>		/* for |ino_t| */
#include	<vecobj.h>
#include	<hdb.h>
#include	<localmisc.h>


#define	NODEDB_MAGIC		0x31415926
#define	NODEDB			struct nodedb_head
#define	NODEDB_CUR		struct nodedb_cursor
#define	NODEDB_ENT		struct nodedb_entry

#define	NODEDB_LSVC		NODENAMELEN
#define	NODEDB_LCLU		NODENAMELEN
#define	NODEDB_LSYS		NODENAMELEN

#define	NODEDB_NFILES		3
#define	NODEDB_DEFENTS		10
#define	NODEDB_ENTLEN		(3*NODENAMELEN)


struct nodedb_cursor {
	hdb_cur		*ecp ;
	int		i ;
} ;

struct nodedb_head {
	vecobj		*filep ;		/* files */
	hdb		*entsp ;
	time_t		checktime ;
	uint		magic ;
	int		cursors ;
} ;

struct nodedb_entry {
	cchar		*(*keys)[2] ;
	cchar		*svc ;
	cchar		*clu ;
	cchar		*sys ;
	int		nkeys ;
	int		esize ;		/* entry-size */
	int		fi ;		/* file index */
} ;

typedef NODEDB		nodedb ;
typedef NODEDB_CUR	nodedb_cur ;
typedef NODEDB_ENT	nodedb_ent ;

EXTERNC_begin

extern int nodedb_open(nodedb *,cchar *) noex ;
extern int nodedb_fileadd(nodedb *,cchar *) noex ;
extern int nodedb_curbegin(nodedb *,nodedb_cur *) noex ;
extern int nodedb_curend(nodedb *,nodedb_cur *) noex ;
extern int nodedb_fetch(nodedb *,cchar *,nodedb_cur *,
		nodedb_ent *,char *,int) noex ;
extern int nodedb_enum(nodedb *,nodedb_cur *,nodedb_ent *,char *,int) noex ;
extern int nodedb_check(nodedb *,time_t) noex ;
extern int nodedb_close(nodedb *) noex ;

EXTERNC_end


#endif /* NODEDB_INCLUDE */


