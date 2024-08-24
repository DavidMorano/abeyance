/* ptma HEADER */
/* lang=C20 */

/* POSIX® Thread Mutex Attribute manipulation */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	PTMA_INCLUDE
#define	PTMA_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<pthread.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	PTMA		pthread_mutexattr_t

#ifdef	__cplusplus
enum ptmamems {
	ptmamem_create,
	ptmamem_destroy,
	ptmamem_setprioceiling,
	ptmamem_setprotocol,
	ptmamem_setpshared,
	ptmamem_setrobustnp,
	ptmamem_settype,
	ptmamem_overlast
} ;
struct ptma ;
struct ptma_co {
        ptma             *op = nullptr ;
        int             w = -1 ;
        constexpr void operator () (ptma *p,int m) noex {
            op = p ;
            w = m ;
        } ;
        int operator () (int = 0) noex ;
} ; /* end struct (ptma_co) */
struct ptma : pthread_mutexattr_t {
	ptma_co		create ;
	ptma_co		destroy ;
	ptma_co		setprioceiling ;
	ptma_co		setprotocol ;
	ptma_co		setpshared ;
	ptma_co		setrobustnp ;
	ptma_co		settype ;
	constexpr ptma() noex {
	    create(this,ptmamem_create) ;
	    destroy(this,ptmamem_destroy) ;
	    setprioceiling(this,ptmamem_setprioceiling) ;
	    setprotocol(this,ptmamem_setprotocol) ;
	    setpshared(this,ptmamem_setpshared) ;
	    setrobustnp(this,ptmamem_setrobustnp) ;
	    settype(this,ptmamem_settype) ;
	} ;
	ptma(const ptma &) = delete ;
	ptma &operator = (const ptma &) = delete ;
	int	getprioceiling(int *) noex ;
	int	getprotocol(int *) noex ;
	int	getpshared(int *) noex ;
	int	getrobustnp(int *) noex ;
	int	gettype(int *) noex ;
	void dtor() noex ;
	~ptma() noex {
	    dtor() ;
	} ; /* end dtor (ptma) */
} ; /* end class (ptma) */
#else
typedef PTMA		ptma ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	ptma_create(ptma *) noex ;
extern int	ptma_destroy(ptma *) noex ;
extern int	ptma_getprioceiling(ptma *,int *) noex ;
extern int	ptma_setprioceiling(ptma *,int) noex ;
extern int	ptma_getprotocol(ptma *,int *) noex ;
extern int	ptma_setprotocol(ptma *,int) noex ;
extern int	ptma_getpshared(ptma *,int *) noex ;
extern int	ptma_setpshared(ptma *,int) noex ;
extern int	ptma_getrobustnp(ptma *,int *) noex ;
extern int	ptma_setrobustnp(ptma *,int) noex ;
extern int	ptma_gettype(ptma *,int *) noex ;
extern int	ptma_settype(ptma *,int) noex ;

EXTERNC_end


#endif /* PTMA_INCLUDE */


