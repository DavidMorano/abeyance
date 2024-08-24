/* thrcomm HEADER */
/* lang=C20 */

/* Thread-Communication (THRCOMM) */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	THRCOMM_INCLUDE
#define	THRCOMM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<usystem.h>
#include	<ptm.h>
#include	<ptc.h>


#define	THRCOMM		struct thrcomm_head
#define	THRCOMM_MAGIC	0x26293177


struct thrcomm_head {
	ptm		*mxp ;
	ptc		*cvp ;
	uint		magic ;
	volatile int	cmd ;
	volatile int	rrs ;
	volatile int	f_cmd ;
	volatile int	f_exiting ;
} ;

typedef THRCOMM		thrcomm ;

EXTERNC_begin

extern int	thrcomm_start(thrcomm *,int) noex ;
extern int	thrcomm_cmdsend(thrcomm *,int,int) noex ;
extern int	thrcomm_cmdrecv(thrcomm *,int) noex ;
extern int	thrcomm_rspsend(thrcomm *,int,int) noex ;
extern int	thrcomm_rsprecv(thrcomm *,int) noex ;
extern int	thrcomm_exiting(thrcomm *) noex ;
extern int	thrcomm_finish(thrcomm *) noex ;

EXTERNC_end


#endif /* THRCOMM_INCLUDE */


