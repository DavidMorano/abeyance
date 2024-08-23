/* dw HEADER */
/* lang=C++20 */

/* directory watch */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DW_INCLUDE
#define	DW_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<time.h>
#include	<vecstr.h>
#include	<vecobj.h>
#include	<localmisc.h>		/* |MAXPATHLEN| */


/* object defines */
#define	DW_MAGIC	0x31415926
#define	DW		struct dw_head
#define	DW_FL		struct dw_flags
#define	DW_ENT		struct dw_entry
#define	DW_CUR		struct dw_cursor

#define	DW_DEFCHECKTIME	20		/* default check time (seconds) */

/* job states */
#define	DW_SRESERVED	0
#define	DW_SNEW		1	/* just in */
#define	DW_SCHECK	2	/* ready for validation check */
#define	DW_SREADY	3
#define	DW_SNOTSUP	4
#define	DW_SRUNNING	5
#define	DW_SRETRY	6
#define	DW_SUSER	10


struct dw_entry {
	time_t		itime ;
	time_t		mtime ;
	size_t		fsize ;
	int		state ;
	char		name[MAXPATHLEN + 1] ;
} ;

struct dw_ientry {
	cchar		*name ;
	time_t		itime ;
	time_t		mtime ;
	size_t		fsize ;
	int		state ;
} ;

struct dw_flags {
	uint		subdirs:1 ;
} ;

struct dw_head {
	vecstr		subdirs ;		/* subdirectories */
	vecobj		e ;			/* directory entries */
	cchar		*dirname ;		/* directory path */
	void		(*callback)(DW_ENT *,int,void *) noex ;
	cvoid		*argp ;
	time_t		opentime ;		/* time FD was cached */
	time_t		mtime ;			/* directory mod-time */
	time_t		checktime ;		/* time last checked */
	time_t		removetime ;		/* last checked for removed */
	DW_FL		f ;
	uint		magic ;
	int		checkint ;		/* file check interval */
	int		fd ;			/* cached directory FD */
	int		count_new ;
	int		count_checkable ;
} ;

struct dw_cursor {
	int		i ;
} ;

typedef	DW		dw ;
typedef	DW_FL		dw_flags ;
typedef	DW_ENT		dw_ent ;
typedef	DW_CUR		dw_cur ;

EXTERNC_begin

extern int dw_start(dw *,cchar *) noex ;
extern int dw_finish(dw *) noex ;
extern int dw_find(dw *,cchar *,dw_ent *) noex ;
extern int dw_del(dw *,dw_cur *) noex ;
extern int dw_check(dw *,time_t) noex ;
extern int dw_curbegin(dw *,dw_cur *) noex ;
extern int dw_curend(dw *,dw_cur *) noex ;
extern int dw_enum(dw *,dw_cur *,dw_ent *) noex ;
extern int dw_enumcheckable(dw *,dw_cur *,dw_ent *) noex ;
extern int dw_state(dw *,int,int) noex ;

EXTERNC_end


#endif /* DW_INCLUDE */


