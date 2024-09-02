/* strlist HEADER */
/* lang=C20 */

/* read or audit a STRLIST database */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRLIST_INCLUDE
#define	STRLIST_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>
#include	<strlisthdr.h>


#define	STRLIST_MAGIC	0x88773421
#define	STRLIST		struct strlist_head
#define	STRLIST_INFO	struct strlist_informtion
#define	STRLIST_OBJ	struct strlist_object
#define	STRLIST_CUR	struct strlist_cursor
#define	STRLIST_FM	struct strlist_filemap
#define	STRLIST_MI	struct strlist_mapidx


struct strlist_informtion {
	time_t		wtime ;
	time_t		mtime ;
	uint		nstrlist ;
	uint		nskip ;
} ;

/* this is the shared-object description */
struct strlist_object {
	cchar		*name ;
	uint		objsize ;
	uint		cursize ;
} ;

struct strlist_cursor {
	uint		chash ;		/* "check" hash for key */
	int		i ;
} ;

struct strlist_filemap {
	char		*mdata ;	/* file map */
	time_t		ti_mod ;
	time_t		ti_map ;
	size_t		msize ;
} ;

struct strlist_mapidx {
	int		(*rt)[1] ;	/* mapped record table */
	int		(*it)[3] ;	/* mapped key-index table */
	char		*kst ;		/* mapped key-string table */
} ;

struct strlist_head {
	cchar 		*dbname ;
	strlisthdr	*fhp ;		/* file-header-pointer */
	STRLIST_FM	vf ;		/* file map */
	STRLIST_MI	mi ;		/* memory index */
	time_t		ti_lastcheck ;	/* time last check of file */
	uint		magic ;
	int		ncursors ;
} ;

typedef	STRLIST		strlist ;
typedef	STRLIST_INFO	strlist_info ;
typedef	STRLIST_OBJ	strlist_obj ;
typedef	STRLIST_CUR	strlist_cur ;
typedef	STRLIST_FM	strlist_fm ;
typedef	STRLIST_MI	strlist_mi ;

EXTERNC_begin

extern int	strlist_open(strlist *,cchar *) noex ;
extern int	strlist_count(strlist *) noex ;
extern int	strlist_curbegin(strlist *,strlist_cur *) noex ;
extern int	strlist_look(strlist *,strlist_cur *,cchar *,int) noex ;
extern int	strlist_enum(strlist *,strlist_cur *,char *,int) noex ;
extern int	strlist_curend(strlist *,strlist_cur *) noex ;
extern int	strlist_getinfo(strlist *,strlist_info *) noex ;
extern int	strlist_audit(strlist *) noex ;
extern int	strlist_close(strlist *) noex ;

EXTERNC_end


#endif /* STRLIST_INCLUDE */


