/* ptrwlock HEADER */
/* lang=C20 */

/* POSIX® Thread Read-Write Lock (PTRWLOCK) */
/* ** broken on SOLARIS®! ** */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	PTRWLOCK_INCLUDE
#define	PTRWLOCK_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<pthread.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<ptrwa.h>


#define	PTRWLOCK		pthread_rwlock_t
#define	PTRWLOCK_NAMELEN	(MAXNAMELEN+1)


typedef PTRWLOCK	ptrwlock ;

EXTERNC_begin

extern int	ptrwlock_create(ptrwlock *,ptrwa *) noex ;
extern int	ptrwlock_rdlock(ptrwlock *) noex ;
extern int	ptrwlock_tryrdlock(ptrwlock *) noex ;
extern int	ptrwlock_rdlockto(ptrwlock *,int) noex ;
extern int	ptrwlock_wrlock(ptrwlock *) noex ;
extern int	ptrwlock_trywrlock(ptrwlock *) noex ;
extern int	ptrwlock_wrlockto(ptrwlock *,int) noex ;
extern int	ptrwlock_unlock(ptrwlock *) noex ;
extern int	ptrwlock_destroy(ptrwlock *) noex ;

EXTERNC_end


#endif /* PTRWLOCK_INCLUDE */


