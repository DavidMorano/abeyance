/* date HEADER */
/* lang=C20 */

/* date storage object */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DATE_INCLUDE
#define	DATE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<time.h>		/* |time_t| */
#include	<usystem.h>
#include	<localmisc.h>		/* |TZABBRLEN| */


#define	DATE		struct date_head
#define	DATE_ZNAMELEN	TZABBRLEN		/* maximum TZ name length */


struct date_head {
	time_t		time ;			/* UNIX® time */
	short		zoff ;			/* minutes west of GMT */
	short		isdst ;			/* is-daylight-savings time */
	char		zname[DATE_ZNAMELEN+1] ; /* time-zone abbreviation */
} ;

typedef DATE		date ;

EXTERNC_begin

extern int date_start(date *,time_t,int,int,cchar *,int) noex ;
extern int date_copy(date *,date *) noex ;
extern int date_gettime(date *,time_t *) noex ;
extern int date_getzoff(date *,int *) noex ;
extern int date_getisdst(date *,int *) noex ;
extern int date_getzname(date *,char *,int) noex ;
extern int date_finish(date *) noex ;

EXTERNC_end


#endif /* DATE_INCLUDE */


