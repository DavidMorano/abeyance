/* usys_mqueue HEADER */
/* lang=C20 */

/* miscelllaneous (XXX) operating system support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX® system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the Apple Darwin operating system.

*******************************************************************************/

#ifndef	USYS_MQUEUE_INCLUDE
#define	USYS_MQUEUE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* <- |mode_t| */
#include	<sys/wait.h>		/* <- type |idtype_t| is there */
#include	<sys/time.h>		/* <- |TIMESPEC| is there */
#include	<signal.h>		/* <- |SIGEVENT| */
#include	<pthread.h>
#include	<time.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#ifndef	MQATTR
#define	MQATTR		struct mq_attr
#endif /* MQ_ATTR */


/* PMQ begin */
#if	(!defined(SYSHAS_PMQ)) || (SYSHAS_PMQ == 0)

#ifndef	STRUCT_MQATTR
#define	STRUCT_MQATTR
struct mq_attr {
	uint	dummy ;
} ;
#endif /* STRUCT_MQATTR */

#ifndef	TYPEDEF_MQDT
#define	TYPEDEF_MQDT
typedef uintptr_t	mqd_t ;
#endif /* TYPEDEF_MQDT */

#ifndef	SUBROUTINE_PMQ
#define	SUBROUTINE_PMQ
EXTERNC_begin
extern mqd_t mq_open(cchar *,int,mode_t,const MQATTR *) noex ;
extern unixret_t mq_close(mqd_t) noex ;
extern unixret_t mq_send(mqd_t,cchar *,int,int) noex ;
extern unixret_t mq_receive(mqd_t,char *,int,uint *) noex ;
extern unixret_t mq_setattr(mqd_t,const MQATTR *,MQATTR *) noex ;
extern unixret_t mq_getattr(mqd_t,MQATTR *) noex ;
extern unixret_t mq_notify(mqd_t,SIGEVENT *) noex ;
extern unixret_t mq_unlink(cchar *) noex ;
EXTERNC_end
#endif /* SUBROUTINE_PMQ */

#else /* (!defined(SYSHAS_PMQ)) || (SYSHAS_PMQ == 0) */

#include	<mqueue.h>

#endif /* (!defined(SYSHAS_PMQ)) || (SYSHAS_PMQ == 0) */
/* PMQ end */


#endif /* USYS_MQUEUE_INCLUDE */


