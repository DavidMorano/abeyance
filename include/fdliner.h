/* fdliner HEADER */
/* lang=C20 */

/* file-read line hanlding */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FDLINER_INCLUDE
#define	FDLINER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |off_t| */
#include	<unistd.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<filer.h>


#define	FDLINER			struct fdliner_head
#define	FDLINER_FL		struct fdliner_flags
#define	FDLINER_MAGIC		0x53272856
#define	FDLINER_BUFSIZEDEF	1024
#define	FDLINER_BUFSIZEBLOCK	512


struct fdliner_flags {
	bool		fnet ;
} ;

struct fdliner_head {
	filer		*fbp ;		/* allocated */
	char		*lbuf ;
	off_t		poff ;		/* file-offset previous */
	off_t		foff ;		/* file-offset current */
	FDLINER_FL	f ;
	int		llen ;
	int		fbo ;
	int		to ;		/* read time-out */
} ;


typedef FDLINER		fdliner ;
typedef FDLINER_FL	fdliner_fl ;

EXTERNC_begin

extern int fdliner_start(fdliner *,int,off_t,int) noex ;
extern int fdliner_getln(fdliner *,cchar **) noex ;
extern int fdliner_done(fdliner *) noex ;
extern int fdliner_finish(fdliner *) noex ;

EXTERNC_end


#endif /* FDLINER_INCLUDE */


