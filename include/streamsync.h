/* streamsync HEADER */
/* lang=C20 */

/* data stream synchronization mechanism */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STREAMSYNC_INCLUDE
#define	STREAMSYNC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	STREAMSYNC_MAGIC	0x96817463
#define	STREAMSYNC		struct streamsync_head


struct streamsync_head {
	char		*st ;		/* sequence to test against */
	char		*data ;		/* the data stream */
	uint		magic ;
	int		stlen ;		/* sequence length needed */
	int		i ;		/* current length */
} ;

typedef STREAMSYNC	streamsync ;

EXTERNC_begin

extern int streamsync_start(streamsync *,cchar *,int) noex ;
extern int streamsync_test(streamsync *,int) noex ;
extern int streamsync_finish(streamsync *) noex ;

EXTERNC_end


#endif /* STREAMSYNC_INCLUDE */


