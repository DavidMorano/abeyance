/* utmpent HEADER */
/* lang=C20 */

/* get UTMP entry */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UTMPENT_INCLUDE
#define	UTMPENT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |pid_t| */
#include	<time.h>
#include	<usystem.h>
#include	<utmpacc.h>		/* <- the money shot! */


#define	UTMPENT		struct utmpent_head

/* UTMP entry types */
#ifndef	UTMPENT_TEMPTY
#define	UTMPENT_TEMPTY		UTMPACC_TEMPTY
#define	UTMPENT_TRUNLEVEL	UTMPACC_TRUNLEVEL
#define	UTMPENT_TBOOTTIME	UTMPACC_TBOOTTIME
#define	UTMPENT_TOLDTIME	UTMPACC_TOLDTIME
#define	UTMPENT_TNEWTIME	UTMPACC_TNEWTIME
#define	UTMPENT_TPROCINIT	UTMPACC_TPROCINIT
#define	UTMPENT_TPROCLOGIN	UTMPACC_TPROCLOGIN
#define	UTMPENT_TPROCUSER	UTMPACC_TPROCUSER
#define	UTMPENT_TPROCDEAD	UTMPACC_TPROCDEAD
#define	UTMPENT_TACCOUNT	UTMPACC_TACCOUNT
#define	UTMPENT_TSIGNATURE	UTMPACC_TSIGNATURE
#endif /* UTMPENT_TEMPTY */

/* UTMP field sizes */
#ifndef	UTMPENT_LID
#define	UTMPENT_LID		4
#define	UTMPENT_LUSER		32
#define	UTMPENT_LLINE		32
#define	UTMPENT_LHOST		256
#endif


struct utmpent_head {
	time_t		date ;
	pid_t		sid ;
	int		session ;
	char		id[UTMPENT_LID + 1] ;
	char		user[UTMPENT_LUSER + 1] ;
	char		line[UTMPENT_LLINE + 1] ;
	char		host[UTMPENT_LHOST + 1] ;
} ;

typedef	UTMPENT		utmpent ;

EXTERNC_begin

extern int getutmpent(utmpent *,pid_t) noex ;

extern int getutmpid(char *,int,pid_t) noex ;
extern int getutmpname(char *,int,pid_t) noex ;
extern int getutmpline(char *,int,pid_t) noex ;
extern int getutmphost(char *,int,pid_t) noex ;

EXTERNC_end


#endif /* UTMPENT_INCLUDE */


