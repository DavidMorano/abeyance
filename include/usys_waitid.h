/* usys_waitid HEADER */
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

#ifndef	USYSWAITID_INCLUDE
#define	USYSWAITID_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/wait.h>

/* WAITID begin */
#if	(!defined(SYSHAS_WAITID)) || (SYSHAS_WAITID == 0)


#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#ifndef	TYPEDEF_WAITID
#define	TYPEDEF_WAITID

typedef enum idtype {          /* pollutes XPG4.2 namespace */
        P_PID,          /* A process identifier.                */
        P_PPID,         /* A parent process identifier.         */
        P_PGID,         /* A process group (job control group) ID */
        P_SID,          /* A session identifier.                */
        P_CID,          /* A scheduling class identifier.       */
        P_UID,          /* A user identifier.                   */
        P_GID,          /* A group identifier.                  */
        P_ALL,          /* All processes.                       */
        P_LWPID,        /* An LWP identifier.                   */
        P_TASKID,       /* A task identifier.                   */
        P_PROJID,       /* A project identifier.                */
        P_POOLID,       /* A pool identifier.                   */
        P_ZONEID,       /* A zone identifier.                   */
        P_CTID,         /* A (process) contract identifier.     */
        P_CPUID,        /* CPU identifier.                      */
        P_PSETID        /* Processor set identifier             */
} idtype_t ;

#endif /* TYPEDEF_WAITID */


#ifndef	SUBROUTINE_WAITID
#define	SUBROUTINE_WAITID
EXTERNC_begin

extern unixret_t waitid(idtype_t,id_t,siginfo_t *,int) noex ;

EXTERNC_end
#endif /* SUBROUTINE_WAITID */


#endif /* (!defined(SYSHAS_WAITID)) || (SYSHAS_WAITID == 0) */
/* WAITID end */


#endif /* USYSWAITID_INCLUDE */


