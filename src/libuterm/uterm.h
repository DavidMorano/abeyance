/* uterm HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 */

/* object to handle UNIX terminal stuff */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UTERM_INCLUDE
#define	UTERM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<termios.h>
#include	<limits.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<charq.h>


#define	UTERM		struct uterm_head
#define	UTERM_FL	struct uterm_flags
#define	UTERM_LD	struct uterm_loader
#define	UTERM_PR	struct uterm_prompter


enum utermcmds {
	utermcmd_noop,
	utermcmd_getuid,
	utermcmd_getsid,
	utermcmd_getmode,
	utermcmd_setmode,
	utermcmd_setrterms,
	utermcmd_reestablish,
	utermcmd_getmesg,
	utermcmd_setmesg,
	utermcmd_getbiff,
	utermcmd_setbiff,
	utermcmd_getlines,
	utermcmd_setlines,
	utermcmd_getpgrp,
	utermcmd_setpgrp,
	utermcmd_getpop,
	utermcmd_setpop,
	utermcmd_overlast
} ;

struct uterm_flags {
	uint		cntl_o:1 ;	/* control-O */
	uint		cntl_c:1 ;	/* control-C */
	uint		cntl_y:1 ;	/* control-Y */
	uint		cntl_z:1 ;	/* control-Z */
	uint		dle:1 ;		/* data-link-escape */
	uint		rw:1 ;		/* ?? */
	uint		suspend:1 ;	/* output suspended */
	uint		read:1 ;	/* read in progress */
	uint		nosig:1 ;	/* no-signal-generation mode */
	uint		nosigecho:1 ;	/* no echo for signals */
	uint		noctty:1 ;	/* the terminal is not controlling */
	uint		noflow:1 ;	/* no output flow control */
} ;

/* prompt-output before input */
struct uterm_prompter {
	cchar		*pbuf ;
	int		plen ;
} ;

/* pre-loading the input buffer */
struct uterm_loader {
	cchar		*lbuf ;
	int		llen ;
} ;

struct uterm_head {
	TERMIOS		ts_old ;
	TERMIOS		ts_new ;
	charq		taq ;
	charq		ecq ;
	time_t		ti_start ;
	uid_t		uid ;
	UTERM_FL	f ;
	uint		magic ;
	int		fd ;
	int		loopcount ;
	int		timeout ;	/* timeout timer counter */
	int		mode ;
	int		ch_read, ch_write ;
	int		status ;
	char		rterms[32] ;
} ;

typedef UTERM		uterm ;
typedef	UTERM_LD	uterm_ld ;
typedef	UTERM_PR	uterm_pr ;

EXTERNC_begin

extern int uterm_start(uterm *,int) noex ;
extern int uterm_control(uterm *,int,...) noex ;
extern int uterm_status(uterm *,int,...) noex ;
extern int uterm_read(uterm *,char *,int) noex ;
extern int uterm_reade(uterm *,char *,int,int,int,uterm_pr *,uterm_ld *) noex ;
extern int uterm_write(uterm *,cchar *,int) noex ;
extern int uterm_suspend(uterm *) noex ;
extern int uterm_resume(uterm *) noex ;
extern int uterm_restore(uterm *) noex ;
extern int uterm_ensure(uterm *) noex ;
extern int uterm_getmesg(uterm *) noex ;
extern int uterm_getbiff(uterm *) noex ;
extern int uterm_getpop(uterm *) noex ;
extern int uterm_setpop(uterm *,int) noex ;
extern int uterm_finish(uterm *) noex ;

EXTERNC_end


#endif /* UTERM_INCLUDE */


