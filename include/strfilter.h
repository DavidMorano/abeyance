/* strfilter HEADER */
/* lang=C20 */


/* Copyright © 2009 David A­D­ Morano.  All rights reserved. */

#ifndef	STRFILTER_INCLUDE
#define	STRFILTER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<limits.h>
#include	<usystem.h>
#include	<vecstr.h>


/* object defines */
#define	STRFILTER		struct strfilter_head
#define	STRFILTER_FL		struct strfilter_flags

/* options */
#define	STRFILTER_MCARRIAGE	0x0001

/* constants */
#ifdef	LINE_MAX
#define	STRFILTER_BUFLEN	MAX(LINE_MAX,4096)
#else
#define	STRFILTER_BUFLEN	4096
#endif


struct strfilter_flags {
	uint		sslist:1 ;	/* select */
	uint		sxlist:1 ;	/* exclude */
} ;

struct strfilter_head {
	vecstr		sslist ;	/* select */
	vecstr		sxlist ;	/* exclude */
	STRFILTER_FL	f ;
} ;

typedef	STRFILTER	strfilter ;
typedef	STRFILTER_FL	strfilter_fl ;

EXTERNC_begin

extern int strfilter_start(strfilter *,cchar *,cchar *) noex ;
extern int strfilter_check(strfilter *,cchar *,int) noex ;
extern int strfilter_finish(strfilter *) noex ;

EXTERNC_end


#endif /* STRFILTER_INCLUDE */


