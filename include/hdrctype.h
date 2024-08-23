/* hdrctype HEADER */
/* lang=C20 */


/* revision history:

	= 1998-02-23, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	HDRCTYPE_INCLUDE
#define	HDRCTYPE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	HDRCTYPE	struct hdrctype_head
#define	HDRCTYPE_T	struct hdrctype_type
#define	HDRCTYPE_MAGIC	0x53232857


struct hdrctype_type {
	cchar		*tp ;
	int		tl ;
} ;

struct hdrctype_head {
	HDRCTYPE_T	main ;
	HDRCTYPE_T	sub ;
} ;

typedef HDRCTYPE	hdrctype ;
typedef	HDRCTYPE_T	hdrctype_t ;

EXTERNC_begin

extern int hdrctype_decode(hdrctype *,cchar *,int) noex ;

EXTERNC_end


#endif /* HDRCTYPE_INCLUDE */



