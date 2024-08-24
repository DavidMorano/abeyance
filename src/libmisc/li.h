/* li HEADER */
/* lang=C20 */

/* long (64 bit) interger arithmetic object module */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LI_INCLUDE
#define	LI_INCLUDE


/* object defines */
#define	LI	struct longint_head


struct longint_head {
	long		u, l ;
} ;

typedef LONGINT		longint ;

EXTERNC_begin

extern int li_load(LI *,int,int) noex ;
extern int li_store(LI *,int *,int *) noex ;
extern int li_zero(LI *) noex ;
extern int li_add2(LI *,LI *) noex ;
extern int li_add3(LI *,LI *,LI *) noex ;

EXTERNC_end


#endif /* LI_INCLUDE */


