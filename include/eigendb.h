/* eigendb HEADER */
/* lang=C20 */

/* store eigen words in a database */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	EIGENDB_INCLUDE
#define	EIGENDB_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<strpack.h>
#include	<hdb.h>
#include	<localmisc.h>


#define	EIGENDB		struct eigendb_head
#define	EIGENDB_CUR	struct eigendb_cursor
#define	EIGENDB_MAGIC	0x83726112


struct eigendb_cursor {
	hdb_cur		*hcp ;
} ;

struct eigendb_head {
	strpack		*spp ;		/* string-pack-pointer */
	hdb		*dbp ;		/* data-base-pointer */
	uint		magic ;
} ;

typedef EIGENDB		eigendb ;
typedef	EIGENDB_CUR	eigendb_cur ;

EXTERNC_begin

extern int	eigendb_open(eigendb *,cchar *) noex ;
extern int	eigendb_addfile(eigendb *,cchar *) noex ;
extern int	eigendb_addword(eigendb *,cchar *,int) noex ;
extern int	eigendb_exists(eigendb *,cchar *,int) noex ;
extern int	eigendb_count(eigendb *) noex ;
extern int	eigendb_curbegin(eigendb *,eigendb_cur *) noex ;
extern int	eigendb_curend(eigendb *,eigendb_cur *) noex ;
extern int	eigendb_enum(eigendb *,eigendb_cur *,cchar **) noex ;
extern int	eigendb_close(eigendb *) noex ;

EXTERNC_end


#endif /* EIGENDB_INCLUDE */


