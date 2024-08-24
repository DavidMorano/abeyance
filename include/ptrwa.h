/* ptrwa HEADER */
/* lang=C20 */

/* POSIX® Thread read-write lock attribute manipulation */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	PTRWA_INCLUDE
#define	PTRWA_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<pthread.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	PTRWA		pthread_rwlockattr_t


#ifndef	TYPEDEF_PTRWA
#define	TYPEDEF_PTRWA
typedef	PTRWA		ptrwa ;
#endif

EXTERNC_begin

extern int	ptrwa_create(ptrwa *) noex ;
extern int	ptrwa_destroy(ptrwa *) noex ;
extern int	ptrwa_setpshared(ptrwa *,int) noex ;
extern int	ptrwa_getpshared(ptrwa *,int *) noex ;

EXTERNC_end


#endif /* PTRWA_INCLUDE */


