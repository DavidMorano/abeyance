/* tmtime HEADER */
/* lang=C20 */

/* this is supposed to provide OS-independent time management operations */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TMTIME_INCLUDE
#define	TMTIME_INCLUDE


#include	<envstandards.h>	/* first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>		/* <- |TZABBRLEN| */


#define	TMTIME			struct tmtime_head
#define	TMTIME_ZNAMELEN		TZABBRLEN
#define	TMTIME_BASEYEAR		1900


struct tmtime_head {
	int	sec ;		/* 0-61 (for up to two leap-seconds) */
	int	min ;		/* 0-59 */
	int	hour ;		/* 0-23 */
	int	mday ;		/* month-day (day-of-month 1-31) */
	int	mon ;		/* month 0-11 */
	int	year ;		/* number of years since 1900 */
	int	wday ;		/* week-day (day-of-week 0-6) */
	int	yday ;		/* year-day (day-of-year) */
	int	isdst ;
	int	gmtoff ;	/* offset from GMT (seconds west of GMT) */
	char	zname[TMTIME_ZNAMELEN + 1] ;	/* TZ name abbreviation */
} ;

typedef TMTIME		tmtime ;

EXTERNC_begin

extern int	tmtime_insert(tmtime *,TM *) noex ;
extern int	tmtime_ztime(tmtime *,bool,time_t) noex ;
extern int	tmtime_gmtime(tmtime *,time_t) noex ;
extern int	tmtime_localtime(tmtime *,time_t) noex ;
extern int	tmtime_extract(tmtime *,TM *) noex ;
extern int	tmtime_mktime(tmtime *,time_t *) noex ;
extern int	tmtime_adjtime(tmtime *,time_t *) noex ;

#ifdef	COMMENT
extern int	tmtime_setznoe(tmtime *,cchar *,int) noex ;
extern int	mktime_settimez(tmtime *,cchar *,cchar *,time_t) noex ;
extern int	mktime_gettime(tmtime *,cchar *,time_t *) noex ;
#endif /* COMMENT */

EXTERNC_end


#endif /* TMTIME_INCLUDE */


