/* lockrw HEADER */
/* lang=C++20 */

/* Reader-Writer Lock (LOCKRW) */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	LOCKRW_INCLUDE
#define	LOCKRW_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<pthread.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<ptm.h>
#include	<ptc.h>


#define	LOCKRW		struct lockrw_head
#define	LOCKRW_MAGIC	0x26293176


struct lockrw_head {
	ptm		*mxp ;
	ptc		*cvp ;
	uint		magic ;
	int		readers ;
	int		writers ;
	int		waitwriters ;
	int		waitreaders ;
} ; /* end struct (lockrw_head) */

#ifdef	__cplusplus
enum lockrwmems {
	lockrwmem_create,
	lockrwmem_destroy,
	lockrwmem_rdlock,
	lockrwmem_wrlock,
	lockrwmem_unlock,
	lockrwmem_overlast
} ;
struct lockrw ;
struct lockrw_co {
	lockrw		*op = nullptr ;
	int		w = -1 ;
	void operator () (lockrw *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex {
	    return (*this)() ;
	} ;
	int operator () (int = -1) noex ;
} ; /* end struct (lockrw_co) */
struct lockrw : lockrw_head {
	lockrw_co	create ;
	lockrw_co	destroy ;
	lockrw_co	rdlock ;
	lockrw_co	wrlock ;
	lockrw_co	unlock ;
	lockrw() noex : lockrw_head{} {
	    create(this,lockrwmem_create) ;
	    destroy(this,lockrwmem_destroy) ;
	    rdlock(this,lockrwmem_rdlock) ;
	    wrlock(this,lockrwmem_wrlock) ;
	    unlock(this,lockrwmem_unlock) ;
	} ;
	lockrw(const lockrw &) = delete ;
	lockrw &operator = (const lockrw &) = delete ;
	~lockrw() noex {
	    (void) int(destroy) ;
	}
} ; /* end struct (lockrw) */
#else
typedef LOCKRW		lockrw ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	lockrw_create(lockrw *,int) noex ;
extern int	lockrw_rdlock(lockrw *,int) noex ;
extern int	lockrw_wrlock(lockrw *,int) noex ;
extern int	lockrw_unlock(lockrw *) noex ;
extern int	lockrw_readers(lockrw *) noex ;
extern int	lockrw_destroy(lockrw *) noex ;

EXTERNC_end


#endif /* LOCKRW_INCLUDE */


