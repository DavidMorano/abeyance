/* outline HEADER */
/* lang=C20 */

/* output lines */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-01, David A­D­ Morano
	This subroutine was originally written.

	= 1999-02-01, David A­D­ Morano
        I added a little code to "post" articles that do not have a valid
        newsgroup to a special "dead article" directory in the BB spool area.

*/

/* Copyright © 1998,1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object deals with printing lines.

*******************************************************************************/

#ifndef	OUTLINE_INCLUDE
#define	OUTLINE_INCLUDE	


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdarg.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<bfile.h>
#include	<localmisc.h>


#define	OUTLINE		struct outline_head
#define	OUTLINE_FL	struct outline_flags


struct outline_flags {
	uint		comma:1 ;
} ;

struct outline_head {
	bfile		*ofp ;
	OUTLINE_FL	f ;
	int		maxlen ;
	int		rlen ;
	int		llen ;
	int		wlen ;
	int		c_values ;
	int		c_items ;
} ;

typedef	OUTLINE		outline ;
typedef	OUTLINE_FL	outline_fl ;

EXTERNC_begin

extern int	outline_start(outline *,bfile *,int) noex ;
extern int	outline_finish(outline *) noex ;
extern int	outline_write(outline *,cchar *,int) noex ;
extern int	outline_printf(outline *,cchar *,...) noex ;
extern int	outline_item(outline *,cchar *,int) noex ;
extern int	outline_value(outline *,cchar *,int) noex ;
extern int	outline_needlength(outline *,int) noex ;

EXTERNC_end


#endif	/* OUTLINE_INCLUDE */


