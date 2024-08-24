/* terment HEADER */
/* lang=C20 */

/* methods for the TERMENT object */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-07-19, David A­D­ Morano
	This subroutine was written for Rightcore Network Services (RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This code provides the methods for the TERMENT object. The
	TERMENT object, while residing in a file, forms a single
	record in a file-database of records. This is similar to a
	raw UTMPX object when it is written out to the 'utmpx' file.
	This object is used by the TERMENQ object to represent a
	record in the TERMENQ database.

*******************************************************************************/

#ifndef	TERMENT_INCLUDE
#define	TERMENT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* |pid_t| */
#include	<sys/param.h>
#include	<stdlib.h>
#include	<string.h>
#include	<usystem.h>

#include	"terment.h"


#define	TERMENT		struct terment_head

/* entry type values */
#define	TERMENT_TEMPTY		0	/* entry is unused */
#define	TERMENT_TLOGINPROC	1	/* a "getty" waiting for login */
#define	TERMENT_TUSERPROC	2	/* a regular user process */
#define	TERMENT_TDEADPROC	3	/* dead process (moved to WTERMENT) */

/* entry lengths */
#define	TERMENT_LID		4
#define	TERMENT_LLINE		32
#define	TERMENT_LTERMTYPE	32
#define	TERMENT_LANSWER		116


struct terment_head {
	pid_t		sid ;		/* session ID */
	uchar		type ;		/* type of entry (see above) */
	uchar		termcode ;	/* ANSI terminal code */
	uchar		lines ;
	uchar		cols ;
	char		id[TERMENT_LID] ;	/* UTMP ID */
	char		line[TERMENT_LLINE] ;
	char		termtype[TERMENT_LTERMTYPE] ;
	char		answer[TERMENT_LANSWER] ;
} ;

typedef TERMENT		terment ;

EXTERNC_begin

extern int terment_start(terment *) noex ;
extern int terment_settype(terment *,int) noex ;
extern int terment_setsid(terment *,pid_t) noex ;
extern int terment_setcode(terment *,int) noex ;
extern int terment_setlines(terment *,int) noex ;
extern int terment_setcols(terment *,int) noex ;
extern int terment_setid(terment *,cchar *,int) noex ;
extern int terment_setline(terment *,cchar *,int) noex ;
extern int terment_settermtype(terment *,cchar *,int) noex ;
extern int terment_setanswer(terment *,cchar *,int) noex ;

extern int terment_gettype(terment *) noex ;
extern int terment_getsid(terment *) noex ;
extern int terment_getcode(terment *) noex ;
extern int terment_getlines(terment *) noex ;
extern int terment_getcols(terment *) noex ;
extern int terment_getid(terment *,cchar **) noex ;
extern int terment_getline(terment *,cchar **) noex ;
extern int terment_gettermtype(terment *,cchar **) noex ;
extern int terment_getanswer(terment *,cchar **) noex ;
extern int terment_finish(terment *) noex ;

EXTERNC_end


#endif /* TERMENT_INCLUDE */


