/* ptm HEADER */
/* lang=C20 */

/* POSIX Thread Mutex manipulation */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PTM_INCLUDE
#define	PTM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<pthread.h>
#include	<usystem.h>

#include	"ptma.h"


#define	PTM	pthread_mutex_t

#ifdef	__cplusplus
enum ptmmems {
	ptmmem_create,
	ptmmem_destroy,
	ptmmem_lockbegin,
	ptmmem_lockend,
	ptmmem_overlast
} ;
struct ptm ;
struct ptm_creater {
	ptm		*op = nullptr ;
	int		w = -1 ;
	constexpr void operator () (ptm *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex {
	    return (*this)() ;
	} ;
	int operator () (ptma * = nullptr) noex ;
} ; /* end struct (ptm_creater) */
struct ptm_co {
        ptm             *op = nullptr ;
        int             w = -1 ;
        constexpr void operator () (ptm *p,int m) noex {
            op = p ;
            w = m ;
        } ;
        operator int () noex {
            return (*this)() ;
        } ;
        int operator () (int = -1) noex ;
} ; /* end struct (ptm_co) */
struct ptm : pthread_mutex_t {
	ptm_creater	create ;
	ptm_co		destroy ;
	ptm_co		lockbegin ;
	ptm_co		lockend ;
	constexpr ptm() noex {
	    create(this,ptmmem_create) ;
	    destroy(this,ptmmem_destroy) ;
	    lockbegin(this,ptmmem_lockbegin) ;
	    lockend(this,ptmmem_lockend) ;
	} ;
	ptm(const ptm &) = delete ;
	ptm &operator = (const ptm &) = delete ;
	void dtor() noex ;
	~ptm() noex {
	    dtor() ;
	} ; /* end dtor (ptm) */
} ; /* end class (ptm) */
#else
typedef PTM	ptm ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	ptm_create(ptm *,ptma *) noex ;
extern int	ptm_destroy(ptm *) noex ;
extern int	ptm_lock(ptm *) noex ;
extern int	ptm_lockto(ptm *,int) noex ;
extern int	ptm_locktry(ptm *) noex ;
extern int	ptm_unlock(ptm *) noex ;
extern int	ptm_setprioceiling(ptm *,int,int *) noex ;
extern int	ptm_getprioceiling(ptm *,int *) noex ;

EXTERNC_end


#endif /* PTM_INCLUDE */


