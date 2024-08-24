/* ptc HEADER */
/* lang=C20 */

/* POSIX Thread Condition manipulation */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-07-28, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	PTC_INCLUDE
#define	PTC_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<pthread.h>
#include	<time.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>

#include	"ptm.h"			/* needed for interface */
#include	"ptca.h"


#define	PTC		pthread_cond_t

#ifdef	__cplusplus
enum ptcmems {
	ptcmem_destroy,
	ptcmem_broadcast,
	ptcmem_signal,
	ptcmem_overlast
} ;
struct ptc ;
struct ptc_creater {
	ptc		*op = nullptr ;
	void init(ptc *p) noex {
	    op = p ;
	} ;
	operator int () noex {
	    return (*this)() ;
	} ;
	int operator () (ptca * = nullptr) noex ;
} ; /* end struct (ptc_creater) */
struct ptc_co {
        ptc             *op = nullptr ;
        int             w = -1 ;
        constexpr void operator () (ptc *p,int m) noex {
            op = p ;
            w = m ;
        } ;
        operator int () noex {
            return (*this)() ;
        } ;
        int operator () (int = -1) noex ;
} ; /* end struct (ptc_co) */
struct ptc : pthread_cond_t {
	ptc_creater	create ;
	ptc_co		destroy ;
	ptc_co		broadcast ;
	ptc_co		signal ;
	constexpr ptc() noex {
	    create.init(this) ;
	    destroy(this,ptcmem_destroy) ;
	    broadcast(this,ptcmem_broadcast) ;
	    signal(this,ptcmem_signal) ;
	} ;
	ptc(const ptc &) = delete ;
	ptc &operator = (const ptc &) = delete ;
	int wait(ptm *,int = -1) noex ;
	int timedwait(ptm *,CTIMESPEC *) noex ;
	int reltimedwaitnp(ptm *,CTIMESPEC *) noex ;
	void dtor() noex ;
	~ptc() noex {
	    dtor() ;
	} ; /* end dtor (ptc) */
} ; /* end class (ptc) */
#else
typedef PTC	ptc ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	ptc_create(ptc *,ptca *) noex ;
extern int	ptc_destroy(ptc *) noex ;
extern int	ptc_broadcast(ptc *) noex ;
extern int	ptc_signal(ptc *) noex ;
extern int	ptc_wait(ptc *,ptm *) noex ;
extern int	ptc_waiter(ptc *,ptm *,int) noex ;
extern int	ptc_timedwait(ptc *,ptm *,CTIMESPEC *) noex ;
extern int	ptc_reltimedwaitnp(ptc *,ptm *,CTIMESPEC *) noex ;

EXTERNC_end


#endif /* PTC_INCLUDE */


