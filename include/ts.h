/* ts INCLUDE (Time-Stamp) */
/* lang=C20 */

/* time-stamp file manager */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	TS_INCLUDE
#define	TS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<mapstrint.h>

#include	"tse.h"
#include	"ebuf.h"


#define	TS_MAGIC		918245636
#define	TS			struct ts_head
#define	TS_FL			struct ts_flags
#define	TS_CUR			struct ts_cursor
#define	TS_HDR			struct ts_header
#define	TS_ENT			TSE_ALL

#define	TS_FILEMAGIC		"TIMESTAMP"
#define	TS_FILEMAGICSIZE	16
#define	TS_FILEVERSION		0
#define	TS_ENDIAN		0
#define	TS_KEYNAMELEN		TSE_LKEYNAME
#define	TS_IDLEN		(TS_FILEMAGICSIZE + sizeof(uint))
#define	TS_HEADTABLEN		(3 * sizeof(uint))
#define	TS_TOPLEN		(TS_IDLEN + TS_HEADTABLEN)

/* entry flags */
#define	TS_FLA			0x01	/* flag-loadaverage */
#define	TS_FUSERS		0x02	/* flag-users */
#define	TS_FPMAVAIL		0x04	/* flag-percent_memory_available */


struct ts_header {
	uint		nentries ;
	uint		wtime ;
	uint		wcount ;
} ;

struct ts_flags {
	uint		fileinit:1 ;		/* file init'ed */
	uint		writable:1 ;
	uint		lockedread:1 ;
	uint		lockedwrite:1 ;
	uint		cursorlockbroken:1 ;	/* cursor lock broken */
	uint		cursoracc:1 ;		/* accessed while cursored? */
	uint		remote:1 ;		/* remote mounted file */
	uint		bufvalid:1 ;		/* buffer valid */
	uint		ebuf:1 ;		/* EBUF active */
} ;

struct ts_head {
	cchar		*fname ;
	ebuf		*ebmp ;			/* entry-buffer-manager */
	mapstrint	*nip ;			/* nodename index */
	time_t		ti_open ;		/* file open time */
	time_t		ti_access ;		/* file access time */
	time_t		ti_mod ;		/* file modification time */
	TS_HDR		h ;
	TS_FL		f ;
	uint		magic ;
	int		oflags ;
	int		pagesize ;
	int		filesize ;
	int		topsize ;
	int		fd ;
	int		ncursors ;
	int		fileversion, fileencoding, filetype ;
	mode_t		operm ;
	char		topbuf[TS_TOPLEN + 1] ;	/* top-buffer */
} ;

struct ts_cursor {
	int		i ;
} ;

typedef	TS		ts ;
typedef	TS_FL		ts_fl ;
typedef	TS_HDR		ts_hdr ;
typedef	TS_CUR		ts_cur ;
typedef	TS_ENT		ts_ent ;

EXTERNC_begin

extern int ts_open(ts *,cchar *,int,mode_t) noex ;
extern int ts_curbegin(ts *,ts_cur *) noex ;
extern int ts_curend(ts *,ts_cur *) noex ;
extern int ts_curenum(ts *,ts_cur *,ts_ent *) noex ;
extern int ts_match(ts *,time_t,cchar *,int,ts_ent *) noex ;
extern int ts_write(ts *,time_t,cchar *,int,ts_ent *) noex ;
extern int ts_update(ts *,time_t,ts_ent *) noex ;
extern int ts_check(ts *,time_t) noex ;
extern int ts_count(ts *) noex ;
extern int ts_close(ts *) noex ;

EXTERNC_end


#endif /* TS_INCLUDE */


