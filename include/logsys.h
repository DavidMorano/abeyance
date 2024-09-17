/* logsys HEADER */
/* lang=C20 */

/* send log messages to the system logger device */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LOGSYS_INCLUDE
#define	LOGSYS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stdarg.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<localmisc.h>		/* |COLUMNS| + |LOGIDLEN| */


#define	LOGSYS_MAGIC		0x13f3c201
#define	LOGSYS			struct logsys_head
#define	LOGSYS_LOGIDLEN		LOGIDLEN	/* <- from 'localmisc' */
#define	LOGSYS_LINELEN		COLUMNS		/* <- from 'localmisc' */
#define	LOGSYS_USERLEN		(LOGSYS_LINELEN - (LOGSYS_LOGIDLEN + 1))


struct logsys_head {
	cchar		*logtag ;
	time_t		ti_open ;
	time_t		ti_write ;
	uint		magic ;
	int		logfac ;
	int		opts ;
	int		lfd ;
	int		logidlen ;
	int		n, c ;
	char		logid[LOGSYS_LOGIDLEN + 1] ;
} ;

typedef LOGSYS		logsys ;

EXTERNC_begin

extern int logsys_open(logsys *,int,cchar *,cchar *,int) noex ;
extern int logsys_setid(logsys *,cchar *) noex ;
extern int logsys_write(logsys *,int,cchar *,int) noex ;
extern int logsys_printf(logsys *,int,cchar *,...) noex ;
extern int logsys_vprintf(logsys *,int,cchar *,va_list) noex ;
extern int logsys_check(logsys *,time_t) noex ;
extern int logsys_flush(logsys *) noex ;
extern int logsys_close(logsys *) noex ;

EXTERNC_end


#endif /* LOGSYS_INCLUDE */


