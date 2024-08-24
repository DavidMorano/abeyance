/* uipc HEADER (UNIX® System V Inter-Process-Communication) */
/* lang=C20 */

/* translation layer interface for UNIX® equivalents */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	u_shmget
	u_shmat
	u_shmctl
	u_shmdt
	u_msgget
	u_msgsnd
	u_msgrcv
	u_msgctl

	Description:
	UNIX® System V Inter-Process-Communication (IPC)

*******************************************************************************/

#ifndef	UIPC_INCLUDE
#define	UIPC_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<sys/ipc.h>		/* UNIX® System V IPC */
#include	<sys/shm.h>		/* UNIX® System V IPC - SHM */
#include	<sys/msg.h>		/* UNIX® System V IPC - MSG */
#include	<sys/sem.h>		/* UNIX® System V IPC - SEM */
#include	<unistd.h>
#include	<limits.h>		/* |INT_MAX| */
#include	<errno.h>
#include	<stddef.h>		/* |nullptr_t| */
#include	<stdint.h>		/* |intptr_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usupport.h>


#ifdef	__cplusplus

namespace uipc {
    struct uipcbase ;
    typedef int (uipcbase::*uipcbase_m)(int,void *) noex ;
    struct uipcbase {
	uipcbase_m	m = nullptr ;
	key_t		key ;
	uipcbase() noex : key(0) { } ;
	int operator () (int,void *) noex ;
    } ; /* end struct (uipcbase) */
}

#endif /* __cplusplus */

EXTERNC_begin

extern int u_shmget(key_t,size_t,int) noex ;
extern int u_shmat(int,void *,int,void **) noex ;
extern int u_shmctl(int,int,SHMIDDS *) noex ;
extern int u_shmdt(void *) noex ;

extern int u_msgget(key_t,int) noex ;
extern int u_msgsnd(int,void *,int,int) noex ;
extern int u_msgrcv(int,void *,int,long,int) noex ;
extern int u_msgctl(int,int,MSQIDDS *) noex ;

extern int u_semget(key_t,int,int) noex ;
extern int u_semop(int,SEMBUF *,size_t) noex ;
extern int u_semctl(int,int,int,...) noex ;

EXTERNC_end


#endif /* UIPC_INCLUDE */


