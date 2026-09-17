/* getsysmisc HEADER */
/* lang=C20 */

/* get SYSMISC information from the kernel */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	GETSYSMISC_INCLUDE
#define	GETSYSMISC_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	GETSYSMISC	struct tsysmisc_head


struct sysmisc_head {
	uint	btime ;
	uint	ncpu ;
	uint	nproc ;
	uint	la[3] ;
} ;

typedef GETSYSMISC	sysmisc ;

EXTERNC_begin

extern int getsysmisc_get(sysmisc *,time_t) noex ;

EXTERNC_end


#endif /* GETSYSMISC_INCLUDE */


