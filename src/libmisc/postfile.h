/* postfile HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* indexed POST file */
/* version %I% last-modified %G% */


/* revision history:

	= 2002-05-01, David A­D­ Morano
	This object module was created from some previous code, of
	which I longer know what it was.

*/

/* Copyright © 2002 David A­D­ Morano.  All rights reserved. */

#ifndef	POSTFILE_INCLUDE
#define	POSTFILE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<time.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<realname.h>


/* object defines */
#define	POSTFILE_MAGIC		0x23456787
#define	POSTFILE		struct postfile_head
#define	POSTFILE_INFO		struct postfile_information
#define	POSTFILE_CUR		struct postfile_cursor
#define	POSTFILE_ENT		struct postfile_entry
/* file values */
#define	POSTFILE_FILEMAGIC	"POSTINDEX"
#define	POSTFILE_FILEMAGICSIZE	16
#define	POSTFILE_FILEMAGICLEN	szof(POSTFILEMAGIC)
#define	POSTFILE_FILEVERSION	0
#define	POSTFILE_FILETYPE	0
/* constants */
#define	POSTFILE_USERNAMELEN	32
#define	POSTFILE_NINDICES	3
/* options */
#define	POSTFILE_OSEC		(1 << 0)	/* use secondard hash */
#define	POSTFILE_ORANDLC	(1 << 1)	/* use |randlc(3c)| */
/* special options */
#define	POSTFILE_FLASTFULL	(1 << 0)	/* full last name */


struct postfile_cursor {
	int		wi ;
	int		i[POSTFILE_NINDICES] ;
	uint		magic ;
} ;

struct postfile_information {
	time_t		writetime ;	/* time DB written */
	uint		writecount ;	/* write counter */
	uint		entries ;	/* total number of entries */
	uint		version ;
	uint		encoding ;
	uint		type ;
	uint		collisions ;
} ;

struct postfile_entry {
	uint		username ;
	uint		last ;
	uint		first ;
	uint		m1 ;
	uint		m2 ;
} ;

struct postfile_flags {
	uint		remote : 1 ;
	uint		fileinit : 1 ;
	uint		cursor : 1 ;
	uint		cursorlockbroken : 1 ;
	uint		cursoracc : 1 ;
	uint		held : 1 ;
	uint		lockedread : 1 ;
	uint		lockedwrite : 1 ;
} ;

struct postfile_head {
	char		*fname ;
	caddr_t		mapbuf ;
	cchar		*stab ;
	POSTFILE_ENT	*rectab ;
	uint		(*recind[POSTFILE_NINDICES])[2] ;
	POSTFILE_FL	fl ;
	time_t		mtime ;
	time_t		opentime ;
	time_t		accesstime ;
	uint		magic ;
	uint		pagesize ;
	uint		mapsize ;
	uint		filesize ;
	uint		stlen ;
	uint		rtlen ;
	uint		rilen ;
	uint		collisions ;
	int		fd ;
	int		oflags ;
	int		ropts ;
	mode_t		operm ;
} ;

typedef	POSTFILE	postfile ;
typedef	POSTFILE_INFO	postfile_info ;
typedef	POSTFILE_CUR	postfile_cur ;
typedef	POSTFILE_ENT	postfile_ent ;

EXTERNC_begin

extern int	postfile_open(postfile *,cchar *) noex ;
extern int	postfile_info(postfile *,postfile_info *) noex ;
extern int	postfile_curbegin(postfile *,postfile_cur *) noex ;
extern int	postfile_curend(postfile *,postfile_cur *) noex ;
extern int	postfile_curenum(postfile *,postfile_cur noex *,
			realname *,char *) noex ;
extern int	postfile_fetch(postfile *,realname *,postfile_cur *,
			int,char *) noex ;
extern int	postfile_close(postfile *) noex ;

EXTERNC_end


#endif /* POSTFILE_INCLUDE */



