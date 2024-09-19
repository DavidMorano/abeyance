/* cyihdr HEADER */
/* lang=C20 */

/* text-index for CYI-INDEX file */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CYIHDR_INCLUDE
#define	CYIHDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	CYIHDR			struct cyihdr_head
#define	CYIHDR_MAGICSIZE	16
#define	CYIHDR_MAGICSTR		"CALENDARINDEX"
#define	CYIHDR_VERSION		0


struct cyihdr_head {
	uint		fsize ;
	uint		wtime ;
	uint		diroff ;
	uint		caloff ;
	uint		vioff ;
	uint		vilen ;
	uint		vloff ;
	uint		vllen ;
	uint		nentries ;
	uint		nskip ;
	uint		year ;		/* the year index was made for */
	uchar		vetu[4] ;
} ;

typedef	CYIHDR		cyihdr ;

EXTERNC_begin

extern int cyihdr_rd(cyihdr *,char *,int) noex ;
extern int cyihdr_wr(cyihdr *,cchar *,int) noex ;

EXTERNC_end


#endif /* CYIHDR_INCLUDE */


