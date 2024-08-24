/* mailmsg HEADER */
/* lang=C20 */

/* message parsing object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSG_INCLUDE
#define	MAILMSG_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<unistd.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<vecobj.h>
#include	<strpack.h>
#include	<mailbox.h>
#include	<localmisc.h>


#define	MAILMSG		struct mailmsg_head
#define	MAILMSG_MAGIC	0x97634587
#define	MAILMSG_MF	5		/* buffer-size multiply factor */


struct mailmsg_head {
	strpack		*slp ;		/* String-List-Pointer */
	vecobj		*elp ;		/* Envelope-List-Pointer */
	vecobj		*hlp ;		/* Header-List-Pointer */
	uint		magic ;
	int		msgstate ;
	int		lastname ;	/* index of last HDR-name */
} ;

typedef MAILMSG		mailmsg ;

EXTERNC_begin

extern int mailmsg_start(mailmsg *) noex ;
extern int mailmsg_loadmb(mailmsg *,mailbox *,off_t) noex ;
extern int mailmsg_loadline(mailmsg *,cchar *,int) noex ;
extern int mailmsg_envcount(mailmsg *) noex ;
extern int mailmsg_envaddress(mailmsg *,int,cchar **) noex ;
extern int mailmsg_envdate(mailmsg *,int,cchar **) noex ;
extern int mailmsg_envremote(mailmsg *,int,cchar **) noex ;
extern int mailmsg_hdrcount(mailmsg *,cchar *) noex ;
extern int mailmsg_hdrikey(mailmsg *,int,cchar **) noex ;
extern int mailmsg_hdriline(mailmsg *,cchar *,int,int,cchar **) noex ;
extern int mailmsg_hdrival(mailmsg *,cchar *,int,cchar **) noex ;
extern int mailmsg_hdrval(mailmsg *,cchar *,cchar **) noex ;
extern int mailmsg_finish(mailmsg *) noex ;

EXTERNC_end

#ifdef	__cplusplus

template<typename ... Args>
inline int mailmsg_magic(mailmsg *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == MAILMSG_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (mailmsg_magic) */

#endif /* __cplusplus */


#endif /* MAILMSG_INCLUDE */


