/* strop HEADER */
/* lang=C20 */

/* string-operations */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STROP_INCLUDE
#define	STROP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	STROP		struct strop_head


struct strop_head {
	cchar		*sp ;
	int		sl ;
} ; /* end struct (strop_head) */

#ifdef	__cplusplus
enum stropmems {
	stropmem_remlen,
	stropmem_inc,
	stropmem_white,
	stropmem_whitedash,
	stropmem_whitecolon,
	stropmem_finish,
	stropmem_overlast
} ;
struct strop ;
struct strop_co {
	strop		*op = nullptr ;
	int		w = -1 ;
	void operator () (strop *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (strop_co) */
struct strop : strop_head {
	strop_co	remlen ;
	strop_co	inc ;
	strop_co	white ;
	strop_co	whitedash ;
	strop_co	whitecolon ;
	strop_co	finish ;
	strop() noex {
	    remlen(this,stropmem_remlen) ;
	    inc(this,stropmem_inc) ;
	    white(this,stropmem_white) ;
	    whitedash(this,stropmem_whitedash) ;
	    whitecolon(this,stropmem_whitecolon) ;
	    finish(this,stropmem_finish) ;
	} ;
	strop(const strop &) = delete ;
	strop &operator = (const strop &) = delete ;
	int start(cchar *,int) noex ;
	int breakfield(cchar *,cchar **) noex ;
	int whitechr(int) noex ;		/* skip wht until */
	int findchr(int) noex ;
	int findterm(cchar *) noex ;
	int spanterm(cchar *) noex ;
	int span(cchar *) noex ;
	~strop() noex {
	    (void) int(finish) ;
	} ;
} ; /* end struct (strop) */
#else	/* __cplusplus */
typedef struct strop_head	strop ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	strop_start(strop *,cchar *,int) noex ;
extern int	strop_breakfield(strop *,cchar *,cchar **) noex ;
extern int	strop_white(strop *) noex ;
extern int	strop_whitechr(strop *,int) noex ;
extern int	strop_findchr(strop *,int) noex ;
extern int	strop_findterm(strop *,cchar *) noex ;
extern int	strop_spanterm(strop *,cchar *) noex ;
extern int	strop_span(strop *,cchar *) noex ;
extern int	strop_finish(strop *) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int strop_whitedash(strop *op) noex {
	return strop_whitechr(op,'-') ;
}
inline int strop_whitecolon(strop *op) noex {
	return strop_whitechr(op,':') ;
}

#else /* __cplusplus */

static inline int strop_whitedash(strop *op) noex {
	return strop_whitechr(op,'-') ;
}
static inline int strop_whitecolon(strop *op) noex {
	return strop_whitechr(op,':') ;
}

#endif /* __cplusplus */


#endif /* STROP_UNCLUDE */


