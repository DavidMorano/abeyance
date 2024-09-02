/* mailmsgstage HEADER */
/* lang=C20 */

/* Message-Entry */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object represents a Message-Entry.
	It is used within the MAILMSGSTAGE object (unless used elsewhere
	also).

*******************************************************************************/

#ifndef		MSGENTRY_INCLUDE
#define		MSGENTRY_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* |off_t| */
#include	<climits>
#include	<cstdlib>
#include	<cstring>		/* |memcpy(3c)| */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<usystem.h>
#include	<mailmsg.h>
#include	<fdliner.h>
#include	<localmisc.h>


#define	MSGENTRY	struct msgentry_head
#define	MSGENTRY_FL	struct msgentry_flags


struct msgentry_flags {
	uint		ctype:1 ;
	uint		cencoding:1 ;
	uint		ctplain:1 ;
	uint		ceplain:1 ;
	uint		plaintext:1 ;
	uint		clen:1 ;
	uint		clines:1 ;
	uint		eoh:1 ;
} ;

struct msgentry_head {
	MSGENTRY_FL	f, hdr ;
	mailmsg		m ;
	off_t		boff ;		/* w/ tmpfile */
	int		blen ;		/* w/ tmpfile */
	int		clen ;		/* supplied or calculated */
	int		clines ;	/* supplied or calculated */
} ;

typedef MSGENTRY	msgentry ;
typedef MSGENTRY_FL	msgentry_fl ;

EXTERNC_begin

extern int	msgentry_start(msgentry *) noex ;
extern int	msgentry_finish(msgentry *) noex ;
extern int	msgentry_loadline(msgentry *,cchar *,int) noex ;
extern int	msgentry_loadhdrs(msgentry *,fdliner *) noex ;
extern int	msgentry_setflags(msgentry *) noex ;
extern int	msgentry_setct(msgentry *) noex ;
extern int	msgentry_setce(msgentry *) noex ;
extern int	msgentry_getclines(msgentry *) noex ;
extern int	msgentry_setclines(msgentry *,int) noex ;
extern int	msgentry_getclen(msgentry *) noex ;
extern int	msgentry_setclen(msgentry *,int) noex ;
extern int	msgentry_setoff(msgentry *,off_t) noex ;
extern int	msgentry_setlen(msgentry *,int) noex ;
extern int	msgentry_gethdrnum(msgentry *,cchar *) noex ;

EXTERNC_end


#endif /* MSGENTRY_INCLUDE */


