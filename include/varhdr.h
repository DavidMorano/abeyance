/* varhdr HEADER */
/* lang=C++20 */

/* text-index header for VAR-INDEX file */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VARHDR_INCLUDE
#define	VARHDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	VARHDR			struct varhdr_head
#define	VARHDR_MAGICSIZE	16
#define	VARHDR_MAGICSTR		"VARIND"
#define	VARHDR_VERSION		0
#define	VARHDR_FSUF		"vi"


struct varhdr_head {
	uint		fsize ;
	uint		wtime ;
	uint		ksoff ;
	uint		kslen ;
	uint		vsoff ;
	uint		vslen ;
	uint		rtoff ;
	uint		rtlen ;
	uint		itoff ;
	uint		itlen ;
	uint		nvars ;
	uint		nskip ;
	char		vetu[4] ;
} ;

typedef	VARHDR		varhdr ;

EXTERNC_begin

extern int	varhdr_rd(varhdr *,char *,int) noex ;
extern int	varhdr_wr(varhdr *,cchar *,int) noex ;

EXTERNC_end


#endif /* VARHDR_INCLUDE */


