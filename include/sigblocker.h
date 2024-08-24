/* sigblocker HEADER */
/* lang=C20 */

/* little object to block signals */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This file was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SIGBLOCKER_INCLUDE
#define	SIGBLOCKER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


#define	SIGBLOCKER	struct sigblocker_head


struct sigblocker_head {
	sigset_t	osm ;
} ;

#ifdef	__cplusplus
enum sigblockermems {
	sigblockermem_start,
	sigblockermem_finish,
	sigblockermem_overlast
} ;
struct sigblocker ;
struct sigblocker_co {
	sigblocker	*op = nullptr ;
	int		w = -1 ;
	void operator () (sigblocker *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () (const int * = nullptr) noex ;
} ; /* end struct (sigblocker_co) */
struct sigblocker : sigblocker_head {
	sigblocker_co	start ;
	sigblocker_co	finish ;
	sigblocker() noex {
	    start(this,sigblockermem_start) ;
	    finish(this,sigblockermem_finish) ;
	} ;
	~sigblocker() noex {
	    (void) int(finish) ;
	}
} ; /* end class (sigblocker) */

#else
typedef	SIGBLOCKER	sigblocker ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	sigblocker_start(sigblocker *,cint *) noex ;
extern int	sigblocker_finish(sigblocker *) noex ;

EXTERNC_end


#endif /* SIGBLOCKERr_INCLUDE */


