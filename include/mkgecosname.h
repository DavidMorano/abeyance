/* mkgecosname HEADER */
/* lang=C20 */

/* make (or get) a GECOS name out of the raw PASSWD c-string */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MKGECOSNAME_INCLUDE
#define	MKGECOSNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int mkgecosname(char *,int,cchar *) noex ;
extern int getgecosname(cchar *,int,cchar **) noex ;

EXTERNC_end


#endif /* MKGECOSNAME_INCLUDE */


