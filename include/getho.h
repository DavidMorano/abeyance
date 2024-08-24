/* getho HEADER */
/* lang=C20 */

/* get protocol entry */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETHO_INCLUDE
#define	GETHO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int getho_begin(int) noex ;
extern int getho_ent(ucentho *,char *,int) noex ;
extern int getho_name(ucentho *,char *,int,cchar *) noex ;
extern int getho_addr(ucentho *,char *,int,int,cvoid *,int) noex ;
extern int getho_end() noex ;

EXTERNC_end


#endif /* GETHO_INCLUDE */


