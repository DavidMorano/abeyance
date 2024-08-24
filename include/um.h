/* um HEADER */
/* lang=C20 */

/* UNIX® Memory-Management interface */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the subroutine declarations for various
	UNIX® system Memory-Management subroutines.

	Names:
	u_mmapbegin
	u_mmapend
	u_mlockbegin
	u_mlockend
	u_mlockallbegin
	u_mlockallend
	u_mcntl
	u_mincore
	u_mprotect
	u_madvise
	u_msync
	u_mlockp

	Aliases:
	u_mapfile		-> u_mmapbegin
	u_mmap			-> u_mmapbegin
	u_munmap		-> u_mmapend

*******************************************************************************/

#ifndef	UM_INCLUDE
#define	UM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/mman.h>
#include	<unistd.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<usys.h>


#ifndef	MLOCKP_LOCKNON
#define	MLOCKP_LOCKNON	UNLOCK		/* for |u_mlockp(3u)| */
#endif

#ifndef	MLOCKP_LOCKALL
#define	MLOCKP_LOCKALL	PROCLOCK	/* for |u_mlockp(3u)| */
#endif

#ifndef	MLOCKP_LOCKTXT
#define	MLOCKP_LOCKTXT	TXTLOCK		/* for |u_mlockp(3u)| */
#endif

#ifndef	MLOCKP_LOCKDAT
#define	MLOCKP_LOCKDAT	DATLOCK		/* for |u_mlockp(3u)| */
#endif


EXTERNC_begin

extern int u_mmapbegin(void *,size_t,int,int,int,off_t,void *) noex ;
extern int u_mmapend(void *,size_t) noex ;
extern int u_mlockbegin(void *,size_t) noex ;
extern int u_mlockend(void *,size_t) noex ;
extern int u_mlockallbegin(int) noex ;
extern int u_mlockallend() noex ;
extern int u_mcntl(void *,size_t,int,void *,int,int) noex ;
extern int u_mincore(void *,size_t,char *) noex ;
extern int u_mprotect(void *,size_t,int) noex ;
extern int u_madvise(void *,size_t,int) noex ;
extern int u_msync(void *,size_t,int) noex ;
extern int u_mlockp(int) noex ;

/* legacy */
extern int u_mapfile(void *,size_t,int,int,int,off_t,void *) noex ;
extern int u_mmap(void *,size_t,int,int,int,off_t,void *) noex ;
extern int u_munmap(void *,size_t) noex ;

EXTERNC_end


#endif /* UM_INCLUDE */


