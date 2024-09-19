/* bvshdr HEADER (Bible Verse Structure) */
/* lang=C20 */

/* index for Bible-Verse-Structure (BVS) file */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-10-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	BVSHDR_INCLUDE
#define	BVSHDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	BVSHDR			struct bvshdr_head
#define	BVSHDR_MAGICSIZE	16
#define	BVSHDR_MAGICSTR		"BVS"
#define	BVSHDR_VERSION		0


struct bvshdr_head {
	uint		fsize ;		/* file-size */
	uint		wtime ;		/* write-time */
	uint		nverses ;	/* total verses */
	uint		nzverses ;	/* non-zero verses */
	uint		nzbooks ;	/* number of non-zero books */
	uint		btoff ;		/* book-table */
	uint		btlen ;
	uint		ctoff ;		/* chapter-table */
	uint		ctlen ;
	uchar		vetu[4] ;
} ;

typedef	BVSHDR		bvshdr ;

EXTERNC_begin

extern int	bvshdr_rd(bvshdr *,char *,int) noex ;
extern int	bvshdr_wr(bvshdr *,char *,int) noex ;

EXTERNC_end


#endif /* BVSHDR_INCLUDE */


