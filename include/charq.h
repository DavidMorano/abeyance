/* charq */
/* lang=C20 */

/* character queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This obejct module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CHARQ_INCLUDE
#define	CHARQ_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<usystem.h>


#define	CHARQ		struct charq_head


struct charq_head {
	char		*buf ;
	int		ri ;
	int		wi ;
	int		sz ;
	int		count ;
} ;

typedef CHARQ		charq ;

EXTERNC_begin

extern int	charq_start(charq *,int) noex ;
extern int	charq_ins(charq *,int) noex ;
extern int	charq_rem(charq *,char *) noex ;
extern int	charq_remall(charq *) noex ;
extern int	charq_size(charq *) noex ;
extern int	charq_count(charq *) noex ;
extern int	charq_finish(charq *) noex ;

EXTERNC_end


#endif /* CHARQ_INCLUDE */


