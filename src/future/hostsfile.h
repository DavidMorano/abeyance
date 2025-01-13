/* hostsfile HEADER */
/* encoding=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	HOSTSFILE_INCLUDE
#define	HOSTSFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vecelem.h>
#include	<vecstr.h>


/* object defines */
#define	HOSTSFILE_MAGIC		0x31415926
#define	HOSTSFILE		struct hostsfile_head
#define	HOSTSFILE_FI		struct hostsfile_filer
#define	HOSTSFILE_ENT		struct hostsfile_entry
#define	HOSTSFILE_ERR		struct hostsfile_errline
#define	HOSTSFILE_CUR		struct hostsfile_cursor
/* other public defines */
#define	HOSTSFILE_FILEMAGIC	"hostscache"
#define	HOSTSFILE_CACHEDIR	"/var/tmp/hostscache"
#define	HOSTSFILE_CACHENAMELEN	14


struct hostsfile_cursor {
	int		i, j ;
} ;

struct hostsfile_head {
	char		*cdir ;			/* cache directory */
	vecelem		*flp ;			/* file-list-pointer */
	vecelem		*hlp ;			/* host-list-pointer */
	time_t		checktime ;
	uint		magic ;
} ;

struct hostsfile_file {
	cchar		*hostsfname ;		/* file path name */
	cchar		*cachefname ;
	time_t		mtime ;
} ;

struct hostsfile_entry {
	uint		fi ;			/* file index */
	uint		ai ;			/* access index to record */
} ;

struct hostsfile_errline {
	cchar		*filename ;
	int		line ;
} ;

typedef	HOSTSFILE	hostsfile ;
typedef	HOSTSFILE_FI	hostsfile_fi ;
typedef	HOSTSFILE_ENT	hostsfile_ent ;
typedef	HOSTSFILE_ERR	hostsfile_err ;
typedef	HOSTSFILE_CUR	hostsfile_cur ;

EXTERNC_begin

extern int hostsfile_start(hostsfile *,char *,char *,vecelem *) noex ;
extern int hostsfile_fileadd(hostsfile *,char *,vecele *) noex ;
extern int hostsfile_finish(hostsfile *) noex ;
extern int hostsfile_check(hostsfile *,vecelem *) noex ;
extern int hostsfile_curbegin(hostsfile *,hostsfile_cur *) noex ;
extern int hostsfile_curenum(hostsfile *,hostsfile_cur *,
		hostsfile_ent **) noex ;
extern int hostsfile_curend(hostsfile *,hostsfile_cur *) noex ;
extern int hostsfile_allowed(hostsfile *,char *,char *,char *,char *) noex ;
extern int hostsfile_anyallowed(hostsfile *,vecstr *,vecstr *,
		char *,char *) noex ;

#ifdef	COMMENT
extern int hostsfile_find(hostsfile *,char *,HOSTSFILE_ENT **) ;
#endif

EXTERNC_end


#endif /* HOSTSFILE_INCLUDE */


