/* opentmp HEADER */
/* lang=C++20 */

/* open a tempoary file (one that is removed immediately) */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	OPENTMP_INCLUDE
#define	OPENTMP_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


enum opentmps {
	opentmp_dgram,
	opentmp_stream,
	opentmp_overlast
} ;

/* options */
#define	OTM_DGRAM	(1<<0)		/* open-type-mask DGRAM */
#define	OTM_STREAM	(1<<1)		/* open-type-mask STREAM */


EXTERNC_begin

extern int opentmpfile(cchar *,int,mode_t,char *) noex ;
extern int opentmpusd(cchar *,int,mode_t,char *) noex ;
extern int opentmpuss(cchar *,int,mode_t,char *) noex ;
extern int opentmp(cchar *,int,mode_t) noex ;

EXTERNC_end


#endif /* OPENTMP_INCLUDE */


