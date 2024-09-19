/* bvihdr HEADER */
/* lang=C20 */

/* index for bible-verse file */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-10-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	BVIHDR_INCLUDE
#define	BVIHDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	BVIHDR			struct bvihdr_head
#define	BVIHDR_MAGICSIZE	16
#define	BVIHDR_MAGICSTR		"BIBLEVERSEINDEX"
#define	BVIHDR_VERSION		0


struct bvihdr_head {
	uint		fsize ;
	uint		wtime ;
	uint		vioff ;
	uint		vilen ;
	uint		vloff ;
	uint		vllen ;
	uint		nverses ;
	uint		nzverses ;
	uint		maxbook ;
	uint		maxchapter ;
	uchar		vetu[4] ;
} ;

typedef	BVIHDR		bvihdr ;

EXTERNC_begin

extern int	bvihdr_rd(bvihdr *,char *,int) noex ;
extern int	bvihdr_wr(bvihdr *,cchar *,int) noex ;

EXTERNC_end


#endif /* BVIHDR_INCLUDE */


