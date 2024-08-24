/* removename HEADER */
/* lang=C20 */

/* remove a named file-system object (and its descendants) */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	REMOVENAME_INCLUDE
#define	REMOVENAME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<randomvar.h>


/* object defines (options) */
#define	REMOVENAME_MDEFAULT	0
#define	REMOVENAME_MBURN	1
#define	REMOVENAME_MFOLLOW	2


EXTERNC_begin

extern int	removename(randomvar *,int,int,cchar *) noex ;

EXTERNC_end


#endif /* REMOVENAME_INCLUDE */


