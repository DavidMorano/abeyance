/* langstate HEADER */
/* lang=C20 */

/* language (parse) state */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-06-29, David A­D­ Morano
	This was really made from scratch.

	= 2016-06-29, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2008,2016 David A­D­ Morano.  All rights reserved. */

#ifndef	LANGSTATE_INCLUDE
#define	LANGSTATE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<vecobj.h>


#define	LANGSTATE_MAGIC		0x13f3c204
#define	LANGSTATE		struct langstate_head
#define	LANGSTATE_FL		struct langstate_flags
#define	LANGSTATE_INFO		struct langstate_lineinfo


enum langstatetypes {
	langstatetype_clear,
	langstatetype_comment,
	langstatetype_quote,
	langstatetype_literal,
	langstatetype_overlast
} ;

struct langstate_lineinfo {
	int		line ;
	int		type ;
} ;

struct langstate_flags {
	uint		comment:1 ;
	uint		quote:1 ;
	uint		literal:1 ;
	uint		skip:1 ;
	uint		clear:1 ;
} ;

struct langstate_head {
	LANGSTATE_FL	f ;
	uint		magic ;
	int		line ;
	int		pch ;		/* previous character */
} ;

typedef LANGSTATE	langstate ;
typedef LANGSTATE_FL	langstate_fl ;
typedef LANGSTATE_INFO	langstate_info ;

EXTERNC_begin

extern int langstate_start(langstate *) noex ;
extern int langstate_proc(langstate *,int,int) noex ;
extern int langstate_stat(langstate *,langstate_info *) noex ;
extern int langstate_finish(langstate *) noex ;

EXTERNC_end


#endif /* LANGSTATE_INCLUDE */


