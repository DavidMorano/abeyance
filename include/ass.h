/* ass HEADER */
/* lang=C20 */

/* allocated string */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ASS_INCLUDE
#define	ASS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>


#define	ASS		struct ass_head


struct ass_head {
	char		*s ;
	int		len ;
	int		e ;
} ;

typedef	ASS		ass ;

EXTERNC_begin

extern int ass_start(ass *) noex ;
extern int ass_add(ass *,int) noex ;
extern int ass_finish(ass *) noex ;

EXTERNC_end


#endif /* ASS_INCLUDE */


