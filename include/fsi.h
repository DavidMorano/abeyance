/* fsi HEADER */
/* lang=C20 */

/* FIFO-String-Interlocked */
/* version %I% last-modified %G% */


/* revision history:

	= 1994-03-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Manage interlocked string-FIFO operations.

*******************************************************************************/

#ifndef	FSI_INCLUDE
#define	FSI_INCLUDE


#include	<envstandards.h>	/* must be before others */
#include	<usystem.h>
#include	<ptm.h>
#include	<fifostr.h>


#define	FSI		struct fsi_head


struct fsi_head {
	ptm		*mxp ;
	fifostr		*qsp ;
} ;

typedef FSI		fsi ;

EXTERNC_begin

extern int	fsi_start(fsi *) noex ;
extern int	fsi_add(fsi *,cchar *,int) noex ;
extern int	fsi_remove(fsi *,char *,int) noex ;
extern int	fsi_count(fsi *) noex ;
extern int	fsi_finish(fsi *) noex ;

EXTERNC_end


#endif /* FSI_INCLUDE */


