/* uvariables HEADER */
/* lang=C++20 */

/* this is a database of commonly used global variables */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-04-11, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object contains various commonly used environment
	variable names.

*******************************************************************************/

#ifndef	UVARIABLES_INCLUDE
#define	UVARIABLES_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>

#include	<syswords.hh>
#include	<varnames.hh>
#include	<valuelims.hh>
#include	<digbufsizes.hh>


extern const syswords		sysword ;
extern const varnames		varname ;
extern const valuelims		valuelimit ;
extern const digbufsizes	digbufsize ;


#endif	/* __cplusplus */
#endif /* UVARIABLES_INCLUDE */


