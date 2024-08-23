/* sigign HEADER */
/* lang=C20 */

/* little object to block signals */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This file was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SIGIGN_INCLUDE
#define	SIGIGN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<signal.h>
#include	<usystem.h>


#define	SIGIGN_MAGIC	0x66938271
#define	SIGIGN		struct sigign_head
#define	SIGIGN_HA	struct sigign_handle


struct sigign_handle {
	SIGACTION	action ;
	int		sig ;
} ;

struct sigign_head {
	uint		magic ;
	sigset_t	osm ;
	SIGIGN_HA	*handles ;
	int		nhandles ;
	int		nblocks ;
} ;

typedef	SIGIGN		sigign ;
typedef	SIGIGN_HA	sigign_ha ;

EXTERNC_begin

extern int	sigign_start(sigign *,cint *) noex ;
extern int	sigign_finish(sigign *) noex ;

EXTERNC_end


#endif /* SIGIGN_INCLUDE */


