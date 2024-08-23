/* fmtspec HEADER */
/* lang=C20 */

/* format-specification */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-01, David A­D­ Morano
	Of course, this subroutine was inspired by the UNIX®
	equivalent, but this is my own version for a) when I do not
	have the UNIX® libraries around, and b) to customize it to
	what I want!

*/

/* Copyright © 1998 David A-D- Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	fmtspec

	Description:
	This object parses a format-specification from the |printf(3c)|
	family-type subroutines.  This object, although it can be
	used alone (for whatever purpose), normally serves as a
	helper object for the FMTSTR facility (which itself is a
	sort of |snprintf(3c)| knock-off).

*******************************************************************************/

#ifndef	FMTSPEC_INCLUDE
#define	FMTSPEC_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>
#include	<cstdlib>
#include	<cstdint>
#include	<cstdarg>
#include	<wchar.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	FMTSPEC_FL	struct fmtspec_flags


enum lenmods : short {
	lenmod_none,
	lenmod_halfhalf,
	lenmod_half,
	lenmod_long,
	lenmod_longlong,
	lenmod_imax,
	lenmod_imaxmax,
	lenmod_longdouble,
	lenmod_wide,
	lenmod_overlast
} ;

enum fmtspecmems {
	fmtspecmem_code,
	fmtspecmem_finish,
	fmtspecmem_overlast
} ;

struct fmtspec_flags {
	uint		alternate:1 ;	/* alternate form */
	uint		zerofill:1 ;	/* zero fill on left */
	uint		plus:1 ;	/* leading plus sign */
	uint		minus:1 ;	/* leading minus sign */
	uint		left:1 ;	/* left justified */
	uint		thousands:1 ;	/* group by thousands */
	uint		space:1 ;	/* leading space */
	uint		isdigit:1 ;	/* is a digit-type character */
} ;

struct fmtspec_head {
	FMTSPEC_FL	f ;
	short		fcode ;		/* the format "code" */
	short		width ;		/* <0 turns off */
	short		prec ;		/* <0 turns off */
	short		lenmod ;	/* length modifier */
	short		skiplen ;	/* skip-specification-length */
} ;

struct fmtspec ;

struct fmtspec_co {
	fmtspec		*op = nullptr ;
	int		w = -1 ;
	void operator () (fmtspec *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
} ; /* end struct (fmtspec_co) */

struct fmtspec : fmtspec_head {
	friend		fmtspec_co ;
	fmtspec_co	code ;
	fmtspec_co	finish ;
	fmtspec() noex : fmtspec_head{} {
	    code(this,fmtspecmem_code) ;
	    finish(this,fmtspecmem_finish) ;
	} ;
	int start(va_list,cchar *,int) noex ;
} ;

typedef	FMTSPEC_FL	fmtspec_fl ;


#endif /* __cplusplus */
#endif /* FMTSPEC_INCLUDE */


