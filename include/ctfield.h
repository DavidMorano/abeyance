/* ctfield INCLUDE */
/* encoding=ISO8859-1 */
/* lang=C20 */

/* structure definition for ctfield extraction calls */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-01, David A­D­ Morano
	File was originally written.
	
*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CTFIELD_INCLUDE
#define	CTFIELD_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<stdintx.h>


#define	CTFIELD		struct ctfield_head


struct ctfield_head {
	char	*lp ;			/* line pointer */
	char	*fp ;			/* ctfield pointer */
	int	rlen ;			/* line length remaining */
	int	flen ;			/* ctfield length */
	int	term ;			/* terminating character */
} ;

typedef	CTFIELD		ctfield_head ;

EXTERNC_begin

extern int ctfield_start(ctfield *,const char *,int) noex ;
extern int ctfield_get(ctfield *,cchar *) noex ;
extern int ctfield_term(ctfield *,cchar *) noex ;
extern int ctfield_sharg(ctfield *,cchar *,char *,int) noex ;
extern int ctfield_finish(ctfield *) noex ;

EXTERNC_end


#endif /* CTFIELD_INCLUDE */


