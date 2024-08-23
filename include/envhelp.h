/* envhelp HEADER */
/* lang=C20 */

/* help w/ handling environment */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-10, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ENVHELP_INCLUDE
#define	ENVHELP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<vechand.h>
#include	<strpack.h>


#define	ENVHELP		struct envhelp_head


struct envhelp_head {
	vechand		*elp ;		/* Environment-List-Pointer */
	strpack		*spp ;		/* String-Pack-Pointer */
} ;

typedef ENVHELP		envhelp ;

EXTERNC_begin

extern int envhelp_start(envhelp *,mainv,mainv) noex ;
extern int envhelp_present(envhelp *,cchar *,int,cchar **) noex ;
extern int envhelp_envset(envhelp *,cchar *,cchar *,int) noex ;
extern int envhelp_sort(envhelp *) noex ;
extern int envhelp_getvec(envhelp *,mainv *) noex ;
extern int envhelp_finish(envhelp *) noex ;

EXTERNC_end


#endif /* ENVHELP_INCLUDE */


