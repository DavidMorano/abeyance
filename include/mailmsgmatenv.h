/* mailmsgmatenv HEADER */
/* lang=C20 */

/* try to match on a UNIX® mail-message envelope */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSGMATENV_INCLUDE
#define	MAILMSGMATENV_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


/* object defines */
#define	MMENVDAT		struct mmenvdat_head
#define	MMENVDAT_FL		struct mmenvdat_flags
#define	MMENVDAT_ELEM		struct mmenvdat_elemement


struct mmenvdat_flags {
	uint		start:1 ;	/* starting envelope? (most are) */
} ;

struct mmenvdat_elemement {
	cchar		*ep ;
	int		el ;
} ;

struct mmenvdat_head {
	MMENVDAT_ELEM		a ;	/* address (EMA) */
	MMENVDAT_ELEM		d ;	/* date */
	MMENVDAT_ELEM		r ;	/* remove-from (EMA) */
	MMENVDAT_FL		f ;	/* flags */
	int			rt ;	/* remote type */
} ;

typedef MMENVDAT		mmenvdat ;
typedef MMENVDAT_FL		mmenvdat_fl ;
typedef MMENVDAT_ELEM		mmenvdat_elem ;

EXTERNC_begin

extern int mailmsgmatenv(mmenvdat *,cchar *,int) noex ;

EXTERNC_end


#endif /* MAILMSGMATENV_INCLUDE */


