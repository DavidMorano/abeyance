/* vars HEADER */
/* lang=C20 */

/* read or audit a VAR database */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VARS_INCLUDE
#define	VARS_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<varhdr.h>		/* <- the money shot */
#include	<localmisc.h>


#define	VARS_MAGIC	0x88773421
#define	VARS		struct vars_head
#define	VARS_INFO	struct vars_information
#define	VARS_OBJ	struct vars_object
#define	VARS_CUR	struct vars_cursor
#define	VARS_FM		struct vars_fmap
#define	VARS_MI		struct vars_mindex


struct vars_information {
	time_t		wtime ;
	time_t		mtime ;
	uint		nvars ;
	uint		nskip ;
} ;

/* this is the shared-object description */
struct vars_object {
	cchar		*name ;
	uint		objsize ;
	uint		cursize ;
} ;

struct vars_cursor {
	uint		chash ;		/* "check" hash for key */
	int		i ;
} ;

struct vars_fmap {
	char		*mdata ;	/* file map */
	time_t		ti_mod ;
	time_t		ti_map ;
	size_t		msize ;
} ;

struct vars_mindex {
	int		(*rt)[2] ;	/* mapped record table */
	int		(*it)[3] ;	/* mapped key-index table */
	char		*kst ;		/* mapped key-string table */
	char		*vst ;		/* mapped value-string table */
} ;

struct vars_head {
	cchar 		*dbname ;
	VARS_FM		vf ;
	VARS_MI		mi ;
	VARHDR		ifi ;		/* index-file (header) information */
	time_t		ti_lastcheck ;	/* time last check of file */
	uint		magic ;
	int		ncursors ;
} ;

typedef	VARS		vars ;
typedef	VARS_INFO	vars_info ;
typedef	VARS_OBJ	vars_obj ;
typedef	VARS_CUR	vars_cur ;
typedef	VARS_FM		vars_fm ;
typedef	VARS_MI		vars_mi ;

EXTERNC_begin

extern int	vars_open(vars *,cchar *) noex ;
extern int	vars_count(vars *) noex ;
extern int	vars_curbegin(vars *,vars_cur *) noex ;
extern int	vars_fetch(vars *,cchar *,int,vars_cur *,char *,int) noex ;
extern int	vars_enum(vars *,vars_cur *,char *,int,char *,int) noex ;
extern int	vars_curend(vars *,vars_cur *) noex ;
extern int	vars_getinfo(vars *,vars_info *) noex ;
extern int	vars_audit(vars *) noex ;
extern int	vars_close(vars *) noex ;

EXTERNC_end


#endif /* VARS_INCLUDE */


