/* outema HEADER */
/* lang=C20 */

/* manage printing EMAs (E-Mail-Addresses) as lines */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/****************************************************************************

	This object deals with printing lines.


****************************************************************************/

#ifndef	OUTEMA_INCLUDE
#define	OUTEMA_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<usystem.h>
#include	<filer.h>
#include	<ema.h>
#include	<localmisc.h>


#define	OUTEMA_MAGIC	0x837261595
#define	OUTEMA		struct outema_head
#define	OUTEMA_FL	struct outema_flags


struct outema_flags {
	uint		comma:1 ;
} ;

struct outema_head {
	filer		*ofp ;
	OUTEMA_FL	f ;
	uint		magic ;
	int		maxlen ;
	int		rlen ;
	int		llen ;
	int		wlen ;
	int		c_values ;
	int		c_items ;
} ;

typedef	OUTEMA		outema ;
typedef	OUTEMA_FL	outema_fl ;

EXTERNC_begin

extern int	outema_start(outema *,filer *,int) noex ;
extern int	outema_ent(outema *,ema_ent *) noex ;
extern int	outema_write(outema *,cchar *,int) noex ;
extern int	outema_hdrkey(outema *,cchar *) noex ;
extern int	outema_item(outema *,cchar *,int) noex ;
extern int	outema_value(outema *,cchar *,int) noex ;
extern int	outema_needlength(outema *,int) noex ;
extern int	outema_finish(outema *) noex ;

#ifdef	COMMENT
extern int	outema_printf(outema *,cchar *,...) noex ;
#endif /* COMMENT */

EXTERNC_end


#endif	/* OUTEMA_INCLUDE */


