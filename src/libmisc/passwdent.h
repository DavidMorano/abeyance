/* passwdent HEADER */
/* lang=C20 */

/* PASSWD structure management */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PASSWDENT_INCLUDE
#define	PASSWDENT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


EXTERNC_begin

extern int passwdent_load(PASSWD *,char *,int,CPASSWD *) noex ;
extern int passwdent_parse(PASSWD *,char *,int,cchar *,int) noex ;
extern int passwdent_size(CPASSWD *) noex ;
extern int passwdent_format(CPASSWD *,char *,int) noex ;

EXTERNC_end


#endif /* PASSWDENT_INCLUDE */


