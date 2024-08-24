/* usysrets HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* UNIX system returns */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

#ifndef	USYSRETS_INCLUDE
#define	USYSRETS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<errno.h>


enum errnomssings {
	errnomissing_l2nsync = 1000,
	errnomissing_l2hlt,
	errnomissing_l3hlt,
	errnomissing_l3rst,
	errnomissing_noano,
	errnomissing_bad,
	errnomissing_badr,
	errnomissing_bade,
	errnomissing_badrqc,
	errnomissing_badslt,
	errnomissing_deadlock,
	errnomissing_bfont,
	errnomissing_ownerdead,
	errnomissing_unavailable,
	errnomissing_notrecoverable,
	errnomissing_notuniq,
	errnomissing_proto,
	errnomissing_badfd,
	errnomissing_libacc,
	errnomissing_libbad,
	errnomissing_libscn,
	errnomissing_libmax,
	errnomissing_libexec,
	errnomissing_hostdown,
	errnomissing_unatch,
	errnomissing_nosr,
	errnomissing_nopkg,
	errnomissing_noattr,
	errnomissing_nocsi,
	errnomissing_nonet,
	errnomissing_chrng,
	errnomissing_lnrng,
	errnomissing_srmnt,
	errnomissing_xfull,
	errnomissing_adv,
	errnomissing_comm,
	errnomissing_remchg,
	errnomissing_restart,
	errnomissing_strpipe,
	errnomissing_overlast
} ;

#ifndef	EL2NSYNC
#define	EL2NSYNC	errnomissing_l2nsync
#endif
#ifndef	EL3HLT
#define	EL3HLT		errnomissing_l3hlt
#endif
#ifndef	EL3RST
#define	EL3RST		errnomissing_l3rst
#endif
#ifndef	EL2HLT
#define	EL2HLT		errnomissing_l2hlt
#endif
#ifndef	ENOANO
#define	ENOANO		errnomissing_noano
#endif
#ifndef	EBAD
#define	EBAD		errnomissing_bad
#endif
#ifndef	EBADR
#define	EBADR		errnomissing_badr
#endif
#ifndef	EBADE
#define	EBADE		errnomissing_bade
#endif
#ifndef	EBADRQC
#define	EBADRQC		errnomissing_badrqc
#endif
#ifndef	EBADSLT
#define	EBADSLT		errnomissing_badslt
#endif
#ifndef	EDEADLOCK
#define	EDEADLOCK	errnomissing_deadlock
#endif
#ifndef	EBFONT
#define	EBFONT		errnomissing_bfont
#endif
#ifndef	EOWNERDEAD
#define	EOWNERDEAD	errnomising_ownerdead
#endif
#ifndef	ENOTRECOVERABLE
#define	ENOTRECOVERABLE	errnomissing_notrecoverable
#endif
#ifndef	ENOTUNIQ
#define	ENOTUNIQ	errnomissing_notuniq
#endif
#ifndef	EPROTO
#define	EPROTO		errnomissing_proto
#endif
#ifndef	EBADFD
#define	EBADFD		errnomissing_badfd
#endif
#ifndef	ELIBACC
#define	ELIBACC		errnomissing_libacc
#endif
#ifndef	ELIBBAD
#define	ELIBBAD		errnomissing_libbad
#endif
#ifndef	ELIBSCN
#define	ELIBSCN		errnomissing_libscn
#endif
#ifndef	ELIBMAX
#define	ELIBMAX		errnomissing_libmax
#endif
#ifndef	ELIBEXEC
#define	ELIBEXEC	errnomissing_libexec
#endif
#ifndef	EHOSTDOWN
#define	EHOSTDOWN	errnomissing_hostdown
#endif
#ifndef	EUNATCH
#define	EUNATCH		errnomissing_unatch
#endif
#ifndef	ENOSR
#define	ENOSR		errnomissing_nosr
#endif
#ifndef	ENOPKG
#define	ENOPKG		errnomissing_nopkg
#endif
#ifndef	ENOATTR
#define	ENOATTR		errnomissing_noattr
#endif

#ifndef	ENOCSI
#define	ENOCSI		errnomissing_nocsi
#endif
#ifndef	ENONET
#define	ENONET		errnomissing_nonet
#endif

#ifndef	ECHRNG
#define	ECHRNG		errnomissing_chrng
#endif
#ifndef	ELNRNG
#define	ELNRNG		errnomissing_lnrng
#endif
#ifndef	ESRMNT
#define	ESRMNT		errnomissing_srmnt
#endif
#ifndef	EXFULL
#define	EXFULL		errnomissing_xfull
#endif
#ifndef	EADV
#define	EADV		errnomissing_adv
#endif
#ifndef	ECOMM
#define	ECOMM		errnomissing_comm
#endif
#ifndef	EREMCHG
#define	EREMCHG		errnomissing_remchg
#endif
#ifndef	ERESTART
#define	ERESTART	errnomissing_restart
#endif
#ifndef	ESTRPIPE
#define	ESTRPIPE	errnomissing_strpipe
#endif

/* status return codes (only used when explicit return status is requested) */

#define	SR_TIMEOUT	2		/* timed out w/ possible data */
#define	SR_CREATED	1		/* created object */

/* operation returns */

#define	SR_OK		0		/* the OK return */

#define	SR_PERM		(- EPERM)	/* Not super-user	*/ 
#define	SR_NOENT	(- ENOENT)	/* No such file or directory */
#define	SR_SRCH		(- ESRCH)	/* No such process */
#define	SR_INTR		(- EINTR)	/* interrupted system call */
#define	SR_IO		(- EIO)		/* I-O error */
#define	SR_NXIO		(- ENXIO)	/* No such device or address */
#define	SR_2BIG		(- E2BIG)	/* Arg list too long */
#define	SR_NOEXEC	(- ENOEXEC)	/* Exec format error */
#define	SR_BAD		(- EBAD)	/* Bad ?? */
#define	SR_BADF		(- EBADF)	/* Bad file number */
#define	SR_CHILD	(- ECHILD)	/* No children */
#define	SR_AGAIN	(- EAGAIN)	/* Resource temporarily unavailable */
#define	SR_NOMEM	(- ENOMEM)	/* Not enough core */
#define	SR_ACCES	(- EACCES)	/* Permission denied */
#define	SR_FAULT	(- EFAULT)	/* Bad address */
#define	SR_NOTBLK	(- ENOTBLK)	/* Block device required */
#define	SR_BUSY		(- EBUSY)	/* Mount device busy */
#define	SR_EXIST	(- EEXIST)	/* File exists */
#define	SR_XDEV		(- EXDEV)	/* Cross-device link */
#define	SR_NODEV	(- ENODEV)	/* No such device */
#define	SR_NOTDIR	(- ENOTDIR)	/* Not a directory */
#define	SR_ISDIR	(- EISDIR)	/* Is a directory */
#define	SR_INVAL	(- EINVAL)	/* Invalid argument */
#define	SR_NFILE	(- ENFILE)	/* File table overflow */
#define	SR_MFILE	(- EMFILE)	/* Too many open files */
#define	SR_NOTTY	(- ENOTTY)	/* Inappropriate ioctl for device */
#define	SR_TXTBSY	(- ETXTBSY)	/* Text file busy */
#define	SR_FBIG		(- EFBIG)	/* File too large */
#define	SR_NOSPC	(- ENOSPC)	/* No space left on device */
#define	SR_SPIPE	(- ESPIPE)	/* Illegal seek */
#define	SR_ROFS		(- EROFS)	/* Read only file system */
#define	SR_MLINK	(- EMLINK)	/* Too many links */
#define	SR_PIPE		(- EPIPE)	/* Broken pipe */
#define	SR_DOM		(- EDOM)	/* Math arg out of domain of func */
#define	SR_RANGE	(- ERANGE)	/* Math result not representable */
#define	SR_NOMSG	(- ENOMSG)	/* No message of desired type */
#define	SR_IDRM		(- EIDRM)	/* Identifier removed */
#define	SR_CHRNG	(- ECHRNG)	/* Channel number out of range */
#define	SR_L2NSYNC	(- EL2NSYNC)	/* Level 2 not synchronized */
#define	SR_L3HLT	(- EL3HLT)	/* Level 3 halted */
#define	SR_L3RST	(- EL3RST)	/* Level 3 reset */
#define	SR_LNRNG	(- ELNRNG)	/* Link number out of range */
#define	SR_UNATCH	(- EUNATCH)	/* Protocol driver not attached */
#define	SR_NOCSI	(- ENOCSI)	/* No CSI structure available */
#define	SR_L2HLT	(- EL2HLT)	/* Level 2 halted */
#define	SR_DEADLK	(- EDEADLK)	/* Deadlock condition */
#define	SR_NOLCK	(- ENOLCK)	/* No record locks available */
#define	SR_CANCELED	(- ECANCELED)	/* Operation canceled */
#define	SR_NOTSUP	(- ENOTSUP)	/* Operation not supported */
#define	SR_DQUOT	(- EDQUOT)	/* Disc quota exceeded */
#define	SR_BADE		(- EBADE)	/* invalid exchange */
#define	SR_BADR		(- EBADR)	/* invalid request descriptor */
#define	SR_XFULL	(- EXFULL)	/* exchange full */
#define	SR_NOANO	(- ENOANO)	/* no anode */
#define	SR_BADRQC	(- EBADRQC)	/* invalid request code */
#define	SR_BADSLT	(- EBADSLT)	/* invalid slot */
#define	SR_DEADLOCK	(- EDEADLOCK)	/* file locking deadlock error */
#define	SR_BFONT	(- EBFONT)	/* bad font file fmt */
#define	SR_OWNERDEAD	(- EOWNERDEAD)	/* owner dead (for mutexes) */
#define	SR_NOTRECOVERABLE	(- ENOTRECOVERABLE)	/* not recoverable */
#define	SR_NOSTR	(- ENOSTR)	/* Device not a stream */
#define	SR_NODATA	(- ENODATA)	/* no data (for no-delay io) */
#define	SR_TIME		(- ETIME)	/* timer expired */
#define	SR_NOSR		(- ENOSR)	/* out of streams resources */
#define	SR_NONET	(- ENONET)	/* Machine is not on the network */
#define	SR_NOPKG	(- ENOPKG)	/* Package not installed */
#define	SR_REMOTE	(- EREMOTE)	/* The object is remote */
#define	SR_NOLINK	(- ENOLINK)	/* the link has been severed */
#define	SR_ADV		(- EADV)	/* advertise error */
#define	SR_SRMNT	(- ESRMNT)	/* srmount error */
#define	SR_COMM		(- ECOMM)	/* Communication error on send */
#define	SR_PROTO	(- EPROTO)	/* Protocol error */
#define	SR_MULTIHOP	(- EMULTIHOP)	/* multihop attempted */
#define	SR_BADMSG	(- EBADMSG)	/* trying to read unreadable message */
#define	SR_NAMETOOLONG	(- ENAMETOOLONG)	/* path name is too long */
#define	SR_OVERFLOW	(- EOVERFLOW)	/* value too large to be stored */
#define	SR_NOTUNIQ	(- ENOTUNIQ)	/* given login name not unique */
#define	SR_BADFD	(- EBADFD)	/* FD invalid for this operation */
#define	SR_REMCHG	(- EREMCHG)	/* Remote address changed */
#define	SR_LIBACC	(- ELIBACC)	/* Can't access a needed shared lib */
#define	SR_LIBBAD	(- ELIBBAD)	/* Accessing a corrupted shared lib */
#define	SR_LIBSCN	(- ELIBSCN)	/* .lib section in a.out corrupted */
#define	SR_LIBMAX	(- ELIBMAX)	/* Attempting link in too many libs */
#define	SR_LIBEXEC	(- ELIBEXEC)	/* Attempting to exec shared library */
#define	SR_ILSEQ	(- EILSEQ)	/* Illegal byte sequence */
#define	SR_NOSYS	(- ENOSYS)	/* Unsupported file system operation */
#define	SR_LOOP		(- ELOOP)	/* Symbolic link loop */
#define	SR_RESTART	(- ERESTART)	/* Restartable system call */
#define	SR_STRPIPE	(- ESTRPIPE)	/* if pipe/FIFO, don't sleep */
#define	SR_NOTEMPTY	(- ENOTEMPTY)	/* directory not empty */
#define	SR_USERS	(- EUSERS)	/* Too many users (for UFS) */
#define	SR_NOTSOCK	(- ENOTSOCK)	/* Socket operation on non-socket */
#define	SR_DESTADDRREQ	(- EDESTADDRREQ)	/* dst address required */
#define	SR_MSGSIZE	(- EMSGSIZE)	/* Message too long */
#define	SR_PROTOTYPE	(- EPROTOTYPE)	/* Protocol wrong type for socket */
#define	SR_NOPROTOOPT	(- ENOPROTOOPT)	/* Protocol not available */
#define	SR_PROTONOSUPPORT	(- EPROTONOSUPPORT)	/* proto not sup. */
#define	SR_SOCKTNOSUPPORT	(- ESOCKTNOSUPPORT) /* Socket not supported */
#define	SR_OPNOTSUPP	(- EOPNOTSUPP)	/* Operation not supported on socket */
#define	SR_PFNOSUPPORT	(- EPFNOSUPPORT)	/* proto family not supported */
#define	SR_AFNOSUPPORT	(- EAFNOSUPPORT)	/* AF not supported by */
#define	SR_ADDRINUSE	(- EADDRINUSE)	/* Address already in use */
#define	SR_ADDRNOTAVAIL	(- EADDRNOTAVAIL)	/* Can't assign address */
#define	SR_NETDOWN	(- ENETDOWN)	/* Network is down */
#define	SR_NETUNREACH	(- ENETUNREACH)	/* Network is unreachable */
#define	SR_NETRESET	(- ENETRESET)	/* Network dropped connection reset */
#define	SR_CONNABORTED	(- ECONNABORTED)	/* connection abort */
#define	SR_CONNRESET	(- ECONNRESET)	/* Connection reset by peer */
#define	SR_NOBUFS	(- ENOBUFS)	/* No buffer space available */
#define	SR_ISCONN	(- EISCONN)	/* Socket is already connected */
#define	SR_NOTCONN	(- ENOTCONN)	/* Socket is not connected */
#define	SR_SHUTDOWN	(- ESHUTDOWN)	/* Can't send after socket shutdown */
#define	SR_TOOMANYREFS	(- ETOOMANYREFS)	/* Too many: can't splice */
#define	SR_TIMEDOUT	(- ETIMEDOUT)	/* Connection timed out */
#define	SR_CONNREFUSED	(- ECONNREFUSED)	/* Connection refused */
#define	SR_HOSTDOWN	(- EHOSTDOWN)	/* Host is down */
#define	SR_HOSTUNREACH	(- EHOSTUNREACH)	/* No route to host */
#define	SR_WOULDBLOCK	(- EAGAIN)	/* UNIX® synonym for AGAIN */
#define	SR_ALREADY	(- EALREADY)	/* operation already in progress */
#define	SR_INPROGRESS	(- EINPROGRESS)	/* operation now in progress */
#define	SR_STALE	(- ESTALE)	/* Stale NFS file handle */
#define	SR_NOATTR	(- ENOATTR)	/* no (extended) attribute */

/* our favorite aliases */

#define	SR_QUIT		SR_L2HLT	/* quit requested */
#define	SR_EXIT		SR_L3HLT	/* exit requested */
#define	SR_NOENTRY	SR_NOENT	/* no entry */
#define	SR_NOTOPEN	SR_BADF		/* not open */
#define	SR_WRONLY	SR_BADF		/* not readable (historical) */
#define	SR_RDONLY	SR_BADF		/* not writable (historical) */
#define	SR_NOTSEEK	SR_SPIPE	/* not seekable */
#define	SR_ACCESS	SR_ACCES	/* permission denied */
#define	SR_INVALID	SR_INVAL	/* invalid argument */
#define	SR_EXISTS	SR_EXIST	/* object already exists */
#define	SR_LOCKED	SR_AGAIN	/* object is already locked */
#define	SR_INUSE	SR_ADDRINUSE	/* already in use */
#define	SR_LOCKLOST	SR_NXIO		/* a lock was lost */
#define	SR_HANGUP	SR_NXIO		/* hangup on device (not writable) */
#define	SR_POLLERR	SR_IO		/* SPECIAL for 'poll(2)' error */
#define	SR_TOOBIG	SR_2BIG		/* arguments too big */
#define	SR_BADFMT	SR_BFONT	/* invalid format */
#define	SR_FULL		SR_XFULL	/* object is full */
#define	SR_EMPTY	SR_NOENT	/* object is empty */
#define	SR_EOF		SR_NOENT	/* end-of-file */
#define	SR_NOEXIST	SR_NOENT	/* object does not exist */
#define	SR_NOTFOUND	SR_NOENT	/* not found */
#define	SR_BADREQUEST	SR_BADRQC	/* bad request code */
#define	SR_NOTCONNECTED	SR_NOTCONN	/* Socket is not connected */
#define	SR_OPEN		SR_ALREADY	/* already open */
#define	SR_OUT		SR_INPROGRESS	/* operation in progress */
#define	SR_NOTAVAIL	SR_ADDRNOTAVAIL	/* address not available */
#define	SR_UNAVAIL	SR_ADDRNOTAVAIL	/* service unavailable */
#define	SR_BADSLOT	SR_BADSLT	/* invalid slot */
#define	SR_SEARCH	SR_SRCH		/* No such process */
#define	SR_NOANODE	SR_NOANO	/* no anode! */
#define	SR_BUGCHECK	SR_NOANO	/* no anode! */
#define	SR_LOOK		SR_BADRQC	/* look-alert */
#define	SR_DOWN		SR_L2HLT	/* service down */
#define	SR_TXTBUSY	SR_TXTBSY	/* Text file busy */

/* missing codes -- backwards */

#ifndef	ETOOBIG
#define	ETOOBIG		E2BIG
#endif

#ifndef	EBADFMT
#define	EBADFMT		(- SR_BADFMT)		/* bad-format */
#endif

#ifndef	EBUGCHECK
#define	EBUGCHECK	(- SR_BUGCHECK)		/* bug-check */
#endif

#ifndef	EUNAVAIL
#define	EUNAVAIL	(- SR_UNAVAIL)		/* unavailable */
#endif

#ifndef	ENOTRECOVERABLE
#define	ENOTRECOVERABLE	(- SR_NOTRECOVERABLE)	/* not-recoverable */
#endif


#endif /* USYSRETS_INCLUDE */


