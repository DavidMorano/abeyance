/* fmqhdr HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 (confirmance reviewed) */

/* File-Message-Queue-Header (FMQ header) file */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FMQHDR_INCLUDE
#define	FMQHDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	FMQHDR			struct fmqhdr_head
#define	FMQHDR_MAGICSIZE	16
#define	FMQHDR_MAGICSTR		"FMQ"
#define	FMQHDR_VERSION		0
#define	FMQHDR_TYPE		0


enum fmqhdrs {
	fmqhdr_nmsg,
	fmqhdr_wtime,
	fmqhdr_wcount,
	fmqhdr_bsz,
	fmqhdr_blen,
	fmqhdr_len,
	fmqhdr_ri,
	fmqhdr_wi,
	fmqhdr_overlast
} ;

struct fmqhdr_head {
	uint		nmsg ;		/* number of messages */
	uint		wtime ;		/* write time */
	uint		wcount ;	/* write count */
	uint		bsz ;		/* total buffer size */
	uint		blen ;		/* buffer bytes used */
	uint		len ;		/* user bytes used */
	uint		ri ;		/* index-read */
	uint		wi ;		/* index-write */
	uchar		vetu[4] ;
} ;

#ifdef	__cplusplus
struct fmqhdr : fmqhdr_head {
	fmqhdr(const fmqhdr &) = delete ;
	fmqhdr &operator = (const fmqhdr &) = delete ;
	fmqhdr() = default ;
	int rd(char *,int) noex ;
	int wr(cchar *,int) noex ;
} ; /* end struct (fmqhdr) */
#else	/* __cplusplus */
typedef FMQHDR		fmqhdr ;
#endif	/* __cplusplus */

EXTERNC_begin

extern int	fmqhdr_rd(fmqhdr *,char *,int) noex ;
extern int	fmqhdr_wr(fmqhdr *,cchar *,int) noex ;

EXTERNC_end


#endif /* FMQHDR_INCLUDE */


