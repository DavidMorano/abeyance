/* memfile HEADER */
/* lang=C20 */

/* provides a memory-mapped file for writing */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MEMFILE_INCLUDE
#define	MEMFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	MEMFILE_MAGIC	0x54728822
#define	MEMFILE		struct memfile_head


struct memfile_head {
	char		*dbuf ;
	void		*bp ;
	size_t		off ;
	size_t		dlen ;
	size_t		fsize ;
	uint		magic ;
	int		pagesize ;
	int		fd ;
} ;

typedef MEMFILE		memfile ;

EXTERNC_begin

extern int	memfile_open(memfile *,cchar *,int,mode_t) noex ;
extern int	memfile_write(memfile *,cvoid *,int) noex ;
extern int	memfile_len(memfile *) noex ;
extern int	memfile_allocation(memfile *) noex ;
extern int	memfile_tell(memfile *,off_t *) noex ;
extern int	memfile_getbuf(memfile *,void *) noex ;
extern int	memfile_close(memfile *) noex ;

EXTERNC_end


#endif /* MEMFILE_INCLUDE */


