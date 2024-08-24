/* uopen HEADER */
/* lang=C20 */

/* UNIX® support for opening files or devices */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	u_open
	u_openat
	u_socket
	u_accept
	u_acceptpass
	u_dup
	u_dupmin
	u_dupminee
	u_dup2
	u_socketpair
	u_pipe
	u_pipe2
	u_piper

	Description:
	This module provides support for opening files or devices.

*******************************************************************************/

#ifndef	UOPEN_INCLUDE
#define	UOPEN_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


/* extra system flags for 'openXXX(2)' and friends */
#ifndef	OF_SPECIALMASK
#define	OF_SPECIALMASK	0xF0000000
#endif

#ifndef	O_SETSID
#define	O_SETSID	(1<<24)
#endif
#ifndef	O_CLOEXEC
#define	O_CLOEXEC	(1<<25)
#endif
#ifndef	O_NETWORK
#define	O_NETWORK	(1<<26)
#endif
#ifndef	O_MINMODE
#define	O_MINMODE	(1<<27)
#endif

/* extra system flags for |uc_lockfile(3uc)| */
#ifndef	F_UNLOCK
#define	F_UNLOCK	F_ULOCK
#endif
#ifndef	F_WLOCK	
#define	F_WLOCK		F_LOCK
#endif
#ifndef	F_TWLOCK
#define	F_TWLOCK	F_TLOCK
#endif
#ifndef	F_WTEST
#define	F_WTEST		F_TEST
#endif
#ifndef	F_RLOCK
#define	F_RLOCK		10		/* new! (watch UNIX® for changes) */
#endif
#ifndef	F_TRLOCK
#define	F_TRLOCK	11		/* new! (watch UNIX® for changes) */
#endif
#ifndef	F_RTEST
#define	F_RTEST		12		/* new! (watch UNIX® for changes) */
#endif


EXTERNC_begin

extern int u_open(cchar *,int,mode_t) noex ;
extern int u_creat(cchar *,mode_t) noex ;
extern int u_openat(int,cchar *,int,mode_t) noex ;
extern int u_socket(int,int,int) noex ;
extern int u_accept(int,SOCKADDR *,int *) noex ;
extern int u_acceptpass(int) noex ;
extern int u_dup(int) noex ;
extern int u_dup2(int,int) noex ;
extern int u_dupmin(int,int) noex ;
extern int u_dupminer(int,int,int) noex ;
/* special */
extern int u_socketpair(int,int,int,int *) noex ;
extern int u_pipe(int *) noex ;
extern int u_pipe2(int *,int) noex ;
extern int u_piper(int *,int,int) noex ;

static inline int u_pipes(int *pipes,int of) noex {
	return u_pipe2(pipes,of) ;
}

EXTERNC_end

#ifdef	__cplusplus

namespace uopen {
   extern sysret_t uopen_lockbegin() noex ;
   extern sysret_t uopen_lockend() noex ;
}

#endif /* __cplusplus */


#endif /* UOPEN_INCLUDE */


