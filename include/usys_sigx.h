/* usys_sigx HEADER */
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

#ifndef	USYSSIGX_INCLUDE
#define	USYSSIGX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

/* SIGQUEUE begin */
#if	(!defined(SYSHAS_SIGQUEUE)) || (SYSHAS_SIGQUEUE == 0)


#ifndef	SUBROUTINE_SIGQUEUE
#define	SUBROUTINE_SIGQUEUE
EXTERNC_begin

extern unixret_t sigqueue(pid_t,int,const SIGVAL) noex ;

EXTERNC_end
#endif /* SUBROUTINE_SIGUEUE */

#endif /* (!defined(SYSHAS_SIGQUEUE)) || (SYSHAS_SIGQUEUE == 0) */
/* SIGQUEUE end */

/* SIGSEND begin */
#if	(!defined(SYSHAS_SIGSEND)) || (SYSHAS_SIGSEND == 0)

#ifndef	SUBROUTINE_SIGSEND
#define	SUBROUTINE_SIGSEND
EXTERNC_begin

extern unixret_t sigsend(idtype_t,id_t,int) noex ;

EXTERNC_end
#endif /* SUBROUTINE_SIGSEND */

#endif /* (!defined(SYSHAS_SIGSEND)) || (SYSHAS_SIGSEND == 0) */
/* SIGSEND end */

/* SIGSENDSET begin */
#if	(!defined(SYSHAS_SIGSENDSET)) || (SYSHAS_SIGSENDSET == 0)

#ifndef	TYPEDEF_IDOP
#define	TYPEDEF_IDOP
typedef int		idop_t ;
#endif

#ifndef	STRUCT_PROCSET
#define	STRUCT_PROCSET
struct procset {
	idop_t		p_op ;
	idtype_t	p_lidtype ;
	id_t		p_lid ;
	idtype_t	p_ridtype ;
	id_t		p_rid ;
} ;
#endif /* STRUCT_PROCSET */

#ifndef	TYPEDEF_PROCSET
#define	TYPEDEF_PROCSET
typedef struct procset		procset_t ;
#endif

#ifndef	SUBROUTINE_SIGSENDSET
#define	SUBROUTINE_SIGSENDSET
EXTERNC_begin
extern unixret_t sigsendset(procset_t *,int) noex ;
EXTERNC_end
#endif /* SUBROUTINE_SIGSENDSET */

#endif /* (!defined(SYSHAS_SIGSENDSET)) || (SYSHAS_SIGSENDSET == 0) */
/* SIGSENDSET end */

/* PTHREADSIGQUEUE begin */
#if	(!defined(SYSHAS_PTHREADSIGQUEUE)) || (SYSHAS_PTHREADSIGQUEUE == 0)

#ifndef	SUBROUTINE_PTHREADSIGQUEUE
#define	SUBROUTINE_PTHREADSIGQUEUE
EXTERNC_begin
extern errno_t pthread_sigqueue(pthread_t,int,const SIGVAL) noex ;
EXTERNC_end
#endif /* SUBROUTINE_PTHREADSIGQUEUE */

#endif /* (!defined(SYSHAS_PTHREADSIGQUEUE)) || (SYSHAS_PTHREADSIGQUEUE == 0) */
/* PTHREADSIGQUEUE end */


#endif /* USYSSIGX_INCLUDE */


