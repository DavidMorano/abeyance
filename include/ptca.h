/* ptca HEADER */
/* lang=C20 */

/* POSIX® Thread (Pthread) Condition-Vvariable Attributes */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	PTCA_INCLUDE
#define	PTCA_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<pthread.h>
#include	<usystem.h>


#define	PTCA		pthread_condattr_t

#ifdef	__cplusplus
enum ptcamems {
	ptcamem_create,
	ptcamem_destroy,
	ptcamem_setpshared,
	ptcamem_overlast
} ;
struct ptca ;
struct ptca_co {
        ptca             *op = nullptr ;
        int             w = -1 ;
        constexpr void operator () (ptca *p,int m) noex {
            op = p ;
            w = m ;
        } ;
        int operator () (int = 0) noex ;
} ; /* end struct (ptca_co) */
struct ptca : pthread_condattr_t {
	ptca_co		create ;
	ptca_co		destroy ;
	ptca_co		setpshared ;
	constexpr ptca() noex {
	    create(this,ptcamem_create) ;
	    destroy(this,ptcamem_destroy) ;
	    setpshared(this,ptcamem_setpshared) ;
	} ;
	ptca(const ptca &) = delete ;
	ptca &operator = (const ptca &) = delete ;
	int	getpshared(int *) noex ;
	void dtor() noex ;
	~ptca() noex {
	    dtor() ;
	} ; /* end dtor (ptca) */
} ; /* end class (ptca) */
#else
typedef PTMA		ptca ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	ptca_create(ptca *) noex ;
extern int	ptca_destroy(ptca *) noex ;
extern int	ptca_setpshared(ptca *,int) noex ;
extern int	ptca_getpshared(ptca *,int *) noex ;

EXTERNC_end


#endif /* PTCA_INCLUDE */


