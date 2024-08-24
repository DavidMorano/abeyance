/* zos HEADER */
/* lang=C20 */

/* time-zone offset string management */
/* lang=C20 */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ZOS_INCLUDE
#define	ZOS_INCLUDE


#include	<envstandards.h>	/* first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


EXTERNC_begin

extern int zos_set(char *,int,int) noex ;
extern int zos_get(cchar *,int,int *) noex ;

EXTERNC_end


#endif /* XOS_INCLUDE */


