/* conslog HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* send log messages to the system logger device */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CONSLOG_INCLUDE
#define	CONSLOG_INCLUDE

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* POSIX */
#include	<sys/syslog.h>		/* POSIX */
#include	<stdarg.h>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */


#define	CONSLOG			struct conslog_head
#define	CONSLOG_MAGIC		0x13f3c201
#define	CONSLOG_LINELEN		80


struct conslog_head {
	time_t		ti_open ;
	time_t		ti_write ;
	uint		magval ;
	int		logfac ;
	int		lfd ;
	int		c ;
} ;

typedef CONSLOG		conslog ;

EXTERNC_begin

extern int conslog_open(conslog *,int) noex ;
extern int conslog_write(conslog *,int,cchar *,int) noex ;
extern int conslog_printf(conslog *,int,cchar *,...) noex ;
extern int conslog_vprintf(conslog *,int,cchar *,va_list) noex ;
extern int conslog_check(conslog *,time_t) noex ;
extern int conslog_count(conslog *) noex ;
extern int conslog_close(conslog *) noex ;

EXTERNC_end


#endif /* conslog_INCLUDE */


