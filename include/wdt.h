/* wdt HEADER */
/* lang=C20 */

/* wælk-directory-tree */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	WDT_INCLUDE
#define	WDT_INCLUDE


/* mode values for call */
#define	WDT_MFOLLOW	1

/* return values */
#define	WDT_ROK		0
#define	WDT_RBADTMP	SR_ACCESS
#define	WDT_RBADTMPOPEN	SR_NOENT
#define	WDT_RBADWRITE	SR_DQUOT


EXTERNC_begin

extern int wdt(cchar *,int,int (*)(),void *) noex ;

EXTERNC_end


#endif /* WDT_INCLUDE */


