/* calmgr HEADER */
/* lang=C20 */

/* calendar manager object */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	CALMGR_INCLUDE
#define	CALMGR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<vechand.h>
#include	<vecobj.h>

#include	"calyears.h"
#include	"calent.h"
#include	"cyi.h"
#include	"calcite.h"


#define	CALMGR		struct calmgr_head
#define	CALMGR_Q	CALCITE
#define	CALMGR_CUR	struct calmgr_cursor
#define	CALMGR_FL	struct calmgr_flags


struct calmgr_cursor {
	void		*results ;
	uint		magic ;
	uint		nresults ;
	int		i ;
} ;

struct calmgr_flags {
	uint		idxes:1 ;		/* IDXES container open */
} ;

struct calmgr_head {
	cchar		*dn ;			/* DB directory-name */
	cchar 		*cn ;			/* DB calendar-name */
	cchar		*a ;			/* memory-allocations */
	cchar		*idxdname ;
	void		*calyears ;
	cchar		*mapdata ;		/* DB memory-map address */
	vechand		idxes ;			/* indices */
	time_t		ti_db ;			/* DB file modification */
	time_t		ti_map ;		/* DB map */
	time_t		ti_lastcheck ;		/* DB last check */
	size_t		fsize ;			/* DB file size */
	size_t		mapsize ;		/* DB map length */
	CALMGR_FL	f ;
	int		nentries ;		/* DB entries */
	int		cidx ;			/* parent index (ordinal) */
} ;

typedef CALMGR		calmgr ;
typedef CALMGR_CUR	calmgr_cur ;

EXTERNC_begin

extern int calmgr_start(calmgr *,CALYEARS *,int,cchar *,cchar *) noex ;
extern int calmgr_finish(calmgr *) noex ;
extern int calmgr_lookup(calmgr *,vecobj *,CALCITE *) noex ;
extern int calmgr_gethash(calmgr *,CALENT *,uint *) noex ;
extern int calmgr_getci(calmgr *) noex ;
extern int calmgr_getbase(calmgr *,cchar **) noex ;
extern int calmgr_loadbuf(calmgr *,char *,int,CALENT *) noex ;
extern int calmgr_audit(calmgr *) noex ;

EXTERNC_end


#endif /* CALMGR_INCLUDE */


