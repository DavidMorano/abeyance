/* pta HEADER */
/* lang=C20 */

/* POSIX Thread Attribute manipulation */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-07-28, David A-D- Morano
	Originally written for Rightcore Network Services.

*/
/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	PTA_INCLUDE
#define	PTA_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<pthread.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	PTA	pthread_attr_t


#ifndef	TYPEDEF_PTA
#define	TYPEDEF_PTA
typedef PTA	pta ;
#endif

EXTERNC_begin

extern int	pta_create(pta *) noex ;
extern int	pta_destroy(pta *) noex ;
extern int	pta_setstacksize(pta *,size_t) noex ;
extern int	pta_getstacksize(pta *,size_t *) noex ;
extern int	pta_setguardsize(pta *,size_t) noex ;
extern int	pta_getguardsize(pta *,size_t *) noex ;
extern int	pta_setstackaddr(pta *,void *) noex ;
extern int	pta_getstackaddr(pta *,void **) noex ;
extern int	pta_setdetachstate(pta *,int) noex ;
extern int	pta_getdetachstate(pta *,int *) noex ;
extern int	pta_setscope(pta *,int) noex ;
extern int	pta_getscope(pta *,int *) noex ;
extern int	pta_setinheritsched(pta *,int) noex ;
extern int	pta_getinheritsched(pta *,int *) noex ;
extern int	pta_setschedpolicy(pta *,int) noex ;
extern int	pta_getschedpolicy(pta *,int *) noex ;
extern int	pta_setschedparam(pta *,const SCHEDPARAM *) noex ;
extern int	pta_getschedparam(pta *,SCHEDPARAM *) noex ;
extern int	pta_setstack(pta *,void *,size_t) noex ;

EXTERNC_end


#endif /* PTA_INCLUDE */


