/* spwd HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* Apple-Darwin types */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the MacOS operating system.


*******************************************************************************/

#ifndef	SPWD_INCLUDE
#define	SPWD_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#ifndef	SPWD
#define	SPWD		struct spwd
#endif

#ifndef	CSPWD
#define	CSPWD		const struct spwd
#endif


#if	defined(SYSHAS_SHADOW) && (SYSHAS_SHADOW > 0)

#include	<shadow.h>

#else /* defined(SYSHAS_SHADOW) && (SYSHAS_SHADOW > 0) */

struct spwd {
	char		*sp_namp ;
	char		*sp_pwdp ;
	unsigned long	sp_flag ;
	long		sp_lstchg ;
	long		sp_min ;
	long		sp_max ;
	long		sp_warn ;
	long		sp_inact ;
	long		sp_expire ;
} ; /* end struct (spwd) */

EXTERNC_begin

void setspent() noex ;
void endspent() noex ;
extern SPWD	*getspent() noex ;
extern SPWD	*getspnam(cchar *) noex ;

EXTERNC_end

#endif /* defined(SYSHAS_SHADOW) && (SYSHAS_SHADOW > 0) */

EXTERNC_begin

extern int	getspent_rp(SPWD *,char *,int) noex ;
extern int	getspnam_rp(SPWD *,char *,int,cchar *) noex ;

EXTERNC_end


#endif /* SPWD_INCLUDE */


