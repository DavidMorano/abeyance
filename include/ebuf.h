/* ebuf HEADER */
/* lang=C20 */

/* manage entry buffering of a file */
/* version %I% last-modified %G% */


/* revision history:

	= 2003-10-22, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2003 David A­D­ Morano.  All rights reserved. */

#ifndef	EBUF_INCLUDE
#define	EBUF_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


#define	EBUF_MAGIC	1092847456
#define	EBUF_NENTS	4
#define	EBUF		struct ebuf_head
#define	EBUF_FL		struct ebuf_flags
#define	EBUF_WAY	struct ebuf_way


struct ebuf_way {
	char		*wbuf ;		/* buffer */
	off_t		woff ;		/* "way" offset to file entries */
	uint		utime ;		/* usage time */
	int		wlen ;
	int		nvalid ;	/* number of valid entries */
} ;

struct ebuf_flags {
	uint		init:1 ;	/* init'ed */
} ;

struct ebuf_head {
	EBUF_WAY	*ways ;
	EBUF_FL		f ;
	uint		magic ;
	uint		utimer ;	/* usage timer (fake time) */
	uint		soff ;		/* starting offset */
	int		esize ;		/* entry size */
	int		nways ;		/* maximum number of ways */
	int		iways ;		/* active number of ways */
	int		npw ;		/* number entries per way */
	int		nentries ;	/* number of total entries */
	int		fd ;
} ;

typedef EBUF		ebuf ;

EXTERNC_begin

extern int ebuf_start(ebuf *,int,uint,int,int,int) noex ;
extern int ebuf_finish(ebuf *) noex ;
extern int ebuf_read(ebuf *,int,char **) noex ;
extern int ebuf_write(ebuf *,int,cvoid *) noex ;
extern int ebuf_count(ebuf *) noex ;
extern int ebuf_sync(ebuf *) noex ;
extern int ebuf_invalidate(ebuf *,int) noex ;

EXTERNC_end


#endif /* EBUF_INCLUDE */


