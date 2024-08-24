/* ucsthr HEADER */
/* lang=C20 */

/* interface component for UNIX® library-3c */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCSTHR_INCLUDE
#define	UCSTHR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<usystem.h>


#if	defined(OSNAME_SunOS) && (OSNAME_SunOS > 0)


EXTERNC_begin

typedef int (*shtr_sub)(void *) noex ;
typedef void (*shtr_keyf)(void *) noex ;

extern int uc_sthrcreate(caddr_t,size_t,sthr_sub,cvoid *,long) noex ;
extern int uc_sthrexit(int) noex ;
extern int uc_sthrjoin(thread_t,int *) noex ;
extern int uc_sthrsuspend(thread_t) noex ;
extern int uc_sthrcontinue(thread_t) noex ;
extern int uc_sthrminstack() noex ;
extern int uc_sthrkill(thread_t,int) noex ;
extern int uc_sthrmain() noex ;
extern int uc_sthrself() noex ;
extern int uc_sthryield() noex ;
extern int uc_sthrsigsetmask(int,const sigset_t *,sigset_t *) noex ;
extern int uc_sthrstksegment(stack_t *) noex ;
extern int uc_sthrkeycreate(thread_key_t *,sthr_keyf) noex ;
extern int uc_sthrsetspecific(thread_key_t,void *) noex ;
extern int uc_sthrgetspecific(thread_key_t,void **) noex ;
extern int uc_sthrgetconcurrency() noex ;
extern int uc_sthrsetconcurrency(int) noex ;

EXTERNC_end


#endif /* defined(OSNAME_SunOS) && (OSNAME_SunOS > 0) */


#endif /* UCSTHR_INCLUDE */


