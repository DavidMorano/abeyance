/* pwihdr HEADER */
/* lang=C20 */

/* Password-Index Header (PWI) */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PWIHDR_INCLUDE
#define	PWIHDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	PWIHDR			struct pwihdr_head
#define	PWIHDR_MAGICSIZE	16
#define	PWIHDR_MAGICSTR		"IPASSWD"
#define	PWIHDR_VERSION		0
#define	PWIHDR_TYPE		0


enum pwihdrs {
	pwihdr_fsize,		/* source DB file size */
	pwihdr_wrtime,
	pwihdr_wrcount,
	pwihdr_rectab,
	pwihdr_reclen,
	pwihdr_recsize,
	pwihdr_strtab,
	pwihdr_strlen,
	pwihdr_strsize,
	pwihdr_idxlen,
	pwihdr_idxsize,
	pwihdr_idxl1,
	pwihdr_idxl3,
	pwihdr_idxf,
	pwihdr_idxfl3,
	pwihdr_idxun,
	pwihdr_overlast
} ;

struct pwihdr_head {
	uint		fsize ;
	uint		wrtime ;
	uint		wrcount ;
	uint		rectab ;
	uint		recsize ;
	uint		reclen ;
	uint		strtab ;
	uint		strlen ;
	uint		strsize ;
	uint		idxlen ;
	uint		idxsize ;
	uint		idxl1 ;
	uint		idxl3 ;
	uint		idxf ;
	uint		idxfl3 ;
	uint		idxun ;
	uchar		vetu[4] ;
} ;

typedef PWIHDR		pwihdr ;

EXTERNC_begin

extern int	pwihdr_rd(pwihdr *,char *,int) noex ;
extern int	pwihdr_wr(pwihdr *,cchar *,int) noex ;

EXTERNC_end


#endif /* PWIHDR_INCLUDE */


