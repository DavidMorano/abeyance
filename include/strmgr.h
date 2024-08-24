/* strmgr HEADER */
/* lang=C20 */

/* string manager */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRMGR_INCLUDE
#define	STRMGR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	STRMGR		struct strmgr_head


struct strmgr_head {
	char		*dp ;
	int		dl ;
	int		dlen ;
} ;

typedef STRMGR		strmgr ;

EXTERNC_begin

extern int strmgr_start(strmgr *,char *,int) noex ;
extern int strmgr_avail(strmgr *) noex ;
extern int strmgr_rem(strmgr *) noex ;
extern int strmgr_str(strmgr *,cchar *,int) noex ;
extern int strmgr_chr(strmgr *,int) noex ;
extern int strmgr_finish(strmgr *) noex ;

EXTERNC_end


#endif /* STRMGR_INCLUDE */


