/* bpihdr HEADER */
/* lang=C20 */

/* Bible-Paragraph-Index */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	BPIHDR_INCLUDE
#define	BPIHDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	BPIHDR			struct bpihdr_head
#define	BPIHDR_MAGICSIZE	16
#define	BPIHDR_MAGICSTR		"BIBLEPARAINDEX"
#define	BPIHDR_VERSION		0


struct bpihdr_head {
	uint		fsize ;
	uint		wtime ;
	uint		vioff ;
	uint		vilen ;
	uint		nverses ;
	uint		nzverses ;
	uint		maxbook ;
	uint		maxchapter ;
	uchar		vetu[4] ;
} ;

typedef	BPIHDR		bpihdr ;

EXTERNC_begin

extern int	bpihdr_rd(bpihdr *,char *,int) noex ;
extern int	bpihdr_wr(bpihdr *,cchar *,int) noex ;

EXTERNC_end


#endif /* BPIHDR_INCLUDE */


