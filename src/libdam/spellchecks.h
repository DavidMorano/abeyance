/* spellchecks HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* SPELLCHECKS object implementation */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	SPELLCHECKS_INCLUDE
#define	SPELLCHECKS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<vechand.h>


#define	SPELLCHECKS		struct spellchecks_head
#define	SPELLCHECKS_FL		struct spellchecks_flags
#define	SPELLCHECKS_OBJ		struct spellchecks_object
#define	SPELLCHECKS_CUR		struct spellchecks_cursor
#define	SPELLCHECKS_MAGIC	0x99447246
#define	SPELLCHECKS_CONFNAME	"conf"
#define	SPELLCHECKS_SEARCHNAME	"spellchecks"


struct spellchecks_object {
	cchar		*name ;
	uint		objsize ;
	uint		cursize ;
} ; /* end struct */

struct spellchecks_cursor {
	void		*results ;
	uint		magic ;
	uint		nresults ;
	int		i ;
} ; /* end struct */

struct spellchecks_flags {
	uint		vind:1 ;		/* index is loaded */
} ; /* end struct */

struct spellchecks_head {
	cchar		*pr ;
	cchar		*tmpdname ;
	vechand		*slp ;			/* spell-list-pointer */
	SPELLCHECKS_FL	fl ;
	uint		magic ;
	int		nlists ;
	int		ncursors ;
} ; /* end struct */

typedef	SPELLCHECKS	spellchecks ;
typedef	SPELLCHECKS_FL	spellchecks_fl ;
typedef	SPELLCHECKS_OBJ	spellchecks_obj ;
typedef	SPELLCHECKS_CUR	spellchecks_cur ;

EXTERNC_begin

extern int spellchecks_start(spellchecks *,cchar *,cchar *) noex ;
extern int spellchecks_count(spellchecks *) noex ;
extern int spellchecks_look(spellchecks *,cchar *,int) noex ;
extern int spellchecks_looks(spellchecks *,bits *,cchar *,int) noex ;
extern int spellchecks_curbegin(spellchecks *,spellchecks_cur *) noex ;
extern int spellchecks_curenum(spellchecks *,spellchecks_cur *,
		char *,int) noex ;
extern int spellchecks_curend(spellchecks *,spellchecks_cur *) noex ;
extern int spellchecks_check(spellchecks *,time_t) noex ;
extern int spellchecks_audit(spellchecks *) noex ;
extern int spellchecks_finish(spellchecks *) noex ;

EXTERNC_end


#endif /* SPELLCHECKS_INCLUDE */


