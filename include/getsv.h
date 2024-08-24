/* getsv HEADER */
/* lang=C20 */

/* get service entry */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETSV_INCLUDE
#define	GETSV_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int getsv_begin(int) noex ;
extern int getsv_ent(ucentsv *,char *,int) noex ;
extern int getsv_name(ucentsv *,char *,int,cchar *,cchar *) noex ;
extern int getsv_port(ucentsv *,char *,int,int,cchar *) noex ;
extern int getsv_end() noex ;

EXTERNC_end


#endif /* GETSV_INCLUDE */


