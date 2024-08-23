/* uinfo HEADER */
/* lang=C20 */

/* UNIX® information (a cache for 'uname(2)' and sisters) */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	UINFO_INCLUDE
#define	UINFO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	UINFO_NAMES	struct uinfo_infoname
#define	UINFO_AUXS	struct uinfo_infoaux


struct uinfo_infoname {
	cchar		*sysname ;
	cchar		*nodename ;
	cchar		*release ;
	cchar		*version ;
	cchar		*machine ;
} ;

struct uinfo_infoaux {
	cchar		*architecture ;
	cchar		*platform ;
	cchar		*hwprovider ;
	cchar		*hwserial ;
	cchar		*nisdomain ;
} ;

typedef UINFO_NAMES	uinfo_names ;
typedef UINFO_AUXS	uinfo_auxs ;

EXTERNC_begin

extern int uinfo_init() noex ;
extern int uinfo_name(uinfo_names *) noex ;
extern int uinfo_aux(uinfo_auxs *) noex ;
extern int uinfo_fini() noex ;

EXTERNC_end


#endif /* UINFO_INCLUDE */


