/* dialuux SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* perform remote UUX service execution */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-10, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	DIALUUX_INCLUDE
#define	DIALUUX_INCLUDE	


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>		/* function-modifier definitions */


/* options */
#define	DIALUUX_OQUEUE		FM_QUEUE
#define	DIALUUX_ONOREPORT	FM_NOREPORT


EXTERNC_begin

extern int dialuux(cchar *,cchar *,cchar *,cchar **,cchar *,cchar *,int) noex ;

EXTERNC_end


#endif /* DIALUUX_INCLUDE */


