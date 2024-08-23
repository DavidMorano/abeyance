/* stdfnames HEADER */
/* lang=C20 */

/* standard byte-order serializations */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-03-24, David A­D­ Morano
	This code is newly written but modeled after some code that
	was originally written to get some standardized variable
	serialization for the Ethernet-Controller (ETHCON) development
	work.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

#ifndef	STDFNAMES_INCLUDE
#define	STDFNAMES_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#ifndef	STDFNIN
#define	STDFNIN		stdfnames[stdfile_in]
#endif

#ifndef	STDFNOUT
#define	STDFNOUT	stdfnames[stdfile_out]
#endif

#ifndef	STDFNERR
#define	STDFNERR	stdfnames[stdfile_err]
#endif

#ifndef	STDFNLOG
#define	STDFNLOG	stdfnames[stdfile_log]
#endif

#ifndef	STDFNNULL
#define	STDFNNULL	stdfnames[stdfile_null]
#endif


enum stdfiles {
	stdfile_in,
	stdfile_out,
	stdfile_err,
	stdfile_log,
	stdfile_null,
	stdfile_overlast
} ;

extern cchar	*const stdfnames[] ;


#endif /* STDFNAMES_INCLUDE */


