/* mailmsgenv HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* manage an UNIX® message envelope */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSGENV_INCLUDE
#define	MAILMSGENV_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<time.h>		/* |time_t| */
#include	<clanguage.h>
#include	<usysbase.h>


#define	MAILMSGENV		struct mailmsgenv_head
#define	MAILMSGENV_FL		struct mailmsgenv_flags
#define	MAILMSGENV_MAXLINELEN	1092


struct mailmsgenv_flags {
	uint		start:1 ;	/* was it a starting envelope? */
	uint		init_time:1 ;	/* did we parse its time yet? */
	uint		hastime:1 ;	/* did it have a time specification */
	uint		haszone:1 ;	/* did it have a time zone? */
} ; /* end struct */

struct mailmsgenv_head {
	cchar		*address ;
	cchar		*origdate ;
	cchar		*remote ;
	cchar		*tzname ;
	time_t		daytime ;
	MAILMSGENV_FL	fl ;
	int		alen ;
} ; /* end struct */

typedef MAILMSGENV	mailmsgenv ;

EXTERNC_begin

extern int mailmsgenv_start(mailmsgenv *,cchar *,int) noex ;
extern int mailmsgenv_isstart(mailmsgenv *) noex ;
extern int mailmsgenv_getaddress(mailmsgenv *,cchar **) noex ;
extern int mailmsgenv_getremote(mailmsgenv *,cchar **) noex ;
extern int mailmsgenv_gettzname(mailmsgenv *,cchar **) noex ;
extern int mailmsgenv_gettime(mailmsgenv *,time_t *) noex ;
extern int mailmsgenv_mkdatestr(mailmsgenv *,char *,char *,int) noex ;
extern int mailmsgenv_mkenv(mailmsgenv *,char *,int) noex ;
extern int mailmsgenv_finish(mailmsgenv *) noex ;

EXTERNC_end


#endif /* MAILMSGENV_INCLUDE */


