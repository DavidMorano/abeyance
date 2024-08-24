/* nodesfile HEADER */
/* lang=C20 */

/* UNIX "nodes" file support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This little object supports "nodes" file management.


*******************************************************************************/

#ifndef	NODESFILE_INCLUDE
#define	NODESFILE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<usystem.h>
#include	<hdb.h>


#define	NODESFILE	struct nodesfile_head
#define	NODESFILE_CUR	struct nodesfile_cursor
#define	NODESFILE_FINFO	struct nodesfile_finfo


struct nodesfile_cursor {
	hdb_cur		*hcp ;
} ;

struct nodesfile_finfo {
	cchar		*fname ;
	ino_t		ino ;
	dev_t		dev ;
	time_t		mtime ;
	int		oflags ;
} ;

struct nodesfile_head {
	char		*mapbuf ;
	hdb		*nlp ;
	time_t		ti_check ;
	time_t		ti_load ;
	NODESFILE_FINFO	fi ;
	uint		pagesize ;
	uint		mapsize ;
	uint		filesize ;
	uint		maxsize ;
	uint		len ;
} ;

typedef NODESFILE	nodesfile ;
typedef NODESFILE_CUR	nodesfile_cur ;

EXTERNC_begin

extern int	nodesfile_open(nodesfile *,cchar *,int,int) noex ;
extern int	nodesfile_search(nodesfile *,cchar *,int) noex ;
extern int	nodesfile_curbegin(nodesfile *,nodesfile_cur *) noex ;
extern int	nodesfile_curend(nodesfile *,nodesfile_cur *) noex ;
extern int	nodesfile_enum(nodesfile *,nodesfile_cur *,char *,int) noex ;
extern int	nodesfile_check(nodesfile *,time_t) noex ;
extern int	nodesfile_close(nodesfile *) noex ;

EXTERNC_end


#endif /* NODESFILE_INCLUDE */


