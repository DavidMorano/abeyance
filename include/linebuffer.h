/* linebuffer HEADER */
/* lang=C20 */

/* provide a line-buffer of the system-defined line-length */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LINEBUFFER_INCLUDE
#define	LINEBUFFER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	LINEBUFFER	struct linebuffer_head


struct linebuffer_head {
	char		*lbuf ;
	int		llen ;
} ;

#ifdef	__cplusplus
enum linebuffermems {
	linebuffermem_start,
	linebuffermem_finish,
	linebuffermem_overlast
} ;
struct linebuffer ;
struct linebuffer_co {
	linebuffer	*op = nullptr ;
	int		w = -1 ;
	void operator () (linebuffer *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (linebuffer_co) */
struct linebuffer : linebuffer_head {
	linebuffer_co	start ;
	linebuffer_co	finish ;
	linebuffer() noex {
	    start(this,linebuffermem_start) ;
	    finish(this,linebuffermem_finish) ;
	} ;
	linebuffer(const linebuffer &) = delete ;
	linebuffer &operator = (const linebuffer &) = delete ;
	~linebuffer() noex {
	    (void) int(finish) ;
	} ;
} ; /* end struct (linebuffer) */
#else /* __cplusplus */
typedef LINEBUFFER		linebuffer ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	linebuffer_start(linebuffer *) noex ;
extern int	linebuffer_finish(linebuffer *) noex ;

EXTERNC_end


#endif /* LINEBUFFER_INCLUDE */


