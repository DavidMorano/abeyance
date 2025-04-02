/* uvariables SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* define various system (global) variables */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-04-11, David D-A- Morano
	This subroutine was written for Rightcore Network Services.

	= 2014-06-27, David D-A- Morano
	I updated this to use the 'constexpr' capability of C++14.

*/

/* Copyright © 2001,2014 David D-A- Morano.  All rights reserved. */

/*******************************************************************************

	We define some system (global) variables in this module.
	This code (below) is some sort of rather lame attempt at
	putting most of the most important global variables used
	by the (rather) low-level facilities of the either the UNIX©
	system or the UNIX© system C-language library into a single
	place.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>

#include	"uvariables.hh"


/* local defines */


/* typedefs */


/* external variables */


/* external subroutines */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */

constinit const varnames	varname ;
constinit const syswords	sysword ;
constinit const valuelims	valuelimit ;

const digbufsizes		digbufsize ;


/* exported subroutines */


