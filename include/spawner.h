/* spawner HEADER */
/* lang=C20 */

/* object to facilitate spanwing processes */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-10, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SPAWNER_INCLUDE
#define	SPAWNER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<vecobj.h>
#include	<envhelp.h>


#define	SPAWNER		struct spawner_head

#define	SPAWNER_OIGNINTR	(1<<0)		/* ignore interrupts */
#define	SPAWNER_OSETSID		(1<<1)		/* set-session-id */
#define	SPAWNER_OSETPGRP	(1<<2)		/* set-process-group */
#define	SPAWNER_OSIGDEFS	(1<<3)		/* set default signals */


/* notes on this structure */

/****

This structure is part of the user interface for this facility. The 'disp'
components should be set by the caller to specify the desired disposition for
each of the three FDs of the child program ('0', '1', and '2'). The 'fd'
component serves as an input to the subroutine when the corresponding
disposition is DUP. The 'fd' component is an output from the subroutine when the
corresponding disposition is OPEN.

****/

struct spawner_head {
	mainv		argv ;
	cchar		*execfname ;
	vecobj		cmds ;
	envhelp		env ;
	pid_t		pid ;
	pid_t		pgrp ;
	int		opts ;
} ;

typedef SPAWNER		spawner ;

EXTERNC_begin

extern int spawner_start(spawner *,cchar *,mainv,mainv) noex ;
extern int spawner_setsid(spawner *) noex ;
extern int spawner_setpgrp(spawner *,pid_t) noex ;
extern int spawner_setctty(spawner *,int,pid_t) noex ;
extern int spawner_seteuid(spawner *,uid_t) noex ;
extern int spawner_setegid(spawner *,gid_t) noex ;
extern int spawner_sigignores(spawner *) noex ;
extern int spawner_sigignore(spawner *,int) noex ;
extern int spawner_sigdefault(spawner *,int) noex ;
extern int spawner_sighold(spawner *,int) noex ;
extern int spawner_sigrelease(spawner *,int) noex ;
extern int spawner_fdclose(spawner *,int) noex ;
extern int spawner_fdnull(spawner *,int) noex ;
extern int spawner_fddup(spawner *,int) noex ;
extern int spawner_fddup2(spawner *,int,int) noex ;
extern int spawner_fddupto(spawner *,int,int) noex ;
extern int spawner_envset(spawner *,cchar *,cchar *,int) noex ;
extern int spawner_run(spawner *) noex ;
extern int spawner_wait(spawner *,int *,int) noex ;
extern int spawner_finish(spawner *) noex ;

EXTERNC_end


#endif /* SPAWNER_INCLUDE */


