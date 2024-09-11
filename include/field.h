/* field HEADER */
/* lang=C20 */

/* structure definition for field extraction calls */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-05-01, David A­D­ Morano
	This code module was originally written in VAX assembly
	(back around 1980 or so).  It was then written into C-language
	perhaps around 1983 (at AT&T Bell Laboratories).  This
	(below) is a new incarnation based on that older C-language
	code.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	field

	Description:
	This is a classic, ported forward from the old VAX-11/780
	days.  This was translated from VAX assembly language.

*******************************************************************************/

#ifndef	FIELD_INCLUDE
#define	FIELD_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<vecstr.h>


#define	FIELD		struct field_head


struct field_head {
	cchar		*lp ;		/* line pointer */
	cchar		*fp ;		/* field pointer */
	int		ll ;		/* line length remaining */
	int		fl ;		/* field length */
	int		term ;		/* terminating character */
} ; /* end struct (field_head) */

#ifdef	__cplusplus
enum fieldmems {
	fieldmem_rem,
	fieldmem_finish,
	fieldmem_overlast
} ;
struct field ;
struct field_co {
	field		*op = nullptr ;
	int		w = -1 ;
	void operator () (field *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (field_co) */
struct field : field_head {
	field_co	finish ;
	field_co	rem ;
	field() noex {
	    rem(this,fieldmem_rem) ;
	    finish(this,fieldmem_finish) ;
	} ;
	field(const field &) = delete ;
	field &operator = (const field &) = delete ;
	int start(cchar *,int = -1) noex ;
	int get(cchar *,cchar **) noex ;
	int getterm(cchar *,cchar **) noex ;
	int sharg(cchar *,char *,int) noex ;
	int remaining(cchar ** = nullptr) noex ;
	void dtor() noex ;
	~field() noex {
	    dtor() ;
	} ;
} ; /* end struct (field) */
#else
typedef FIELD		field ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	field_start(field *,cchar *,int) noex ;
extern int	field_get(field *,cchar *,cchar **) noex ;
extern int	field_getterm(field *,cchar *,cchar **) noex ;
extern int	field_sharg(field *,cchar *,char *,int) noex ;
extern int	field_remaining(field *,cchar **) noex ;
extern int	field_finish(field *) noex ;

extern int	field_word(field *,cchar *,cchar **) noex ;
extern int	field_wordphrase(field *,cchar *,char *,int) noex ;
extern int	field_srvarg(field *,cchar *,char *,int) noex ;
extern int	field_svcargs(field *,vecstr *) noex ;

static inline int field_term(field *op,cchar *tp,cchar **rpp) noex {
	return field_getterm(op,tp,rpp) ;
}

EXTERNC_end


#endif /* FIELD_INCLUDE */


