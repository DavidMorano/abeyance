/* usig HEADER */
/* lang=C20 */

/* UNIX® process signal mangement */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This module provides UNIX® process signal mangement.

*******************************************************************************/

#ifndef	USIG_INCLUDE
#define	USIG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<signal.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int u_kill(pid_t,int) noex ;
extern int u_killpg(pid_t,int) noex ;
extern int u_sigaction(int,SIGACTION *,SIGACTION *) noex ;
extern int u_sigaltstack(const stack_t *,stack_t *) noex ;
extern int u_sigpending(sigset_t *) noex ;
extern int u_sigprocmask(int,sigset_t *,sigset_t *) noex ;
extern int u_sigsuspend(const sigset_t *) noex ;
extern int u_sigsend(idtype_t,id_t,int) noex ;
extern int u_sigsendset(procset_t *,int) noex ;
extern int u_sigwait(const sigset_t *,int *) noex ;
extern int u_sigmask(int,sigset_t *,sigset_t *) noex ;

EXTERNC_end


#endif /* USIG_INCLUDE */


