/* outbuf HEADER */
/* lang=C20 */

/* output buffer management (really?) */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	OUTBUF_INCLUDE
#define	OUTBUF_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


#define	OUTBUF		struct outbuf_head


struct outbuf_head {
	char		*obuf ;
	int		olen ;
	int		f_alloc ;
} ;

typedef OUTBUF		outbuf ;

EXTERNC_begin

extern int	outbuf_start(outbuf *,char *,int) noex ;
extern int	outbuf_get(outbuf *,char **) noex ;
extern int	outbuf_finish(outbuf *) noex ;

EXTERNC_end


#endif /* OUTBUF_INCLUDE */


