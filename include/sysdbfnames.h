/* sysdbfnames HEADER */
/* lang=C20 */

/* standard byte-order serializations */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-03-24, David A­D­ Morano
	This code is newly written but modeled after some code that
	was originally written for the Ethernet-Controller (ETHCON)
	development work.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSDBFNAMES_INCLUDE
#define	SYSDBFNAMES_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


enum sysdbfiles {
	sysdbfile_pw,			/* passwd */
	sysdbfile_sp,			/* shadow */
	sysdbfile_ua,			/* userattr */
	sysdbfile_gr,			/* group */
	sysdbfile_pj,			/* project */
	sysdbfile_pr,			/* protocols */
	sysdbfile_nw,			/* networks */
	sysdbfile_ho,			/* hosts */
	sysdbfile_sv,			/* services */
	sysdbfile_sh,			/* shells */
	sysdbfile_overlast
} ;

extern cchar	*sysdbfnames[] ;


#endif /* SYSDBFNAMES_INCLUDE */


