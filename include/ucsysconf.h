/* ucsysconf HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* auxillary operating system support */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a
	very small way to make up for some of the immense brain-damage
	within the Apple Darwin operating system.

*******************************************************************************/

#ifndef	UCSYSCONF_INCLUDE
#define	UCSYSCONF_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<unistd.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


enum missingconfstrs {
	missingconfstr_publicdir = 1000,
	missingconfstr_tmpdir,
	missingconfstr_cachedir,
	missingconfstr_overlast
} ;


#ifndef	_CS_PUBLICDIR
#ifdef	_CS_DARWIN_USER_DIR	
#define	_CS_PUBLICDIR	_CS_DARWIN_USER_DIR	
#else
#define	_CS_PUBLICDIR	missingconfstr_publicdir
#endif
#endif

#ifndef	_CS_TMPDIR
#ifdef	_CS_DARWIN_USER_TEMP_DIR
#define	_CS_TMPDIR	_CS_DARWIN_USER_TEMP_DIR
#else
#define	_CS_TMPDIR	missingconfstr_tmpdir
#endif
#endif

#ifndef	_CS_CACHEDIR
#ifdef	_CS_DARWIN_USER_CACHE_DIR
#define	_CS_CACHEDIR	_CS_DARWIN_USER_CACHE_DIR
#else
#define	_CS_CACHEDIR	missingconfstr_cachedir
#endif
#endif


EXTERNC_begin

extern int	uc_sysconfval(int,long *) noex ;
extern int	uc_sysconfstr(char *,int,int) noex ;

static inline int uc_sysconf(int req,long *rp) noex {
	return uc_sysconfval(req,rp) ;
}
static inline int uc_sysconfmaxline() noex {
	cint		req = _SC_LINE_MAX ;
	return uc_sysconfval(req,nullptr) ;
}

EXTERNC_end


#endif /* UCSYSCONF_INCLUDE */


