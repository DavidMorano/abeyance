/* recip HEADER */
/* lang=C20 */

/* recipient object for DMAIL¦DMAILBOX */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	RECIP_INCLUDE
#define	RECIP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<limits.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<vecitem.h>


#define	RECIP_MAGIC	0x73169284
#define	RECIP		struct recip_head
#define	RECIP_FL	struct recip_flags
#define	RECIP_ENT	struct recip_ent


struct recip_ent {
	int		moff ;
	int		mlen ;
} ;

struct recip_flags {
	uint		user:1 ;	/* is an actual user */
} ;

struct recip_head {
	vecitem		*mdp ;		/* message delivery entries */
	cchar		*recipient ;	/* recipient name */
	cchar		*name ;		/* recipient real-name (if known) */
	cchar		*maildname ;	/* recipient maildir */
	uid_t		uid ;
	RECIP_FL	f ;		/* flags */
	uint		magic ;
	int		mbo ;		/* mailbox-message offset */
	int		n ;		/* number of deliveries */
	int		ds ;		/* delivery status */
} ;

typedef RECIP		recip ;
typedef RECIP_FL	recip_fl ;
typedef RECIP_ENT	recip_ent ;

EXTERNC_begin

extern int	recip_start(recip *,cchar *,int) noex ;
extern int	recip_get(recip *,cchar **) noex ;
extern int	recip_setuser(recip *,uid_t) noex ;
extern int	recip_setname(recip *,cchar *,int) noex ;
extern int	recip_setmailspool(recip *,cchar *,int) noex ;
extern int	recip_mbo(recip *,int) noex ;
extern int	recip_ds(recip *,int) noex ;
extern int	recip_mo(recip *,int,int) noex ;
extern int	recip_match(recip *,cchar *,int) noex ;
extern int	recip_getmbo(recip *) noex ;
extern int	recip_getmo(recip *,int,int *) noex ;
extern int	recip_getname(recip *,cchar **) noex ;
extern int	recip_getmailspool(recip *,cchar **) noex ;
extern int	recip_getuser(recip *,uid_t *) noex ;
extern int	recip_isuser(recip *) noex ;
extern int	recip_finish(recip *) noex ;

EXTERNC_end


#endif /* RECIP_INCLUDE */


