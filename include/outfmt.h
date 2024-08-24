/* outfmt HEADER */
/* lang=C20 */

/* output formats */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	OUTFMT_INCLUDE
#define	OUTFMT_INCLUDE


#include	<envstandards.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


enum ofis {
	outfmt_raw,
	outfmt_fill,
	outfmt_bible,
	outfmt_overlast
} ;

extern cpcchar		outfmts[] ;


#endif /* OUTFMT_INCLUDE */


