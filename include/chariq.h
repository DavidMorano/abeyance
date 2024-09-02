/* chariq HEADER */
/* lang=C20 */

/* Character-Interlocked Queue */
/* version %I% last-modified %G% */


/* revision history:

	= 1994-03-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1994 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Manage interlocked FIFO-character operations.

*******************************************************************************/

#ifndef	CHARIQ_INCLUDE
#define	CHARIQ_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<usystem.h>
#include	<charq.h>
#include	<ptm.h>


#define	CHARIQ		struct chariq


struct chariq {
	charq		q ;
	ptm		m ;
} ;

EXTERNC_begin

extern int	chariq_start(chariq *,int) noex ;
extern int	chariq_ins(chariq *,int) noex ;
extern int	chariq_rem(chariq *,char *) noex ;
extern int	chariq_size(chariq *) noex ;
extern int	chariq_count(chariq *) noex ;
extern int	chariq_finish(chariq *) noex ;

EXTERNC_end


#endif /* CHARIQ_INCLUDE */


