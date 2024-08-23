/* holidays */
/* lang=C20 */

/* access for the HOLIDAYS database */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-10-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	HOLIDAYS_INCLUDE
#define	HOLIDAYS_INCLUDE


#include	<envstandards.h>
#include	<sys/types.h>
#include	<usystem.h>
#include	<localmisc.h>


#define	HOLIDAYS_MAGIC	0x63328183
#define	HOLIDAYS	struct holidays_head
#define	HOLIDAYS_OBJ	struct holidays_object
#define	HOLIDAYS_CITE	struct holidays_query
#define	HOLIDAYS_CUR	struct holidays_cursor


struct holidays_object {
	cchar		*name ;
	uint		objsize ;
	uint		cursize ;
} ;

struct holidays_query {
	ushort		y ;
	uchar		m, d ;
} ;

struct holidays_cursor {
	uint		chash ;
	int		i ;
} ;

struct holidays_head {
	cchar		*pr ;
	cchar		*fname ;
	uint		(*rt)[3] ;	/* the records (sorted by m-d) */
	int		(*kit)[3] ;	/* key-index-table */
	char		*kst ;		/* key string-table */
	char		*vst ;		/* val string-table */
	time_t		ti_check ;
	time_t		ti_mtime ;
	uint		magic ;
	int		year ;
	int		kslen ;
	int		vslen ;
	int		rtlen ;
	int		itlen ;
	int		ncursors ;
} ;

typedef	HOLIDAYS	holidays ;
typedef	HOLIDAYS_OBJ	holidays_obj ;
typedef	HOLIDAYS_CITE	holidays_cite ;
typedef	HOLIDAYS_CUR	holidays_cur ;

EXTERNC_begin

extern int holidays_open(holidays *,cchar *,int,cchar *) ;
extern int holidays_count(holidays *) ;
extern int holidays_curbegin(holidays *,holidays_cur *) ;
extern int holidays_curend(holidays *,holidays_cur *) ;
extern int holidays_fetchcite(holidays *,holidays_cite *,holidays_cur *,
		char *,int) ;
extern int holidays_fetchname(holidays *,cchar *,int,holidays_cur *,
		holidays_cite *,char *,int) ;
extern int holidays_enum(holidays *,holidays_cur *,
		holidays_cite *,char *,int) ;
extern int holidays_check(holidays *,time_t) ;
extern int holidays_audit(holidays *) ;
extern int holidays_close(holidays *) ;

#ifdef	COMMENT
extern int holidays_lookday(holidays *,holidays_cur *,holidays_cite *) ;
extern int holidays_lookname(holidays *,holidays_cur *,cchar *,int) ;
extern int holidays_read(holidays *,holidays_cur *,
			holidays_cite *,char *,int) ;
#endif

EXTERNC_end


#endif /* HOLIDAYS_INCLUDE */


