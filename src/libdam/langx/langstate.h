/* langstate HEADER */
/* charset=ISO8859-1 */
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
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


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
} ; /* end enum (langstatetypes) */

struct langstate_flags {
	uint		comment:1 ;
	uint		quote:1 ;
	uint		literal:1 ;
	uint		skip:1 ;
	uint		clear:1 ;
} ; /* end struct (langstate_flags) */

struct langstate_lineinfo {
	int		line ;
	int		type ;
} ; /* end struct (langstate_lineinfo) */

struct langstate_head {
	LANGSTATE_FL	fl ;
	uint		magic ;
	int		line ;
	int		pch ;		/* previous character */
} ; /* end struct (linestage_head) */

typedef LANGSTATE_FL	langstate_fl ;
typedef LANGSTATE_INFO	langstate_info ;

#ifdef	__cplusplus
enum langstatemems {
    	langstatemem_start,
	langstatemem_finish,
	langstatemem_code,
	langstatemem_overlast
} ;
struct langstate ;
struct langstate_co {
	langstate	*op = nullptr ;
	int		w = -1 ;
	void operator () (langstate *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (langstate_co) */
struct langstate : langstate_head {
	langstate_co	start ;
	langstate_co	finish ;
	langstate_co	code ;
	langstate() noex {
	    start	(this,langstatemem_start) ;
	    finish	(this,langstatemem_finish) ;
	    code	(this,langstatemem_code) ;
	    magic = 0 ;
	} ; /* end ctor */
	langstate(const langstate &) = delete ;
	langstate &operator = (const langstate &) = delete ;
	int proc(int,int = -1) noex ;
	int procln(int,cchar *,int = -1) noex ;
	int getstat(langstate_info *) noex ;
	operator int () noex ;
	void dtor() noex ;
	destruct langstate() {
	    if (magic) dtor() ;
	} ;
} ; /* end struct (langstate) */
#else	/* __cplusplus */
typedef LANGSTATE	langstate ;
#endif /* __cplusplus */

EXTERNC_begin

extern int langstate_start	(langstate *) noex ;
extern int langstate_proc	(langstate *,int,int) noex ;
extern int langstate_procln	(langstate *,int,cchar *,int) noex ;
extern int langstate_getstat	(langstate *,langstate_info *) noex ;
extern int langstate_code	(langstate *) noex ;
extern int langstate_finish	(langstate *) noex ;

EXTERNC_end


#endif /* LANGSTATE_INCLUDE */


