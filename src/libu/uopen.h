/* ufdlock HEADER */
/* charset=ISO8859-1 */
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
	u_dupover
	u_dup2
	u_fcntl
	u_close
	u_socketpair
	u_pipe
	u_pipe2
	u_piper

	Description:
	This module provides support for opening files or devices.

*******************************************************************************/

#ifndef	UFDLOCK_INCLUDE
#define	UFDLOCK_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int u_open(cchar *,int,mode_t) noex ;
extern int u_creat(cchar *,mode_t) noex ;
extern int u_openat(int,cchar *,int,mode_t) noex ;
extern int u_socket(int,int,int) noex ;
extern int u_accept(int,SOCKADDR *,int *) noex ;
extern int u_acceptpass(int,STRRECVFD *,int) noex ;
extern int u_dup(int) noex ;
extern int u_dupmin(int,int) noex ;
extern int u_dupminer(int,int,int) noex ;
extern int u_dupover(int,int) noex ;
extern int u_fcntl(int,int,...) noex ;
extern int u_close(int) noex ;
/* special */
extern int u_socketpair(int,int,int,int *) noex ;
extern int u_pipe(int *) noex ;
extern int u_pipe2(int *,int) noex ;
extern int u_piper(int *,int,int) noex ;

static inline int u_pipes(int *pipes,int of) noex {
	return u_pipe2(pipes,of) ;
}

extern int ufdlock_init() noex ;
extern int ufdlock_fini() noex ;

EXTERNC_end

#ifdef	__cplusplus

namespace libu {
    extern sysret_t ufdlock_lockbegin() noex ;
    extern sysret_t ufdlock_lockend() noex ;
}

namespace libu {
    extern int special_acceptpass(int,STRRECVFD *,int) noex ;
}

#endif /* __cplusplus */


#endif /* UFDLOCK_INCLUDE */


