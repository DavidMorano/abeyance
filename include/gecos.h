/* gecos HEADER */
/* lang=C20 */

/* parse a GECOS field located in a buffer */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GECOS_INCLUDE
#define	GECOS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	GECOS		struct gecos_head
#define	GECOS_VAL	struct gecos_value
#define	GECOS_ITEMLEN	256


enum gecosvals {
	gecosval_organization,
	gecosval_realname,
	gecosval_account,
	gecosval_bin,
	gecosval_office,
	gecosval_wphone,
	gecosval_hphone,
	gecosval_printer,
	gecosval_overlast
} ;

struct gecos_value {
	cchar		*vp ;
	int		vl ;
} ;

struct gecos_head {
	GECOS_VAL	vals[gecosval_overlast] ;
} ;

typedef GECOS		gecos ;
typedef GECOS_VAL	gecos_val ;

EXTERNC_begin

extern int	gecos_start(gecos *,cchar *,int) noex ;
extern int	gecos_compose(gecos *,char *,int) noex ;
extern int	gecos_getval(gecos *,int,cchar **) noex ;
extern int	gecos_finish(gecos *) noex ;

EXTERNC_end


#endif /* GECOS_INCLUDE */


