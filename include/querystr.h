/* querystr HEADER */
/* lang=C99 */

/* Query-String manager */
/* version %I% last-modified %G% */


/* revision history:

	= 2017-09-25, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */

#ifndef	QUERYSTR_INCLUDE
#define	QUERYSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<strpack.h>


#define	QUERYSTR	struct querystr_head
#define	QUERYSTR_FL	struct querystr_flags
#define	QUERYSTR_CUR	struct querystr_cur


struct querystr_cur {
	int		i ;
} ;

struct querystr_flags {
	uint		packer:1 ;
} ;

struct querystr_head {
	strpack		*spp ;
	cchar		*(*kv)[2] ;
	QUERYSTR_FL	open ;
	int		n ;
} ;

typedef QUERYSTR	querystr ;
typedef QUERYSTR_FL	querystr_fl ;
typedef QUERYSTR_CUR	querystr_cur ;

EXTERNC_begin

extern int querystr_start(querystr *,cchar *,int) noex ;
extern int querystr_count(querystr *) noex ;
extern int querystr_already(querystr *,cchar *,int) noex ;
extern int querystr_curbegin(querystr *,querystr_cur *) noex ;
extern int querystr_curend(querystr *,querystr_cur *) noex ;
extern int querystr_fetch(querystr *,cchar *,int,querystr_cur *,cchar **) noex ;
extern int querystr_enum(querystr *,querystr_cur *,cchar **,cchar **) noex ;
extern int querystr_get(querystr *,int,cchar **,cchar **) noex ;
extern int querystr_finish(querystr *) noex ;

EXTERNC_end


#endif /* QUERYSTR_INCLUDE */


