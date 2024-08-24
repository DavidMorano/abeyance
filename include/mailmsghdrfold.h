/* mailmsghdrfold HEADER */
/* lang=C20 */

/* manage folding of a mail-message header line */
/* version %I% last-modified %G% */


/* Copyright © 2009 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSGHDRFOLD_INCLUDE
#define	MAILMSGHDRFOLD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<limits.h>
#include	<usystem.h>
#include	<vecobj.h>
#include	<localmisc.h>		/* |MIN(3dam)| */


/* object defines */
#define	MAILMSGHDRFOLD_MAGIC	0x88431773
#define	MAILMSGHDRFOLD		struct mailmsghdrfold_head
#define	MAILMSGHDRFOLD_FL	struct mailmsghdrfold_flags

/* options */
#define	MAILMSGHDRFOLD_MCARRIAGE	0x0001

/* constants */
#ifdef	LINE_MAX
#define	MAILMSGHDRFOLD_BUFLEN	MAX(LINE_MAX,4096)
#else
#define	MAILMSGHDRFOLD_BUFLEN	4096
#endif


struct mailmsghdrfold_flags {
	uint		dummy:1 ;
} ;

struct mailmsghdrfold_head {
	cchar		*sp ;
	MAILMSGHDRFOLD_FL	f ;
	uint		magic ;
	int		sl ;
	int		mcols ;		/* message columns (usually 76) */
	int		ln ;		/* line within header instance */
} ;

typedef MAILMSGHDRFOLD		mailmsghdrfold ;
typedef MAILMSGHDRFOLD_FL	mailmsghdrfold_fl ;

EXTERNC_begin

extern int mailmsghdrfold_start(mailmsghdrfold *,int,int,cchar *,int) noex ;
extern int mailmsghdrfold_get(mailmsghdrfold *,int,cchar **) noex ;
extern int mailmsghdrfold_finish(mailmsghdrfold *) noex ;

EXTERNC_end


#endif /* MAILMSGHDRFOLD_INCLUDE */


