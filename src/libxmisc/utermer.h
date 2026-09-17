/* utermer HEADER */
/* lang=C++20 */

/* object to handle UNIX terminal stuff */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UTERMER_INCLUDE
#define	UTERMER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<termios.h>
#include	<limits.h>
#include	<pthead.h>
#include	<time.h>
#include	<charq.h>
#include	<ptm.h>
#include	<psem.h>
#include	<piq.h>
#include	<ciq.h>


#define	UTERMER_MAGIC	0x33442281
#define	UTERMER		struct utermer_head
#define	UTERMER_FL	struct utermer_flags
#define	UTERMER_PR	struct utermer_prompt
#define	UTERMER_LD	struct utermer_load
#define	UTERMER_CS	struct utermer_codespace
#define	UTERMER_BD	struct utermer_bdesc


struct utermer_bdesc {
	char		*dbuf ;
	int		dlen ;
} ;

struct utermer_codespace {
	PSEM		*sem ;
	int		len ;
	int		cs ;
} ;

struct utermer_flags {
	uint		co:1 ;		/* control O */
	uint		cc:1 ;		/* control C */
	uint		rw:1 ;
	uint		suspend:1 ;	/* output suspended */
	uint		read:1 ;	/* read in progress */
	uint		onint:1 ;	/* on an interrupt */
} ;

struct utermer_head {
	TERMIOS		ts_old ;
	TERMIOS		ts_new ;
	PTM		mout ;
	CHARIQ		taq ;		/* type-ahead */
	CHARIQ		ecq ;		/* echo */
	PIQ		fstore ;	/* free-packet store */
	CIQ		rq ;		/* reader queue */
	CIQ		wq ;		/* writer queue */
	PSEM		rq_sem ;
	PSEM		wq_sem ;
	pthread_t	tid_read, tid_write, tid_int ;
	time_t		basetime ;
	UTERMER_FL	f ;
	uint		magic ;
	int		fd ;
	int		loopcount ;
	int		timeout ;	/* timeout timer counter */
	int		mode ;
	int		ch_read, ch_write ;
	int		stat ;
} ;

typedef	UTERMER		utermer ;
typedef	UTERMER_FL	utermer_fl ;
typedef	UTERMER_PR	utermer_pr ;
typedef	UTERMER_LD	utermer_ld ;
typedef	UTERMER_CS	utermer_cs ;

EXTERNC_begin

extern int utermer_start(utermer *,int) noex ;
extern int utermer_control(utermer *,int,...) noex ;
extern int utermer_status(utermer *,int,...) noex ;
extern int utermer_read(utermer *,char *,int) noex ;
extern int utermer_reade(utermer *,char *,int,int,int,
		ustermer_pr *,utermer_ld *) noex ;
extern int utermer_reader(utermer *,utermer_cs *,char *,int,int,int,
		utermer_bd *,utermer_bd *) noex ;
extern int utermer_write(utermer *,cchar *,int) noex ;
extern int utermer_suspend(utermer *) noex ;
extern int utermer_resume(utermer *) noex ;
extern int utermer_restore(utermer *) noex ;
extern int utermer_ensure(utermer *) noex ;
extern int utermer_finish(utermer *) noex ;

EXTERNC_end


#endif /* UTERMER_INCLUDE */


