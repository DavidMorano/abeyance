/* upt HEADER */
/* lang=C20 */

/* UNIX® POSIX Thread manipulation */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-08-20, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UPT_INCLUDE
#define	UPT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<pthread.h>
#include	<usystem.h>
#include	<pta.h>


EXTERNC_begin

typedef int (*uptsub_f)(void *) noex ;

extern int uptcreate(pthread_t *,pthread_attr_t *,uptsub_f,void *) noex ;
extern int uptexit(int) noex ;
extern int uptonce(pthread_once_t *,void_f) noex ;
extern int uptjoin(pthread_t,int *) noex ;
extern int uptdetach(pthread_t) noex ;
extern int uptcancel(pthread_t) noex ;
extern int uptkill(pthread_t,int) noex ;
extern int uptsetschedparam(pthread_t,int,SCHEDPARAM *) noex ;
extern int uptgetschedparam(pthread_t,int *,SCHEDPARAM *) noex ;
extern int uptgetconcurrency() noex ;
extern int uptsetconcurrency(int) noex ;
extern int uptsetcancelstate(int,int *) noex ;
extern int uptsetcanceltype(int,int *) noex ;
extern int upttestcancel() noex ;
extern int uptequal(pthread_t,pthread_t) noex ;
extern int uptself(pthread_t *) noex ;
extern int uptatfork(void_f,void_f,void_f) noex ;
extern int uptncpus(int) noex ;

EXTERNC_end


#endif /* UPT_INCLUDE */


