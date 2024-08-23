/* pmq HEADER */
/* lang=C20 */

/* Posix Message Queue (PMQ) */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-07-23, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PMQ_INCLUDE
#define	PMQ_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<usystem.h>


#define	PMQ		struct pmq_head
#define	PMQ_ATTR	struct mq_attr
#define	PMQ_MAGIC	0x31419876


struct pmq_head {
	mqd_t		pq ;
	char		*name ;		/* allocated */
	uint		magic ;
} ;

typedef PMQ		pmq ;
typedef PMQ_ATTR	pmq_attr ;

EXTERNC_begin

extern int	pmq_open(pmq *,cchar *,int,mode_t,const pmq_attr *) noex ;
extern int	pmq_close(pmq *) noex ;
extern int	pmq_send(pmq *,cvoid *,int,uint) noex ;
extern int	pmq_recv(pmq *,void *,int,uint *) noex ;
extern int	pmq_attrset(pmq *,const pmq_attr *,pmq_attr *) noex ;
extern int	pmq_attrget(pmq *,pmq_attr *) noex ;
extern int	pmq_notify(pmq *,SIGEVENT *) noex ;
extern int	pmq_unlink(pmq *) noex ;

extern int	uc_unlinkpmq(cchar *) noex ;

EXTERNC_end


#endif /* PMQ_INCLUDE */


