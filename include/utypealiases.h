/* utypealiases HEADER */
/* lang=C20 */

/* virtual-system definitions */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

#ifndef	UTYPEALIASES_INCLUDE
#define	UTYPEALIASES_INCLUDE


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
#include	<sys/shm.h>		/* UNIX® Sys-V IPC - Shared-Memory */
#include	<sys/msg.h>		/* UNIX® Sys-V IPC - Message-Queues */
#include	<sys/sem.h>		/* UNIX® Sys-V IPC - Semaphores */

#if	defined(SYSHAS_ACL) && (SYSHAS_ACL > 0)
#include	<sys/acl.h>
#endif

#include	<ucontext.h>
#include	<signal.h>
#include	<limits.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<utime.h>		/* for |u_utime(2)| */
#include	<pthread.h>
#include	<termios.h>
#include	<time.h>
#include	<errno.h>
#include	<dirent.h>
#include	<netdb.h>
#include	<pwd.h>
#include	<grp.h>

#include	<stdintx.h>
#include	<clanguage.h>
#include	<usysdefs.h>


/* UNIX kernal structures */

#ifndef	UTSNAME
#define	UTSNAME		struct utsname
#endif

#ifndef	RLIMIT
#define	RLIMIT		struct rlimit
#endif

#ifndef	RUSAGE
#define	RUSAGE		struct rusage
#endif

#ifndef	SIGACTION
#define	SIGACTION	struct sigaction
#endif

#ifndef	SIGEVENT
#define	SIGEVENT	struct sigevent
#endif

#ifndef	SIGVAL
#define	SIGVAL		union sigval	
#endif

#ifndef	USTAT
#define	USTAT		struct ustat
#endif

#ifndef	STATFS
#define	STATFS		struct statfs
#endif

#ifndef	STATVFS
#define	STATVFS		struct statvfs
#endif

#ifndef	DIRENT
#define	DIRENT		struct dirent
#endif

#ifndef	FLOCK
#define	FLOCK		struct flock
#endif

#ifndef	AIOCB
#define	AIOCB		struct aiocb
#endif

#ifndef	IOVEC
#define	IOVEC		struct iovec
#endif

#ifndef	LINGER
#define	LINGER		struct linger
#endif

#ifndef	SOCKADDR
#define	SOCKADDR	struct sockaddr
#endif

#ifndef	SOCKADDR_UN
#define	SOCKADDR_UN	struct sockaddr_un
#endif

#ifndef	SOCKADDR_IN4
#define	SOCKADDR_IN4	struct sockaddr_in
#endif

#ifndef	SOCKADDR_IN6
#define	SOCKADDR_IN6	struct sockaddr_in6
#endif

#ifndef	MSGHDR
#define	MSGHDR		struct msghdr
#endif

/* not constant - "Control-Message-Header" */
#ifndef	CONMSGHDR
#define	CONMSGHDR	struct cmsghdr
#endif

#ifndef	SFHDTR
#define	SFHDTR		struct sf_hdtr
#endif

#ifndef	TIMEVAL
#define	TIMEVAL		struct timeval
#endif

#ifndef	ITIMERVAL
#define	ITIMERVAL	struct itimerval
#endif

#ifndef	TIMESPEC
#define	TIMESPEC	struct timespec
#endif

#ifndef	ITIMERSPEC
#define	ITIMERSPEC	struct itimerspec
#endif

#ifndef	UTIMBUF
#define	UTIMBUF		struct utimbuf
#endif

#ifndef	TIMEB
#define	TIMEB		struct timeb
#endif

#ifndef	TM
#define	TM		struct tm
#endif

#ifndef	TMS
#define	TMS		struct tms
#endif

#ifndef	TERMIOS
#define	TERMIOS		struct termios
#endif

#ifndef	WINSIZE
#define	WINSIZE		struct winsize
#endif

/* UNIX® System V STREAMS® */

#ifndef	POLLFD
#define	POLLFD		struct pollfd		/* UNIX® Sys-V (STREAMS) */
#endif

#ifndef	STRBUF
#define	STRBUF		struct strbuf		/* UNIX® Sys-V STREAMS */
#endif

#ifndef	STRPEEK
#define	STRPEEK		struct strpeek		/* UNIX® Sys-V STREAMS */
#endif

#ifndef	STRRECVFD
#define	STRRECVFD	struct strrecvfd	/* UNIX® Sys-V STREAMS */
#endif

#ifndef	STRIOCTL
#define	STRIOCTL	struct strioctl		/* UNIX® Sys-V STREAMS */
#endif

/* UNIX® System V Inter-Process-Communication (IPC) */

#ifndef	SHMIDDS
#define	SHMIDDS		struct shmid_ds		/* for UNIX® SysV-IPC SHM */
#endif

#ifndef	MSQIDDS
#define	MSQIDDS		struct msqid_ds		/* for UNIX® SysV-IPC MQ */
#endif

#ifndef	MQATTR
#define	MQATTR		struct mq_attr		/* for UNIX® SysV-IPC MQ */
#endif

#ifndef	MSQPERM		/* this is an ALIAS of |MSGPERM| */
#define	MSQPERM		struct msg_perm		/* for UNIX® SysV-IPC MQ */
#endif

#ifndef	MSGPERM
#define	MSGPERM		struct msg_perm		/* for UNIX® SysV-IPC MQ */
#endif

#ifndef	SEMIDDS
#define	SEMIDDS		struct semid_ds		/* for UNIX® SysV-IPC SEM */
#endif

#ifndef	SEMBUF
#define	SEMBUF		struct sembuf		/* for UNIX® SysV-IPC SEM */
#endif

#ifndef	SEMUN
#define	SEMUN		union semun		/* for UNIX® SysV-IPC SEM */
#endif

/* Internet */

#ifndef	INADDR
#define	INADDR		struct in_addr
#endif

#ifndef	INADDR4
#define	INADDR4		struct in_addr
#endif

#ifndef	INADDR6
#define	INADDR6		struct in6_addr
#endif

#ifndef	INADDRX
#define	INADDRX		struct in4in6_addr
#endif

/* UTMPX */

#ifndef	UTMPX
#define	UTMPX		struct utmpx
#endif

/* scheduler paramters */

#ifndef	SCHEDPARAM
#define	SCHEDPARAM	struct sched_param
#endif

/* constant versions of above */

#ifndef	CSIGVAL
#define	CSIGVAL		const SIGVAL
#endif

#ifndef	CUSTAT
#define	CUSTAT		const USTAT
#endif

#ifndef	CTIMEVAL
#define	CTIMEVAL	const TIMEVAL
#endif

#ifndef	CITIMERVAL
#define	CITIMERVAL	const ITIMERVAL
#endif

#ifndef	CTIMESPEC
#define	CTIMESPEC	const TIMESPEC
#endif

#ifndef	CITIMERSPEC
#define	CITIMERSPEC	const ITIMERSPEC
#endif

#ifndef	CUTIMBUF
#define	CUTIMBUF	const UTIMBUF
#endif

#ifndef	CTIMEB
#define	CTIMEB		const TIMEB
#endif

#ifndef	CTM
#define	CTM		const TM
#endif

#ifndef	CTMS
#define	CTMS		const TMS
#endif

#ifndef	CTERMIOS
#define	CTERMIOS	const TERMIOS
#endif

#ifndef	CAIOCB
#define	CAIOCB		const AIOCB
#endif

#ifndef	CIOVEC
#define	CIOVEC		const IOVEC
#endif

#ifndef	CLINGER
#define	CLINGER		const LINGER
#endif

#ifndef	CSOCKADDR
#define	CSOCKADDR	const SOCKADDR
#endif

#ifndef	CMSGHDR
#define	CMSGHDR		const MSGHDR
#endif

#ifndef	CSFHDTR
#define	CSFHDTR		const SFHDTR
#endif

#ifndef	CRLIMIT
#define	CRLIMIT		const RLIMIT
#endif

#ifndef	CUTMPX
#define	CUTMPX		const UTMPX
#endif

#ifndef	CSCHEDPARAM
#define	CSCHEDPARAM	const SCHEDPARAM
#endif


/* SYSDB account management structures */

#ifndef	PASSWD
#define	PASSWD		struct passwd
#endif

#ifndef	SPWD
#define	SPWD		struct spwd
#endif

#ifndef	GROUP
#define	GROUP		struct group
#endif

#ifndef	PROJECT
#define	PROJECT		struct project
#endif

#ifndef	USERATTR
#define	USERATTR	userattr
#endif

/* SYSDB network related structures */

#ifndef	PROTOENT
#define	PROTOENT	struct protoent
#endif

#ifndef	NETENT
#define	NETENT		struct netent
#endif

#ifndef	HOSTENT
#define	HOSTENT		struct hostent
#endif

#ifndef	SERVENT
#define	SERVENT		struct servent
#endif

#ifndef	ADDRINFO
#define	ADDRINFO	struct addrinfo
#endif

/* constant versions of above */

#ifndef	CPASSWD
#define	CPASSWD		const PASSWD
#endif

#ifndef	CSPWD
#define	CSPWD		const SPWD
#endif

#ifndef	CGROUP
#define	CGROUP		const GROUP
#endif

#ifndef	CPROJECT
#define	CPROJECT	const PROJECT
#endif

#ifndef	CUSERATTR
#define	CUSERATTR	const USERATTR
#endif

#ifndef	CPROTOENT
#define	CPROTOENT	const struct protoent
#endif

#ifndef	CNETENT
#define	CNETENT		const struct netent
#endif

#ifndef	CHOSTENT
#define	CHOSTENT	const struct hostent
#endif

#ifndef	CSERVENT
#define	CSERVENT	const struct servent
#endif

#ifndef	CADDRINFO
#define	CADDRINFO	const struct addrinfo
#endif

/* UNIX® System V Inter-Process-Communication (IPC) */

#ifndef	CSHMIDDS
#define	CSHMIDDS	const struct shmid_ds	/* for UNIX® SysV-IPC SHM */
#endif

#ifndef	CMSQIDDS
#define	CMSQIDDS	const struct msqid_ds	/* for UNIX® SysV-IPC MQ */
#endif

#ifndef	CMQATTR
#define	CMQATTR		const struct mq_attr	/* for UNIX® SysV-IPC MQ */
#endif

#ifndef	CMSQPERM		/* this is an ALIAS of |MSGPERM| */
#define	CMSQPERM	const struct msg_perm	/* for UNIX® SysV-IPC MQ */
#endif

#ifndef	CMSGPERM
#define	CMSGPERM	const struct msg_perm	/* for UNIX® SysV-IPC MQ */
#endif

#ifndef	CSEMIDDS
#define	CSEMIDDS	const struct semid_ds	/* for UNIX® SysV-IPC SEM */
#endif

#ifndef	CSEMBUF
#define	CSEMBUF		const struct sembuf	/* for UNIX® SysV-IPC SEM */
#endif

#ifndef	CSEMUN
#define	CSEMUN		const union semun	/* for UNIX® SysV-IPC SEM */
#endif


#endif /* UTYPEALIASES_INCLUDE */


