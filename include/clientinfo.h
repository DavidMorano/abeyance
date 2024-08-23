/* clientinfo HEADER */
/* lang=C++20 */

/* manage client information (a little bit) */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	CLIENTINFO_INCLUDE
#define	CLIENTINFO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |pid_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<sockaddress.h>
#include	<vecstr.h>


#define	CLIENTINFO	struct clientinfo_head


struct clientinfo_head {
	sockaddress	*sap ;			/* peername socket address */
	vecstr		*nlp ;
	vecstr		*slp ;
	cchar		*peername ;
	cchar		*netuser ;
	cchar		*netpass ;
	cchar		*netident ;
	cchar		*service ;		/* service */
	cchar		*subservice ;		/* subservice */
	long		mtype ;			/* SYSV-IPC message type */
	time_t		stime ;			/* start time */
	pid_t		pid ;
	int		salen ;			/* socket length */
	int		nnames ;		/* number of names */
	int		fd_input ;
	int		fd_output ;
	int		f_long ;		/* the "long" switch */
	int		f_local ;		/* client is local */
} ;

typedef	CLIENTINFO	clientinfo ;

EXTERNC_begin

extern int clientinfo_start(clientinfo *) noex ;
extern int clientinfo_finish(clientinfo *) noex ;
extern int clientinfo_loadnames(clientinfo *,cchar *) noex ;

EXTERNC_end


#endif /* CLIENTINFO_INCLUDE */


