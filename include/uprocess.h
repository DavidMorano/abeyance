/* uprocess HEADER (UNIX® file operations) */
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
	u_alarm
	u_exit
	u_fork
	u_atfork
	u_getgroups
	u_getpgid
	u_getrlimit
	u_getsid
	u_nice
	u_setuid
	u_setreuid
	u_seteuid
	u_setgid
	u_setregid
	u_setegid
	u_setpgid
	u_setsid
	u_setgroups
	u_setrlimit
	u_times
	u_ulimit
	u_vfork
	u_wait
	u_waitid
	u_waitpid
	u_nanosleep

	Description:
	All of the UNIX® system calls that use (operate on) a
	UNIX® process.

*******************************************************************************/

#ifndef	UPROCESS_INCLUDE
#define	UPROCESS_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>		/* system types */
#include	<sys/resource.h>	/* |getrlimit(2)| */
#include	<unistd.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usupport.h>


#ifdef	__cplusplus

namespace uprocess {
    struct uprocessflags {
	uint		fintr:1 ;	/* request interrupts to return */
    } ; /* end struct (uprocessflags) */
    struct uprocessbase {
	uprocessflags	f{} ;
	uprocessbase() noex { } ;
	int operator () () noex ;
	virtual int callstd() noex = 0 ;
    } ; /* end struct (uprocessbase) */
}

#endif /* __cplusplus */

EXTERNC_begin

extern int u_alarm(cuint secs) noex ;
extern int u_atfork(void_f,void_f,void_f) noex ;
extern int u_exit(int ex) noex ;
extern int u_fork() noex ;
extern int u_getgroups(int n,gid_t *a) noex ;
extern int u_getpgid(pid_t pid) noex ;
extern int u_getrlimit(int rn,RLIMIT *rp) noex ;
extern int u_getsid(pid_t pid) noex ;
extern int u_kill(pid_t pid,int sig) noex ;
extern int u_nice(int,int *) noex ;
extern int u_pause() noex ;
extern int u_setuid(uid_t uid) noex ;
extern int u_setreuid(uid_t ruid,uid_t euid) noex ;
extern int u_seteuid(uid_t euid) noex ;
extern int u_setgid(gid_t gid) noex ;
extern int u_setregid(gid_t rgid,gid_t egid) noex ;
extern int u_setegid(gid_t egid) noex ;
extern int u_setpgid(pid_t pid,pid_t pgid) noex ;
extern int u_setsid() noex ;
extern int u_setgroups(int n,const gid_t *list) noex ;
extern int u_setrlimit(int rn,CRLIMIT *rp) noex ;
extern int u_times(TMS *rp) noex ;
extern int u_ulimit(int,...) noex ;
extern int u_vfork() noex ;
extern int u_wait(int *sp) noex ;
extern int u_waitid(idtype_t idtype,id_t id,siginfo_t *sip,int opts) noex ;
extern int u_waitpid(pid_t pid,int *sp,int flags) noex ;
extern int u_nanosleep(CTIMESPEC *,TIMESPEC *) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int u_nice(int incr) noex {
	return u_nice(incr,nullptr) ;
}

#endif /* __cplusplus */


#endif /* UPROCESS_INCLUDE */


