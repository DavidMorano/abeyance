/* babieshdr HEADER */
/* lang=C20 */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	BABIESHDR_INCLUDE
#define	BABIESHDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	BABIESHDR		struct babieshdr_head
#define	BABIESHDR_MAGICSIZE	16
#define	BABIESHDR_MAGICSTR	"BABIES"
#define	BABIESHDR_VERSION	0
#define	BABIESHDR_IDLEN		20


enum babieshdrhs {
	babieshdrh_shmsize,
	babieshdrh_dbsize,
	babieshdrh_dbtime,
	babieshdrh_wtime,
	babieshdrh_atime,
	babieshdrh_acount,		/* access count */
	babieshdrh_muoff,
	babieshdrh_musize,
	babieshdrh_btoff,
	babieshdrh_btlen,
	babieshdrh_overlast
} ;

struct babieshdr_head {
	uint		shmsize ;
	uint		dbsize ;
	uint		dbtime ;
	uint		wtime ;
	uint		atime ;		/* access time */
	uint		acount ;	/* access count */
	uint		muoff ;
	uint		musize ;
	uint		btoff ;
	uint		btlen ;
	uchar		vetu[4] ;
} ;

typedef	BABIESHDR	babieshdr ;

EXTERNC_begin

extern int	babieshdr_rd(babieshdr *,char *,int) noex ;
extern int	babieshdr_wr(babieshdr *,cchar *,int) noex ;

EXTERNC_end


#endif /* BABIESHDR_INCLUDE */


