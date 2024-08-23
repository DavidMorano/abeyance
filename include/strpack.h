/* strpack HEADER */
/* lang=C20 */

/* string-pack */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRPACK_INCLUDE
#define	STRPACK_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<vechand.h>


#define	STRPACK_MAGIC		0x42114683
#define	STRPACK			struct strpack_head
#define	STRPACK_CH		struct strpack_chunk


struct strpack_chunk {
	char		*cdata ;
	int		csz ;		/* allocated buffer length */
	int		i ;		/* index length */
	int		c ;		/* item count within chunk */
} ;

struct strpack_head {
	STRPACK_CH	*chp ;		/* current chunk pointer */
	vechand		*clp ;		/* chunk-list-pointer */
	uint		magic ;
	int		chsize ;
	int		totalsize ;
	int		c ;		/* total count */
} ;

typedef STRPACK		strpack ;
typedef STRPACK_CH	strpack_ch ;

EXTERNC_begin

extern int	strpack_start(strpack *,int) noex ;
extern int	strpack_store(strpack *,cchar *,int,cchar **) noex ;
extern int	strpack_count(strpack *) noex ;
extern int	strpack_size(strpack *) noex ;
extern int	strpack_finish(strpack *) noex ;

extern int strpack_envstore(strpack *,cc *,cc *,int,cc **) noex ;
extern int strpack_envstorer(strpack *,cc *,int,cc *,int,cc **) noex ;

EXTERNC_end


#endif /* STRPACK_INCLUDE */


