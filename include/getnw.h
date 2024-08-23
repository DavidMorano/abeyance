/* getnw HEADER */
/* lang=C20 */

/* get protocol entry */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETNW_INCLUDE
#define	GETNW_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int getnw_begin(int) noex ;
extern int getnw_ent(ucentnw *,char *,int) noex ;
extern int getnw_name(ucentnw *,char *,int,cchar *) noex ;
extern int getnw_addr(ucentnw *,char *,int,int,int) noex ;
extern int getnw_end() noex ;

EXTERNC_end


#endif /* GETNW_INCLUDE */


