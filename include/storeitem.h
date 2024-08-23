/* storeitem HEADER */
/* lang=C20 */

/* storage object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-17, David A­D­ Morano
	This object was originally written for use in some old
	Personal Communication Services (PCS) code (from some time
	ago, 1993?).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STOREITEM_INCLUDE
#define	STOREITEM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	STOREITEM	struct storeitem_head


struct storeitem_head {
	char		*dbuf ;
	int		dlen ;
	int		index ;
	int		f_overflow ;
} ;

typedef STOREITEM	storeitem ;

EXTERNC_begin

extern int storeitem_start(storeitem *,char *,int) noex ;
extern int storeitem_strw(storeitem *,cchar *,int,cchar **) noex ;
extern int storeitem_buf(storeitem *,cvoid *,int,cchar **) noex ;
extern int storeitem_dec(storeitem *,int,cchar **) noex ;
extern int storeitem_chr(storeitem *,int,cchar **) noex ;
extern int storeitem_nul(storeitem *,cchar **) noex ;
extern int storeitem_ptab(storeitem *,int,void ***) noex ;
extern int storeitem_block(storeitem *,int,int,void **) noex ;
extern int storeitem_getlen(storeitem *) noex ;
extern int storeitem_finish(storeitem *) noex ;

static inline int storeitem_char(storeitem *op,int ch,cchar **rpp) noex {
	return storeitem_chr(op,ch,rpp) ;
}

EXTERNC_end


#endif /* STOREITEM_INCLUDE */


