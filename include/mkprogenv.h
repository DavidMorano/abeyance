/* mkprogenv HEADER */
/* lang=C20 */

/* make new environment for a program */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKPROGENV_INCLUDE
#define	MKPROGENV_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<vechand.h>
#include	<strpack.h>


#define	MKPROGENV	struct mkprogenv_head


struct mkprogenv_head {
	cchar		*un ;		/* user-name */
	cchar		*uh ;		/* user-home */
	mainv		envv ;
	vechand		env ;
	strpack		stores ;
} ;

typedef MKPROGENV	mkprogenv ;

EXTERNC_begin

extern int mkprogenv_start(mkprogenv *,mainv) noex ;
extern int mkprogenv_envset(mkprogenv *,cchar *,cchar *,int) noex ;
extern int mkprogenv_getvec(mkprogenv *,mainv *) noex ;
extern int mkprogenv_finish(mkprogenv *) noex ;

EXTERNC_end


#endif /* MKPROGENV_INCLUDE */


