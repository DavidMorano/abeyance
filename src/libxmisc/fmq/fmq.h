/* fmq HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* File Message Queue (FMQ) */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-07-23, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FMQ_INCLUDE
#define	FMQ_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* system types */
#include	<signal.h>		/* |sigset_t| */
#include	<time.h>		/* |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	FMQ_MAGIC		0x21419876
#define	FMQ			struct fmq_head
#define	FMQ_FL			struct fmq_flags
#define	FMQ_FM			struct fmq_filemagic
#define	FMQ_FH			struct fmq_filehead
#define	FMQ_BD			struct fmq_bufdesc
#define	FMQ_FILEMAGIC		"FMQ"
#define	FMQ_FILEMAGICSIZE	16
#define	FMQ_FILEVERSION		0
#define	FMQ_ENDIAN		0
#define	FMQ_MINBUFSIZE		(3 * 64 * 1024)	/* 2 x 64k byte buffers */


struct fmq_filemagic {
	char		magic[16] ;
	char		vetu[4] ;
} ;

/* decoded file header values */
struct fmq_filehead {
	uint		nmsg ;		/* number of messages */
	uint		wtime ;		/* write time */
	uint		wcount ;	/* write count */
	uint		bsz ;		/* total buffer size */
	uint		blen ;		/* buffer bytes used */
	uint		len ;		/* user bytes used */
	uint		ri ;		/* index-read */
	uint		wi ;		/* index-write */
} ;

struct fmq_bufdesc {
	char		*buf ;
	uint		bsz ;		/* allocated size */
	uint		i ;		/* index to valid data */
	uint		len ;		/* length of valid data */
} ;
	
struct fmq_flags {
	uint		fileinited:1 ;
	uint		writable:1 ;
	uint		readlocked:1 ;
	uint		writelocked:1 ;
	uint		cursorlockbroken:1 ;	/* cursor lock broken */
	uint		cursoracc:1 ;		/* accessed while cursored ? */
	uint		remote:1 ;		/* remote mounted file */
	uint		bufvalid:1 ;		/* buffer valid */
	uint		create:1 ;
	uint		ndelay:1 ;
	uint		nonblock:1 ;
	uint		created:1 ;		/* result of open */
} ;

struct fmq_head {
	cchar		*fname ;
	FMQ_FL		f ;
	FMQ_FM		m ;
	FMQ_FH		h ;
	FMQ_BD		b ;
	sigset_t	sigmask ;
	time_t		tiopen ;	/* file open time */
	time_t		tiaccess ;	/* file access time */
	time_t		timod ;		/* file modification time */
	uint		magic ;
	int		oflags ;
	int		pagesize ;
	int		filesize ;
	int		bufsize ;	/* user hint at open time */
	int		fd ;
	int		count ;
	mode_t		operm ;
} ; /* end struct (fmq_head) */

typedef	FMQ		fmq ;
typedef	FMQ_FL		fmq_fl ;
typedef	FMQ_FM		fmq_fm ;
typedef	FMQ_FH		fmq_fh ;
typedef	FMQ_BD		fmq_bd ;

EXTERNC_begin

extern int	fmq_open(fmq *,cchar *,int,mode_t,int) noex ;
extern int	fmq_close(fmq *) noex ;
extern int	fmq_send(fmq *,cvoid *,int) noex ;
extern int	fmq_sende(fmq *,cvoid *,int,int,int) noex ;
extern int	fmq_recv(fmq *,void *,int) noex ;
extern int	fmq_recve(fmq *,void *,int,int,int) noex ;

EXTERNC_end

#ifdef	__cplusplus

template<typename ... Args>
inline int fmq_magic(fmq *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == FMQ_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (fmq_magic) */

#endif /* __cplusplus */


#endif /* FMQ_INCLUDE */


