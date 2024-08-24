/* cmi HEADER */
/* lang=C20 */

/* ComMand Index object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CMI_INCLUDE
#define	CMI_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>

#include	"cmihdr.h"		/* this is the hash-file-header */


#define	CMI_MAGIC	0x88773427
#define	CMI_SUF		"cmi"		/* variable-index */
#define	CMI		struct cmi_head
#define	CMI_OBJ		struct cmi_object
#define	CMI_CUR		struct cmi_cursor
#define	CMI_ENT		struct cmi_entry
#define	CMI_LINE	struct cmi_liner
#define	CMI_INFO	struct cmi_information
#define	CMI_FMI		struct cmi_fmidx


struct cmi_obj {
	cchar		*name ;
	uint		objsize ;
	uint		cursize ;
} ;

struct cmi_i {
	time_t		idxctime ;	/* IDX creation-time */
	time_t		idxmtime ;	/* IDX modification-time */
	time_t		dbtime ;	/* DB-file time */
	size_t		dbsize ;	/* DB-file size */
	size_t		idxsize ;	/* IDX-file size */
	uint		nents ;
	uint		maxent ;
} ;

struct cmi_liner {
	uint		loff ;
	uint		llen ;
} ;

struct cmi_entry {
	CMI_LINE	*lines ;
	uint		eoff ;
	uint		elen ;
	ushort		nlines ;
	ushort		cn ;
} ;

struct cmi_cursor {
	int		i ;
} ;

struct cmi_fmidx {
	char		*mapdata ;	/* file map */
	uint		(*vt)[4] ;	/* mapped verses table */
	uint		(*lt)[2] ;	/* mapped lines table */
	time_t		ti_mod ;	/* time file modication */
	time_t		ti_map ;	/* time file map */
	size_t		mapsize ;
} ;

struct cmi_head {
	cchar 		*dbname ;
	cchar		*fname ;
	CMI_FMI		fmi ;		/* file-map information */
	CMIHDR		fhi ;		/* file-header information */
	time_t		ti_lastcheck ;	/* time last check of file */
	uint		magic ;
	int		ncursors ;
} ;

typedef	CMI		cmi ;
typedef	CMI_OBJ		cmi_obj ;
typedef	CMI_CUR		cmi_cur ;
typedef	CMI_ENT		cmi_ent ;
typedef	CMI_LINE	cmi_line ;
typedef	CMI_INFO	cmi_info ;
typedef	CMI_FMI		cmi_fmi ;

EXTERNC_begin

extern int	cmi_open(CMI *,cchar *) noex ;
extern int	cmi_count(CMI *) noex ;
extern int	cmi_getinfo(CMI *,CMI_INFO *) noex ;
extern int	cmi_read(CMI *,CMI_ENT *,char *,int,uint) noex ;
extern int	cmi_curbegin(CMI *,CMI_CUR *) noex ;
extern int	cmi_enum(CMI *,CMI_CUR *,CMI_ENT *,char *,int) noex ;
extern int	cmi_curend(CMI *,CMI_CUR *) noex ;
extern int	cmi_audit(CMI *) noex ;
extern int	cmi_close(CMI *) noex ;

EXTERNC_end


#endif /* CMI_INCLUDE */


