/* uclibsubs HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* UNIX® C-language library (standard) subroutines */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

#ifndef	UCLIBSUBS_INCLUDE
#define	UCLIBSUBS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<sys/utsname.h>
#include	<sys/uio.h>
#include	<sys/time.h>		/* for 'u_adjtime(3u)' */
#include	<sys/timeb.h>		/* for 'uc_ftime(3uc)' */
#include	<sys/resource.h>
#include	<sys/stat.h>
#include	<sys/statvfs.h>
#include	<sys/socket.h>
#include	<sys/poll.h>
#include	<ucontext.h>

#if	defined(SYSHAS_ACL) && (SYSHAS_ACL > 0)
#include	<sys/acl.h>
#endif

#include	<signal.h>
#include	<limits.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<utime.h>		/* for 'u_utime(2)' */
#include	<pthread.h>
#include	<termios.h>
#include	<time.h>
#include	<errno.h>
#include	<dirent.h>
#include	<netdb.h>
#include	<pwd.h>
#include	<grp.h>
#include	<secdb.h>

#if	defined(SYSHAS_XTI) && (SYSHAS_XTI > 0)
#include	<xti.h>
#endif

#include	<usys.h>	/* <- auxilllary OS support */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>

#include	<ucsys.h>
#include	<ucent.h>
#include	<ucget.h>
#include	<ucuserattr.h>
#include	<uclibmemalloc.h>
#include	<ucmemalloc.h>
#include	<ucmallocx.h>
#include	<ucstrtox.h>
#include	<ucopen.h>
#include	<uctc.h>		/* terminal interface */
#include	<ucpts.h>		/* pseudo-terminal management */
#include	<ucfdmanip.h>
#include	<uctimer.h>
#include	<ucgetpid.h>
#include	<ucrand.h>
#include	<ucgetrandom.h>
#include	<ucsysauxinfo.h>
#include	<uctimer.h>
#include	<ucinetconv.h>
#include	<ucsysconf.h>

#include	<getexecname.h>
#include	<termios_cf.h>


EXTERNC_begin

/* system group */
extern int	uc_gethostid(ulong *) noex ;
extern int	uc_gethostname(char *,int) noex ;
extern int	uc_getarchitecture(char *,int) noex ;
extern int	uc_getnisdomain(char *,int) noex ;
extern int	uc_getloadavg(double *,int) noex ;
extern int	uc_nprocessors(int) noex ;
extern int	uc_syspages(int) noex ;
extern int	uc_nprocs(int) noex ;

/* time group */
extern int	uc_gettimeofday(TIMEVAL *,void *) noex ;
extern int	uc_ftime(TIMEB *) noex ;
extern int	uc_clockset(clockid_t,const TIMESPEC *) noex ;
extern int	uc_clockget(clockid_t,TIMESPEC *) noex ;
extern int	uc_clockres(clockid_t,TIMESPEC *) noex ;

extern int	uc_fork() noex ;
extern int	uc_forklockbegin(int) noex ;
extern int	uc_forklockend() noex ;
extern int	uc_execve(cchar *,mainv,mainv) noex ;
extern int	uc_isaexecve(cchar *,mainv,mainv) noex ;
extern int	uc_initgroups(cchar *,gid_t) noex ;
extern int	uc_exit(int) noex ;
extern int	uc_atexit(void_f) noex ;
extern int	uc_atforkrecord(void_f,void_f,void_f) noex ;
extern int	uc_atforkexpunge(void_f,void_f,void_f) noex ;
extern int	uc_atfork(void_f,void_f,void_f) noex ;

extern int	uc_getcwd(char *,int) noex ;
extern int	uc_swapcontext(ucontext_t *,const ucontext_t *) noex ;
extern int	uc_msync(caddr_t,size_t,int) noex ;
extern int	uc_getauid() noex ;
extern int	uc_getpriority(int,id_t,int *) noex ;
extern int	uc_setpriority(int,id_t,int) noex ;
extern int	uc_getpuid(pid_t) noex ;
extern int	uc_procpid(cchar *,uid_t) noex ;

/* double-special open group */
extern int	uc_pipe(int *) noex ;
extern int	uc_pipes(int *,int) noex ;
extern int	uc_piper(int *,int,int) noex ;
extern int	uc_sockpair(int,int,int,int *) noex ;

/* operate group */
extern int	uc_mknod(cchar *,mode_t,dev_t) noex ;
extern int	uc_statvfs(cchar *,STATVFS *) noex ;
extern int	uc_stat(cchar *,USTAT *) noex ;
extern int	uc_lstat(cchar *,USTAT *) noex ;
extern int	uc_readlink(cchar *,char *,int) noex ;
extern int	uc_chmod(cchar *,mode_t) noex ;
extern int	uc_chown(cchar *,uid_t,gid_t) noex ;
extern int	uc_rename(cchar *,cchar *) noex ;
extern int	uc_utime(cchar *,const UTIMBUF *) noex ;
extern int	uc_realpath(cchar *,char *) noex ;
extern int	uc_truncate(cchar *,off_t) noex ;

/* use group */
extern int	uc_fcntl(int,int,...) noex ;
extern int	uc_ioctl(int,int,...) noex ;
extern int	uc_tell(int,off_t *) noex ;
extern int	uc_fpassfd(int,int) noex ;
extern int	uc_ftruncate(int,off_t) noex ;
extern int	uc_fstat(int,USTAT *) noex ;
extern int	uc_fchown(int,uid_t,gid_t) noex ;
extern int	uc_isatty(int) noex ;
extern int	uc_fsync(int) noex ;
extern int	uc_fdatasync(int) noex ;
extern int	uc_fattach(int,cchar *) noex ;
extern int	uc_fdetach(cchar *) noex ;
extern int	uc_minmod(cchar *,mode_t) noex ;
extern int	uc_fminmod(int,mode_t) noex ;
extern int	uc_fsize(int) noex ;
extern int	uc_fuid(int) noex ;
extern int	uc_fgid(int) noex ;
extern int	uc_rewind(int) noex ;
extern int	uc_lockf(int,int,off_t) noex ;
extern int	uc_lockfile(int,int,off_t,off_t,int) noex ;

extern int	uc_bind(int,void *,int) noex ;
extern int	uc_joinus(int,SOCKADDR *,int,int,mode_t) noex ;
extern int	uc_accepte(int,SOCKADDR *,int *,int) noex ;
extern int	uc_connect(int,cvoid *,int) noex ;
extern int	uc_connecte(int,cvoid *,int,int) noex ;
extern int	uc_setsockopt(int,int,int,int *,int) noex ;
extern int	uc_linger(int,int) noex ;

extern int	uc_copy(int,int,int) noex ;

extern int	uc_read(int,void *,int) noex ;
extern int	uc_readn(int,void *,int) noex ;
extern int	uc_readline(int,char *,int) noex ;
extern int	uc_readlinetimed(int,char *,int,int) noex ;

extern int	uc_writeto(int,cvoid *,int,int) noex ;
extern int	uc_write(int,cvoid *,int) noex ;
extern int	uc_writen(int,cvoid *,int) noex ;
extern int	uc_writedesc(int,int,int) noex ;
extern int	uc_writefile(int,cchar *) noex ;

extern int	uc_reade(int,void *,int,int,int) noex ;
extern int	uc_recve(int,void *,int,int,int,int) noex ;
extern int	uc_recvfrome(int,void *,int,int,void *,int *,int,int) noex ;
extern int	uc_recvmsge(int,MSGHDR *,int,int,int) noex ;
extern int	uc_sockatmark(int) noex ;
extern int	uc_peek(int,void *,int) noex ;
extern int	uc_getsocktype(int) noex ;

extern int	uc_tcattrset(int,int,const TERMIOS *) noex ;
extern int	uc_tcattrget(int,TERMIOS *) noex ;
extern int	uc_tcgetsid(int) noex ;
extern int	uc_tcsetpgrp(int,pid_t) noex ;
extern int	uc_tcgetpgrp(int) noex ;
extern int	uc_keepalive(int,int) noex ;
extern int	uc_reuseaddr(int) noex ;
extern int	uc_moveup(int,int) noex ;
extern int	uc_ndelay(int,int) noex ;
extern int	uc_nonblock(int,int) noex ;
extern int	uc_msgdiscard(int) noex ;
extern int	uc_setappend(int,int) noex ;
extern int	uc_closeonexec(int,int) noex ;
extern int	uc_close(int) noex ;
extern int	uc_locktail(int,int,int,int) noex ;

extern int	uc_remove(cchar *) noex ;
extern int	uc_link(cchar *,cchar *) noex ;
extern int	uc_symlink(cchar *,cchar *) noex ;
extern int	uc_unlink(cchar *) noex ;
extern int	uc_mkdir(cchar *,mode_t) noex ;
extern int	uc_rmdir(cchar *) noex ;
extern int	uc_access(cchar *,int) noex ;
extern int	uc_pathconf(cchar *,int,long *) noex ;

/* process-signal group */
extern int	uc_raise(int) noex ;
extern int	uc_sigdefault(int) noex ;
extern int	uc_sigignore(int) noex ;
extern int	uc_sighold(int) noex ;
extern int	uc_sigrelease(int) noex ;
extern int	uc_sigpause(int) noex ;
extern int	uc_sigsetempty(sigset_t *) noex ;
extern int	uc_sigsetfill(sigset_t *) noex ;
extern int	uc_sigsetadd(sigset_t *,int) noex ;
extern int	uc_sigsetdel(sigset_t *,int) noex ;
extern int	uc_sigsetismem(sigset_t *,int) noex ;

/* special */
extern int	uc_sigqueue(pid_t,int,const SIGVAL) noex ;
extern int	uc_sigwaitinfo(const sigset_t *,siginfo_t *) noex ;
extern int	uc_sigtimedwait(const sigset_t *,siginfo_t *,
			const TIMESPEC *) noex ;
extern int	uc_sigwaitinfoto(const sigset_t *,siginfo_t *,
			const TIMESPEC *) noex ;
/* special */

extern int	uc_safesleep(int) noex ;
extern int	uc_mktime(TM *,time_t *) noex ;
extern int	uc_gmtime(const time_t *,TM *) noex ;
extern int	uc_localtime(const time_t *,TM *) noex ;
extern int	uc_ttyname(int,char *,int) noex ;
extern int	uc_mkfifo(cchar *,mode_t) noex ;

/* memory allocation (user-space) */

#ifdef	COMMENT
extern int	uc_malloc(int,void *) noex ;
extern int	uc_calloc(int,int,void *) noex ;
extern int	uc_valloc(int,void *) noex ;
extern int	uc_realloc(cvoid *,int,void *) noex ;
extern int	uc_free(cvoid *) noex ;
extern int	uc_mallset(int) noex ;
extern int	uc_mallout(ulong *) noex ;
extern int	uc_mallinfo(unsigned int *,int) noex ;
extern int	uc_mallpresent(cvoid *) noex ;
extern int	uc_mallocstrw(cchar *,int,cchar **) noex ;
extern int	uc_mallocsys(int,char **) noex ;
extern int	uc_mallocbuf(cvoid *,int,cvoid **) noex ;
#endif /* COMMENT */

/* project related */
extern int	uc_inproj(cchar *,cchar *,char *,int) noex ;

/* POSIX shared memory operations */
extern int	uc_openshm(cchar *,int,mode_t) noex ;
extern int	uc_openshmto(cchar *,int,mode_t,int) noex ;
extern int	uc_unlinkshm(cchar *) noex ;

/* miscellaneous */
extern int	uc_strtod(cchar *,char **,double *) noex ;
extern int	uc_getnetname(char *) noex ;

/* NETWORK IPNODE database */
extern int	uc_getipnodebyname(HOSTENT **,cchar *,int,int) noex ;
extern int	uc_freehostent(HOSTENT *) noex ;

/* NETWORK ADDRINFO database */
extern int uc_addrinfoget(cchar *,cchar *,const ADDRINFO *,ADDRINFO **) noex ;
extern int uc_addrinfofree(ADDRINFO *) noex ;

/* NETWORK SOCKADDR combined database */
extern int	uc_getnameinfo(const SOCKADDR *,int,
			char *,int,char *,int,int) noex ;

/* why was this missing? */
extern int	uc_getlogin(char *,int) noex ;

/* miscellaneous */
extern int	uc_ztime(TM *,const time_t *,int) noex ;
extern int	uc_kvamatch(kva_t *,cchar *,cchar **) noex ;

EXTERNC_end


#endif /* UCLIBSUBS_INCLUDE */


