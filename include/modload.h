/* modload HEADER */
/* lang=C20 */

/* module-load management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MODLOAD_INCLUDE
#define	MODLOAD_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


#define	MODLOAD			struct modload_head
#define	MODLOAD_MI		struct modload_mid
#define	MODLOAD_MAGIC		0x99447246
#define	MODLOAD_DEFENTS		(44 * 1000)
#define	MODLOAD_SYMSUF		"_mod"

#define	MODLOAD_OLIBVAR		(1<<0)
#define	MODLOAD_OPRS		(1<<1)
#define	MODLOAD_OSDIRS		(1<<2)
#define	MODLOAD_OAVAIL		(1<<3)	/* make global-syms available */
#define	MODLOAD_OSELF		(1<<4)


struct modload_mid {
	cchar		*name ;
	int		mv[1] ;
} ;

struct modload_head {
	void		*sop ;		/* shared-object (SO) pointer */
	cchar		*modname ;
	MODLOAD_MI	*midp ;
	uint		magic ;
} ;

typedef MODLOAD		modload ;
typedef MODLOAD_MI	modload_mi ;

EXTERNC_begin

extern int modload_open(modload *,cchar *,cchar *,cchar *,int,mainv) noex ;
extern int modload_getmv(modload *,int) noex ;
extern int modload_getmva(modload *,int *,int) noex ;
extern int modload_getsym(modload *,cchar *,cvoid **) noex ;
extern int modload_close(modload *) noex ;

EXTERNC_end


#endif /* MODLOAD_INCLUDE */


