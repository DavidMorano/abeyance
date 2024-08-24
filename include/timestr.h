/* timestr HEADER */
/* lang=C20 */

/* convert a UNIX® time value into a c-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TIMESTR_INCLUDE
#define	TIMESTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<time.h>		/* |time_t| */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<nistinfo.h>


enum timestrstypes {
	timestrtype_std,	/* standard (and MSG envelope) */
	timestrtype_gmstd,	/* standard for GMT */
	timestrtype_msg,	/* RFC-822 message */
	timestrtype_log,	/* "log" format */
	timestrtype_gmlog,	/* "log" format for GMT */
	timestrtype_logz,	/* "logz" format */
	timestrtype_gmlogz,	/* "logz" format for GMT */
	timestrtype_overlast
} ;


EXTERNC_begin

extern char *timestr_log(time_t,char *) noex ;
extern char *timestr_msg(time_t,char *) noex ;
extern char *timestr_std(time_t,char *) noex ;
extern char *timestr_logz(time_t,char *) noex ;
extern char *timestr_edate(time_t,char *) noex ;
extern char *timestr_gmlog(time_t,char *) noex ;
extern char *timestr_hdate(time_t,char *) noex ;
extern char *timestr_gmlogz(time_t,char *) noex ;
extern char *timestr_gmtstd(time_t,char *) noex ;
extern char *timestr_date(time_t,int,char *) noex ;
extern char *timestr_scandate(time_t,char *) noex ;
extern char *timestr_elapsed(time_t,char *) noex ;
extern char *timestr_nist(time_t,nistinfo *,char *) noex ;

EXTERNC_end


#endif /* TIMESTR_INCLUDE */


