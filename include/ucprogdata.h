/* ucprogdata HEADER */
/* lang=C20 */

/* UNIX® program-data cache */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCPROGDATA_INCLUDE
#define	UCPROGDATA_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


#define	UCPROGDATA_DNETLOAD	0	/* netload */
#define	UCPROGDATA_DSYSTAT	1	/* sys-stat */


EXTERNC_begin

extern int ucprogdata_init() noex ;
extern int ucprogdata_set(int,cchar *,int,int) noex ;
extern int ucprogdata_get(int,char *,int) noex ;
extern int ucprogdata_fini() noex ;

EXTERNC_end


#endif /* UCPROGDATA_INCLUDE */


