/* utmpacc HEADER */
/* lang=C20 */

/* UTMPACC management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This module serves as a per-process cache for UNIX® UTMP
	information.

	Since we are basically dealing with global data, we need
	to make the establishment of it multi-thread safe.  We also
	want fork safety.  Yes, we want everything, including cleanup
	on module unloading (since, yes, we could all be inside a
	loadable and unloadble module!).  For these purposes we
	employ the basic (and not so basic) means of accomplishing
	this.  See the code for our various machinations.

*******************************************************************************/

#ifndef	UTMPACC_INCLUDE
#define	UTMPACC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<utmpx.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>
#include	<utmpaccent.h>		/* <- the money shot */


#define	UTMPACC_ENT		UTMPACCENT
#define	UTMPACC_SB		struct utmpacc_statistics
#define	UTMPACC_CUR		struct utmpacc_cursor
#define	UTMPACC_BUFLEN		332	/* large enough for all fields */
#define	UTMPACC_MAX		20
#define	UTMPACC_TTL		(20*60)
#define	UTMPACC_CURMAGIC	0x97635148

#if	(defined(OSNAME_SunOS) && (OSNAME_SunOS > 0))
#define	UTMPACC_DEFUTMP	"/var/adm/utmpx"
#elif	(defined(OSNAME_Darwin) && (OSNAME_Darwin > 0))
#define	UTMPACC_DEFUTMP	"/var/run/utmpx"
#else
#define	UTMPACC_DEFUTMP	"/var/run/utmpx"
#endif

#ifndef	UTMPACC_TEMPTY
#define	UTMPACC_TEMPTY		UTMPACCENT_TEMPTY
#define	UTMPACC_TRUNLEVEL	UTMPACCENT_TRUNLEVEL
#define	UTMPACC_TBOOTTIME	UTMPACCENT_TBOOTTIME
#define	UTMPACC_TOLDTIME	UTMPACCENT_TOLDTIME
#define	UTMPACC_TNEWTIME	UTMPACCENT_TNEWTIME
#define	UTMPACC_TPROCINIT	UTMPACCENT_TPROCINIT
#define	UTMPACC_TPROCLOGIN	UTMPACCENT_TPROCLOGIN
#define	UTMPACC_TPROCUSER	UTMPACCENT_TPROCUSER
#define	UTMPACC_TPROCDEAD	UTMPACCENT_TPROCDEAD
#define	UTMPACC_TACCOUNT	UTMPACCENT_TACCOUNT
#define	UTMPACC_TSIGNATURE	UTMPACCENT_TSIGNATURE
#endif /* UTMPACC_TEMPTY */

#ifndef	UTMPACC_LID
#define	UTMPACC_LID		4
#define	UTMPACC_LUSER		32
#define	UTMPACC_LLINE		32
#define	UTMPACC_LHOST		256
#endif


enum utxproctypes {
	utxproctype_user,
	utxproctype_login,
	utxproctype_init,
	utxproctype_dead,
	utxproctype_overlast
} ;

struct utmpacc_statistics {
	uint		maxusers ;
	uint		maxents ;
} ;

struct utmpacc_cursor {
	void		*icursor ;
} ;

typedef	UTMPACC_SB	utmpacc_sb ;
typedef	UTMPACC_CUR	utmpacc_cur ;
typedef	UTMPACC_ENT	utmpacc_ent ;

EXTERNC_begin

extern int utmpacc_init() noex ;
extern int utmpacc_boottime(time_t *) noex ;
extern int utmpacc_runlevel() noex ;
extern int utmpacc_users(int) noex ;
extern int utmpacc_entsid(utmpacc_ent *,char *,int,pid_t) noex ;
extern int utmpacc_entstat(utmpacc_ent *,char *,int,pid_t) noex ;
extern int utmpacc_entline(utmpacc_ent *,char *,int,cchar *,int) noex ;
extern int utmpacc_stats(utmpacc_sb *) noex ;
extern int utmpacc_extract(int) noex ;
extern int utmpacc_fini() noex ;

extern int utmpacc_curbegin(utmpacc_cur *) noex ;
extern int utmpacc_curenum(utmpacc_cur *,utmpacc_ent *,char *,int) noex ;
extern int utmpacc_curend(utmpacc_cur *) noex ;

EXTERNC_end


#endif /* UTMPACC_INCLUDE */


