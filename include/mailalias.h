/* mailalias */
/* lang=C20 */

/* indexed PASSWD GECOS DB */
/* version %I% last-modified %G% */


/* revision history:

	= 2003-06-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2003 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILALIAS_INCLUDE
#define	MAILALIAS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<usystem.h>
#include	<vecstr.h>
#include	<ids.h>
#include	<localmisc.h>


#define	MAILALIAS		struct mailalias_head
#define	MAILALIAS_INFO		struct mailalias_information
#define	MAILALIAS_CUR		struct mailalias_cursor
#define	MAILALIAS_FI		struct mailalias_finfo
#define	MAILALIAS_FL		struct mailalias_flags
#define	MAILALIAS_MAGIC		0x23456187
#define	MAILALIAS_FSUF		"mac"		/* Mail Alias Cache */
#define	MAILALIAS_MAGICSTR	"MAILALIAS"
#define	MAILALIAS_MAGICSIZE	16
#define	MAILALIAS_NSHIFT	8
#define	MAILALIAS_FILEVERSION	0
#define	MAILALIAS_DEFAPTAB	"default"

#define	MAILALIAS_OSEC		(1<<0)		/* use secondard hash */
#define	MAILALIAS_ORANDLC	(1<<1)		/* use |randlc()| */


struct mailalias_cursor {
	uint		magic ;
	int		i ;
} ;

struct mailalias_information {
	time_t		wtime ;		/* time DB written */
	uint		wcount ;	/* write counter */
	uint		entries ;	/* total number of entries */
	uint		version ;
	uint		encoding ;
	uint		type ;
	uint		collisions ;
} ;

struct mailalias_finfo {
	ino_t		ino ;
	dev_t		dev ;
	time_t		mtime ;
	size_t		fsize ;
} ;

struct mailalias_flags {
	uint		remote:1 ;
	uint		ocreate:1 ;
	uint		owrite:1 ;
	uint		fileinit:1 ;
	uint		cursorlockbroken:1 ;
	uint		cursoracc:1 ;
	uint		held:1 ;
	uint		lockedread:1 ;
	uint		lockedwrite:1 ;
	uint		needcreate:1 ;
} ;

struct mailalias_head {
	mainv		aprofile ;
	cchar		*pr ;
	cchar		*apname ;
	cchar		*dbfname ;
	cchar		*skey ;
	cchar		*sval ;
	int		*keytab ;
	int		(*rectab)[2] ;
	int		(*indtab)[2] ;
	char		*mapdata ;
	vecstr		*afp ;
	ids		*idp ;
	time_t		ti_aprofile ;
	time_t		ti_open ;
	time_t		ti_access ;
	time_t		ti_map ;
	time_t		ti_check ;
	time_t		ti_filecheck ;
	time_t		ti_fileold ;
	size_t		mapsize ;
	MAILALIAS_FI	fi ;
	MAILALIAS_FL	f ;
	uint		magic ;
	int		pagesize ;
	int		sklen ;
	int		svlen ;
	int		ktlen ;
	int		rtlen, rilen ;
	int		collisions ;
	int		cursors ;
	int		fd ;
	int		oflags, otype ;
	int		ropts ;
	mode_t		operm ;
} ;

typedef	MAILALIAS	mailalias ;
typedef	MAILALIAS_INFO	mailalias_info ;
typedef	MAILALIAS_CUR	mailalias_cur ;
typedef	MAILALIAS_FI	mailalias_fi ;
typedef	MAILALIAS_FL	mailalias_fl ;

EXTERNC_begin

extern int	mailalias_open(mailalias *,cc *,cc *,int,mode_t,int) noex ;
extern int	mailalias_getinfo(mailalias *,mailalias_info *) noex ;
extern int	mailalias_curbegin(mailalias *,mailalias_cur *) noex ;
extern int	mailalias_enum(mailalias *,mailalias_cur *,
			char *,int,char *,int) noex ;
extern int	mailalias_fetch(mailalias *,int,cchar *,
			mailalias_cur *,char *,int) noex ;
extern int	mailalias_curend(mailalias *,mailalias_cur *) noex ;
extern int	mailalias_count(mailalias *) noex ;
extern int	mailalias_indcount(mailalias *) noex ;
extern int	mailalias_audit(mailalias *) noex ;
extern int	mailalias_close(mailalias *) noex ;

EXTERNC_end


#endif /* MAILALIAS_INCLUDE */


