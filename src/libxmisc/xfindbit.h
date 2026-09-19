/* xfindbit */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	XFINDBIT_INCLUDE
#define	XFINDBIT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


EXTERNC_begin

extern int xffbsi	(uint)	noex ;
extern int xffbci	(uint)	noex ;
extern int xffbsl	(ulong)	noex ;
extern int xffbcl	(ulong)	noex ;
extern int xflbsi	(uint)	noex ;
extern int xflbci	(uint)	noex ;
extern int xflbsl	(ulong)	noex ;
extern int xflbcl	(ulong)	noex ;
extern int xfbscounti	(uint)	noex ;
extern int xfbscountl	(ulong)	noex ;

EXTERNC_end


#endif /* XFINDBIT_INCLUDE */


