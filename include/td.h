/* td HEADER */
/* lang=C++20 */

/* Terminal-Display manager */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-08-01, Dave morano
	File was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TD_INCLUDE
#define	TD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stdarg.h>		/* |va_list| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<vecitem.h>
#include	<termstr.h>


#define	TD		struct td_head
#define	TD_POS		struct td_position
#define	TD_WIN		struct td_window
#define	TD_FL		struct td_flags

/* control codes */
#define	TD_CEOL		0		/* set "erase to EOL" mode */
#define	TD_CLINES	1		/* change number of lines in window */
#define	TD_CSCROLL	2		/* scroll the window up or down */
#define	TD_CSUBWIN	3		/* create a subwindow */
#define	TD_CCURSOR	4		/* position the cursor */

/* graphic renditions */
#define	TD_GRBOLD	(1<<0)		/* graphic-rendition bold */
#define	TD_GRUNDER	(1<<1)		/* graphic-rendition underline */
#define	TD_GRBLINK	(1<<2)		/* graphic-rendition blinking */
#define	TD_GRREV	(1<<3)		/* graphic-rendition reverse-video */


struct td_flags {
	uint		statusdisplay:1 ;
	uint		meol:1 ;	/* erase-to-EOL mode */
	uint		linebuf:1 ;	/* line buffer mode */
	uint		smallscroll:1 ;
	uint		nlcr:1 ;	/* NL-character display behavior */
} ;

struct td_position {
	uint		timecount ;
	int		row ;
	int		col ;
} ;

struct td_window {
	TD_POS		move ;		/* move is outstanding */
	TD_POS		cur ;		/* current position */
	int		srow ;		/* starting absolute row */
	int		scol ;		/* starting absolute col */
	int		rows ;		/* rows */
	int		cols ;		/* cols */
} ;

struct td_head {
	cchar		*termname ;	/* given terminal type-name */
	char		*buf ;		/* storage buffer */
	termstr		*tsp ;		/* term-string-pointer */
	vecitem		*wlp ;		/* window-list-pointer */
	TD_POS		cur ;		/* current position */
	TD_FL		f ;
	uint		timecounter ;
	uint		magic ;
	int		tfd ;
	int		termcap ;	/* terminal capabilities */
	int		buflen ;	/* buffer extent */
	int		curlen ;	/* current buffer occupancy */
	int		rows ;
	int		cols ;
} ;

typedef TD		td ;
typedef TD_FL		td_fl ;
typedef TD_POS		td_pos ;
typedef TD_WIN		td_win ;

EXTERNC_begin

extern int td_start(td *,int,cchar *,int,int) noex ;
extern int td_finish(td *) noex ;
extern int td_flush(td *) noex ;
extern int td_subnew(td *,int,int,int,int) noex ;
extern int td_subdel(td *,int) noex ;
extern int td_getlines(td *,int) noex ;
extern int td_setlines(td *,int,int) noex ;
extern int td_move(td *,int,int,int) noex ;
extern int td_scroll(td *,int,int) noex ;
extern int td_control(td *,int,...) noex ;
extern int td_setsize(td *,int,int) noex ;
extern int td_suspend(td *,int,int) noex ;
extern int td_write(td *,int,cchar *,int) noex ;
extern int td_pwrite(td *,int,int,int,cchar *,int) noex ;
extern int td_pwritegr(td *,int,int,int,int,cchar *,int) noex ;
extern int td_vprintf(td *,int,cchar *,va_list) noex ;
extern int td_vpprintf(td *,int,int,int,cchar *,va_list) noex ;
extern int td_printf(td *,int,cchar *,...) noex ;
extern int td_pprintf(td *,int,int,int,cchar *,...) noex ;
extern int td_clear(td *,int) noex ;
extern int td_ew(td *,int,int,int) noex ;
extern int td_el(td *,int,int) noex ;
extern int td_ec(td *,int,int) noex ;
extern int td_check(td *) noex ;
extern int td_position(td *,int,td_pos *) noex ;

EXTERNC_end


#endif /* TD_INCLUDE */


