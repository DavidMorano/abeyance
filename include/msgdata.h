/* msgdata HEADER */
/* lang=C++20 */

/* miscellaneous message handling */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-11-01, David A­D­ Morano
	Written to have a place for the various KSH initialization subroutines.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

#ifndef	MSGDATA_INCLUDE
#define	MSGDATA_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<sockaddress.h>


#ifndef	MSGBUFLEN
#define	MSGBUFLEN	2048
#endif

#ifndef	MSGHDR
#define	MSGHDR		srtuct msghdr
#endif

#ifndef	CONMSGHDR
#define	CONMSGHDR	srtuct cmsghdr
#endif

#define	MSGDATA		struct msgdata_head


struct msgdata_head {
	MSGHDR		msg ;
	SOCKADDRESS	from ;
	IOVEC		vecs[1] ;
	CONMSGHDR	*cmsgp ;	/* Control-Message-Header */
	void		*a ;		/* allocation */
	char		*mbuf ;		/* buffer */
	int		clen ;		/* Control-Message length */
	int		mlen ;		/* fixed at buffer size */
	int		ml ;		/* variable as used */
	int		ns ;
} ;

typedef MSGDATA		msgdata ;

EXTERNC_begin

extern int	msgdata_init(msgdata *,int) noex ;
extern int	msgdata_setaddr(msgdata *,cvoid *,int) noex ;
extern int	msgdata_getbufsize(msgdata *) noex ;
extern int	msgdata_getbuf(msgdata *,char **) noex ;
extern int	msgdata_getdatalen(msgdata *) noex ;
extern int	msgdata_getdata(msgdata *,char **) noex ;
extern int	msgdata_setdatalen(msgdata *,int) noex ;
extern int	msgdata_send(msgdata *,int,int,int) noex ;
extern int	msgdata_recv(msgdata *,int) noex ;
extern int	msgdata_recvto(msgdata *,int,int) noex ;
extern int	msgdata_conpass(msgdata *,int) noex ;
extern int	msgdata_getpassfd(msgdata *) noex ;
extern int	msgdata_rmeol(msgdata *) noex ;
extern int	msgdata_fini(msgdata *) noex ;

EXTERNC_end


#endif /* MSGDATA_INCLUDE */


