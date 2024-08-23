/* lineindex HEADER */
/* lang=C20 */

/* line indexing object */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LINEINDEX_INCLUDE
#define	LINEINDEX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<time.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>


#define	LINEINDEX		struct lineindex_head
#define	LINEINDEX_FL		struct lineindex_flags
#define	LINEINDEX_INFO		struct lineindex_information
#define	LINEINDEX_CUR		struct lineindex_cursor

#define	LINEINDEX_MAGIC		0x23456787
#define	LINEINDEX_FILEMAGIC	"LINEINDEX"
#define	LINEINDEX_FILEMAGICSIZE	16
#define	LINEINDEX_FILEMAGICLEN	sizeof(LINEINDEX_FILEMAGIC)
#define	LINEINDEX_FILEVERSION	1
#define	LINEINDEX_ENDIAN	1	/* always network order */
#define	LINEINDEX_FILETYPE	0


struct lineindex_cursor {
	int		i ;
} ;

struct lineindex_information {
	time_t		wtime ;		/* time DB written */
	uint		lines ;		/* total number of entries */
	uint		version ;
	uint		encoding ;
	uint		type ;
} ;

struct lineindex_flags {
	uint		remote:1 ;
	uint		fileinit:1 ;
	uint		cursorlockbroken:1 ;
	uint		cursoracc:1 ;
	uint		wantwrite:1 ;
} ;

struct lineindex_head {
	cchar		*ifn ;		/* index-file-name */
	cchar		*tfn ;		/* text-file-name */
	uint		*rectab ;
	caddr_t		mapbuf ;
	time_t		wtime ;
	time_t		mtime ;
	time_t		ti_open ;
	time_t		ti_map ;
	time_t		ti_check ;
	time_t		ti_access ;
	size_t		mapsize ;
	LINEINDEX_FL	f ;
	uint		magic ;
	int		pagesize ;
	int		filesize ;
	int		lines ;
	int		cursors ;
	int		fd ;
	int		of ;
	int		ropts ;
	mode_t		om ;
} ;

typedef	LINEINDEX		lineindex ;
typedef	LINEINDEX_FL		lineindex_fl ;
typedef	LINEINDEX_INFO		lineindex_info ;
typedef	LINEINDEX_CUR		lineindex_cur ;

EXTERNC_begin

extern int lineindex_open(lineindex *,cchar *,int,mode_t,cchar *) noex ;
extern int lineindex_lookup(lineindex *,uint,off_t *) noex ;
extern int lineindex_curbegin(lineindex *,lineindex_cur *) noex ;
extern int lineindex_curend(lineindex *,lineindex_cur *) noex ;
extern int lineindex_enum(lineindex *,lineindex_cur *,off_t *) noex ;
extern int lineindex_check(lineindex *,time_t) noex ;
extern int lineindex_count(lineindex *) noex ;
extern int lineindex_close(lineindex *) noex ;

EXTERNC_end


#endif /* LINEINDEX_INCLUDE */


