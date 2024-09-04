/* usysdefs HEADER */
/* lang=C20 */

/* define the various system buffer sizes */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-04-11, David D-A- Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2001 David D-A- Morano.  All rights reserved. */

/*******************************************************************************

	Description:
	This file defines various preprocessor variables for use
	in setting up the UNIX®-system default for various buffer
	sizes.  The real run-time system buffer sizes are (indeed)
	determined at runtime where they may exist.

	Usage:
	Among the most important uses for the data contained herein
	is the BUFSIZE management facility. It uses the data below
	to set default buffer sizes for those systems that do not 
	have dynamicly managed buffer size support in the system kernel.

*******************************************************************************/

#ifndef	USYSDEFS_INCLUDE
#define	USYSDEFS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/utsname.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<limits.h>		/* |{xxx}_MAX| */


/* extra "open" flags */

enum extraopenflags {
	extraopenflag_start = 28,
	extraopenflag_minmode = 28,
	extraopenflag_minfd,
	extraopenflag_network,
	extraopenflag_overlast
} ;


/* missing UNIX® signals */

enum signalmissings {
	signalmissing_poll = 1000,
	signalmissing_pwr,
	signalmissing_cancel,
	signalmissing_lost,
	signalmissing_overlast
} ;

#ifndef	SIGCLD
#define	SIGCLD		SIGCHLD
#endif

#ifndef	SIGPOLL
#define	SIGPOLL		signalmissing_poll
#endif

#ifndef	SIGPWR
#define	SIGPWR		signalmissing_pwr
#endif

#ifndef	SIGCANCEL
#define	SIGCANCEL	signalmissing_cancel
#endif

#ifndef	SIGLOST
#define	SIGLOST		signalmissing_lost
#endif

/* missing file open-flags */

#ifndef	O_SPECIALMASK
#define	O_SPECIALMASK	((~ 0) << extraopenflag_start)
#endif

#ifndef	O_LARGEFILE
#define	O_LARGEFILE	0
#endif

#ifndef	O_MINMODE
#define	O_MINMODE	(1 << extraopenflag_minmode)
#endif

#ifndef	O_MINFD
#define	O_MINFD		(1 << extraopenflag_minfd)
#endif

#ifndef	O_NETWORK
#define	O_NETWORK	(1 << extraopenflag_network)
#endif

/* missing from some operating systems */

#ifndef	S_IAMB
#define	S_IAMB		0x1FF		/* mask for the permissions field */
#endif

#ifndef	S_IFNAM
#define	S_IFNAM		0x5000		/* MicroSoft XENIX® named file */
#endif

#ifndef	S_IFDOOR
#define	S_IFDOOR	0xD000		/* Solaris® "door" file */
#endif

#ifndef	S_ISNAM
#define	S_ISNAM(fm)	(((fm) & S_IFMT) == S_IFNAM)
#endif

#ifndef	S_ISDOOR
#define	S_ISDOOR(fm)	(((fm) & S_IFMT) == S_IFDOOR)
#endif

/* PATHCONF preprocessor defines */

#ifndef	_PC_CHOWN_RESTRICTED
#define	_PC_CHOWN_RESTRICTED	-1
#endif

/* various limits (that might be missing) */

#ifndef	SHORT_MIN
#ifdef	SHRT_MIN
#define	SHORT_MIN	SHRT_MIN
#else
#define	SHORT_MIN	(-32768)	/* min value of a "short int" */
#endif
#endif

#ifndef	SHORT_MAX
#ifdef	SHRT_MAX
#define	SHORT_MAX	SHRT_MAX
#else
#define	SHORT_MAX	32767		/* max value of a "short int" */
#endif
#endif

#ifndef	USHORT_MAX
#ifdef	USHRT_MAX
#define	USHORT_MAX	USHRT_MAX
#else
#define	USHORT_MAX	65535		/* max value of "unsigned short int" */
#endif
#endif

#ifndef	SIZE_MAX
#define	SIZE_MAX	ULONG_MAX
#endif

#ifndef	SSIZE_MAX
#define	SSIZE_MAX	LONG_MAX
#endif

/* the following could be determined dynamically, but we choose not to */
#ifndef	TIME_MAX
#define	TIME_MAX	LONG_MAX
#endif

/* arguments (and environment) */
#ifndef	ARBUFLEN
#ifdef	ARG_MAX
#define	ARBUFLEN	ARG_MAX
#else
#define	ARBUFLEN	(2*1024*1024)	/* default for many systems */
#endif
#endif

/* max-name */
#ifndef	MNBUFLEN
#ifdef	NAME_MAX
#define	MNBUFLEN	NAME_MAX
#else
#define	MNBUFLEN	(1*1024)
#endif
#endif

/* max-path */
#ifndef	MPBUFLEN
#ifdef	PATH_MAX
#define	MPBUFLEN	PATH_MAX
#else
#define	MPBUFLEN	(4*1024)
#endif
#endif

/* max-line */
#ifndef	MLBUFLEN
#ifdef	LINE_MAX
#define	MLBUFLEN	LINE_MAX
#else
#define	MLBUFLEN	(2*2048)
#endif
#endif

/* node-name */
#ifndef	NNBUFLEN
#ifdef	_POSIX_HOST_NAME_MAX
#define	NNBUFLEN	(_POSIX_HOST_NAME_MAX-1)
#else
#ifdef	SYS_NMLN
#define	NNBUFLEN	(SYS_NMLN-1)
#else
#define	NNBUFLEN	256
#endif
#endif
#endif

/* host-name */
#ifndef	HNBUFLEN
#ifdef	MAXHOSTNAMELEN
#define	HNBUFLEN	MAXHOSTNAMELEN
#else
#define	HNBUFLEN	(1*1024)
#endif
#endif

/* user-name */
#ifndef	UNBUFLEN
#ifdef	_POSIX_LOGIN_NAME_MAX
#define	UNBUFLEN	_POSIX_LOGIN_NAME_MAX
#else
#define	UNBUFLEN	255		/* picked value from MacOS! */
#endif
#endif

/* group-name */
#ifndef	GNBUFLEN
#define	GNBUFLEN	255		/* picked value from MacOS! */
#endif

/* project-name */
#ifndef	PNBUFLEN
#define	PNBUFLEN	255		/* picked value from MacOS! */
#endif

/* password entry */
#ifndef	PWBUFLEN
#ifdef	_SC_GETPW_R_SIZE_MAX
#define	PWBUFLEN	_SC_GETPW_R_SIZE_MAX
#else
#define	PWBUFLEN	1024		/* Solaris® _SC_GETPW_R_SIZE_MAX */
#endif
#endif

/* shadow-password entry */
#ifndef	SPBUFLEN
#define	SPBUFLEN	1024		/* same as PWBUFLEN for now */
#endif

/* user-attribute entry */
#ifndef	UABUFLEN
#define	UABUFLEN	(2*1024)	/* this is just a suggestion */
#endif

/* group entry */
#ifndef	GRBUFLEN
#ifdef	_SC_GETGR_R_SIZE_MAX
#define	GRBUFLEN	_SC_GETGR_R_SIZE_MAX
#else
#define	GRBUFLEN	7296		/* Solaris® _SC_GETGR_R_SIZE_MAX */
#endif
#endif

/* project entry */
#ifndef	PJBUFLEN
#define	PJBUFLEN	(4 * 1024)	/* Solaris® recommends (4*1024) */
#endif

/* protocol entry */
#ifndef	PRBUFLEN
#define	PRBUFLEN	256
#endif

/* network entry */
#ifndef	NWBUFLEN
#define	NWBUFLEN	(4 * 1024)
#endif

/* host entry */
#ifndef	HOBUFLEN
#define	HOBUFLEN	(8 * 1024)
#endif

/* service entry */
#ifndef	SVBUFLEN
#define	SVBUFLEN	256
#endif

/* filesystem-type buffer length */
#ifndef	FSBUFLEN
#ifdef	MFSNAMELEN
#define	FSBUFLEN	MFSNAMELEN
#else
#ifdef	MFSTYPENAMELEN
#define	FSBUFLEN	(MFSTYPENAMELEN-1) /* Apple-Darwin value */
#else
#ifdef	_ST_FSTYPSZ
#define	FSBUFLEN	_ST_FSTYPSZ	/* Sun-Solaris value */
#else
#define	FSBUFLEN	15		/* Apple-Darwin value */
#endif
#endif
#endif
#endif

/* zone-name (from Zone-Info) */
#ifndef	ZNBUFLEN
#ifdef	TZNAME_MAX
#define	ZNBUFLEN	TZNAME_MAX
#else
#define	ZNBUFLEN	20		/* POSIX®-2 value */
#endif
#endif

#ifndef	NODENAMELEN
#ifdef	SYS_NMLN
#define	NODENAMELEN	(SYS_NMLN-1)	/* usually 256 for SVR4! */
#else
#define	NODENAMELEN	256		/* should be at least 256 for SVR4! */
#endif
#endif

#ifndef	USERNAMELEN
#ifdef	LOGNAME_MAX
#define	USERNAMELEN	LOGNAME_MAX
#else
#define	USERNAMELEN	32
#endif
#endif

#ifndef	GROUPNAMELEN
#ifdef	LOGNAME_MAX
#define	GROUPNAMELEN	LOGNAME_MAX
#else
#define	GROUPNAMELEN	32
#endif
#endif

/* Solaris® project name */
#ifndef	PROJNAMELEN
#ifdef	LOGNAME_MAX
#define	PROJNAMELEN	LOGNAME_MAX
#else
#define	PROJNAMELEN	32
#endif
#endif

#ifndef	LOGNAMELEN
#ifdef	LOGNAME_MAX
#define	LOGNAMELEN	LOGNAME_MAX
#else
#define	LOGNAMELEN	32
#endif
#endif

#ifndef	PASSWORDLEN
#define	PASSWORDLEN	8
#endif

/* service name */
#ifndef	SVCNAMELEN
#define	SVCNAMELEN	32
#endif

/* maximum SHM name (as per POSIX®) */
#ifndef	SHMNAME_MAX
#define	SHMNAME_MAX	14		/* historic value (in decimal) */
#endif

/* maximum PID on the system (could be wrong) */
#ifndef	PID_MAX
#define	PID_MAX		99999		/* historic value (in decimal) */
#endif

#ifndef	POLL_INTMULT
#define	POLL_INTMULT	1000		/* poll-interval-multiplier (to secs) */
#endif

/* C-C++ memory order */
#ifndef	memord_relaxed
#define	memord_relaxed	std::memory_order_relaxed
#define	memord_consume	std::memory_order_consume
#define	memord_acquire	std::memory_order_acquire
#define	memord_release	std::memory_order_release
#define	memord_acqrel	std::memory_order_acq_rel
#define	memord_seq	std::memory_order_seq_cst
#endif /* memord_relaxed */


#endif /* USYSDEFS_INCLUDE */


