/* ucsem HEADER */
/* lang=C20 */

/* UNIX® Counting Semaphore (UCSEM) */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCSEM_INCLUDE
#define	UCSEM_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<semaphore.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	UCSEM_MAGIC	0x31419877
#define	UCSEM		struct ucsem_head


struct ucsem_head {
	sem_t		*sp ;
	cchar		*name ;
	uint		magic ;
} ;

typedef UCSEM		ucsem ;

EXTERNC_begin

extern int	ucsem_open(ucsem *,cchar *,int,mode_t,uint) noex ;
extern int	ucsem_close(ucsem *) noex ;
extern int	ucsem_wait(ucsem *) noex ;
extern int	ucsem_waiti(ucsem *) noex ;
extern int	ucsem_trywait(ucsem *) noex ;
extern int	ucsem_post(ucsem *) noex ;
extern int	ucsem_unlink(ucsem *) noex ;

extern int	ucsemunlink(cchar *) noex ;
extern int	unlinkucsem(cchar *) noex ;

EXTERNC_end


#endif /* UCSEM_INCLUDE */


