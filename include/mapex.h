/* mapex HEADER */
/* lang=C20 */

/* map status-return (SR) values to program exit-codes (EX) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-15, David A­D­ Morano
	This code is basically an independent repeat of the same code located
	in |localmisc.h|.  That code should be dropped and instead just include
	this header file there instead.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAPEX_INCLUDE
#define	MAPEX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<utypedefs.h>
#include	<clanguage.h>


#ifndef	MAPEX
#define	MAPEX		struct mapex_map
#endif


#ifndef	STRUCT_MAPEXMAP
#define	STRUCT_MAPEXMAP
struct mapex_map {
	int	rs, ex ;
} ;
#endif /* STRUCT_MAPEXMAP */

#ifndef	EXTERN_MAXEX
#define	EXTERN_MAXEX

EXTERNC_begin

extern int	mapex(const MAPEX *,int) noex ;

EXTERNC_end

#endif /* EXTERN_MAXPEX */


#endif /* MAPEX_INCLUDE */


