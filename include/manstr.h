/* manstr HEADER */
/* lang=C20 */

/* special string manipulations */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MANSTR_INCLUDE
#define	MANSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	MANSTR		struct manstr_head


struct manstr_head {
	cchar		*sp ;
	int		sl ;
} ;

typedef	MANSTR		manstr ;

EXTERNC_begin

extern int	manstr_start(manstr *,cchar *,int) noex ;
extern int	manstr_breakfield(manstr *,cchar *,cchar **) noex ;
extern int	manstr_span(manstr *,cchar *) noex ;
extern int	manstr_whitechr(manstr *,int) noex ;	/* skip wht until */
extern int	manstr_finish(manstr *) noex ;

static inline int manstr_whitecolon(manstr *sop) noex {
	return manstr_whitechr(sop,':') ;
}
static inline int manstr_whitedash(manstr *sop) noex {
	return manstr_whitechr(sop,'-') ;
}

EXTERNC_end


#endif /* MANSTR_INCLUDE */


