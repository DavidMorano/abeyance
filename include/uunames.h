/* uunames HEADER */
/* lang=C20 */

/* uunames-query database manager */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UUNAMES_INCLUDE
#define	UUNAMES_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<time.h>		/* |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<vecobj.h>


#define	UUNAMES_MAGIC	0x99889298
#define	UUNAMES		struct uunames_head
#define	UUNAMES_FL	struct uunames_flags
#define	UUNAMES_OBJ	struct uunames_object
#define	UUNAMES_CUR	struct uunames_cursor


struct uunames_object {
	cchar		*name ;
	uint		objsize ;
	uint		cursize ;
} ;

struct uunames_cursor {
	int		i ;
} ;

struct uunames_flags {
	uint		varind:1 ;
} ;

struct uunames_head {
	cchar		*pr ;
	cchar		*dbname ;
	cchar		*indfname ;		/* index file-name */
	vecobj		*nlp ;			/* name-list-pointer */
	caddr_t		mapdata ;		/* index map-data */
	size_t		mapsize ;		/* index map-size */
	time_t		ti_mod ;		/* DB file modification */
	time_t		ti_map ;		/* map */
	time_t		ti_lastcheck ;
	UUNAMES_FL	f ;
	uint		magic ;
	int		ncursors ;
} ;

typedef	UUNAMES		uunames ;
typedef	UUNAMES_FL	uunames_fl ;
typedef	UUNAMES_OBJ	uunames_obj ;
typedef	UUNAMES_CUR	uunames_cur ;

EXTERNC_begin

extern int uunames_open(uunames *,cchar *,cchar *) noex ;
extern int uunames_count(uunames *) noex ;
extern int uunames_exists(uunames *,cchar *,int) noex ;
extern int uunames_curbegin(uunames *,uunames_cur *) noex ;
extern int uunames_enum(uunames *,uunames_cur *,char *,int) noex ;
extern int uunames_curend(uunames *,uunames_cur *) noex ;
extern int uunames_audit(uunames *) noex ;
extern int uunames_close(uunames *) noex ;

EXTERNC_end


#endif /* UUNAMES_INCLUDE */


