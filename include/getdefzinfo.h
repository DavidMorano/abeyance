/* getdefzinfo HEADER */
/* lang=C++20 */

/* this is supposed to provide an OS-independent time management operation */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETDEFZINFO_INCLUDE
#define	GETDEFZINFO_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>		/* <- |TZABBRLEN| */


#define	DEFZINFO		struct defzinfo_head
#define	DEFZINFO_ZNAMELEN	TZABBRLEN


struct defzinfo_head {
	int	zoff  ;		/* minutes west of GMT */
	int	isdst ;		/* is-dst flag */
	char	zname[DEFZINFO_ZNAMELEN + 1] ;
} ;

typedef DEFZINFO	defzinfo ;

EXTERNC_begin

extern int	getdefzinfo(defzinfo *,int) noex ;

EXTERNC_end


#endif /* GETDEFZINFO_INCLUDE */


