/* dupstr HEADER */
/* lang=C20 */

/* create a (writable) duplicate of a string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DUPSTR_INCLUDE
#define	DUPSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	DUPSTR		struct dupstr
#define	DUPSTR_SHORTLEN	32


struct dupstr {
	char		*as ;	/* allocated string */
	char		buf[DUPSTR_SHORTLEN+1] ;
} ;

typedef DUPSTR		dupstr ;

EXTERNC_begin

extern int	dupstr_start(dupstr *,cchar *,int,char **) noex ;
extern int	dupstr_finish(dupstr *) noex ;

EXTERNC_end


#endif /* DUPSTR_INCLUDE */


