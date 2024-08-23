/* sighand HEADER */
/* lang=C++20 */

/* little object to block signals */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This file was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SIGHAND_INCLUDE
#define	SIGHAND_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<signal.h>
#include	<usystem.h>


#define	SIGHAND_MAGIC	0x66938271
#define	SIGHAND		struct sighand_head
#define	SIGHAND_HA	struct sighand_handle


struct sighand_handle {
	SIGACTION	action ;
	int		sig ;
} ;

struct sighand_head {
	SIGHAND_HA	*handles ;
	sigset_t	osm ;
	uint		magic ;
	int		nhandles ;
	int		nblocks ;
} ;

typedef SIGHAND		sighand ;
typedef	SIGHAND_HA	sighand_ha ;

EXTERNC_begin

typedef void (*sighand_handler)(int,siginfo_t *,void *) noex ;

extern int sighand_start(SIGHAND *,cint *,cint *,cint *,sighand_handler) noex ;
extern int sighand_finish(SIGHAND *) noex ;

EXTERNC_end


#endif /* SIGHAND_INCLUDE */


