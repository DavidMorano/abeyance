/* mailmsgstage HEADER */
/* lang=C20 */

/* process the input messages and spool them up */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSGSTAGE_INCLUDE
#define	MAILMSGSTAGE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vechand.h>


#define	MAILMSGSTAGE		struct mailmsgstage_head
#define	MAILMSGSTAGE_FL		struct mailmsgstage_flags
#define	MAILMSGSTAGE_MAGIC	0x53232856
#define	MAILMSGSTAGE_TMPDNAME	"/tmp"

#define	MAILMSGSTAGE_OUSECLEN	(1 << 0) /* option: use content-length */
#define	MAILMSGSTAGE_OUSECLINES	(1 << 1) /* option: use content-lines */

#define	MAILMSGSTAGE_MCLEN	(1 << 0)
#define	MAILMSGSTAGE_MCLINES	(1 << 1)
#define	MAILMSGSTAGE_MCTYPE	(1 << 2)
#define	MAILMSGSTAGE_MCENCODING	(1 << 3)
#define	MAILMSGSTAGE_MCTPLAIN	(1 << 4)
#define	MAILMSGSTAGE_MCEPLAIN	(1 << 5)
#define	MAILMSGSTAGE_MCPLAIN	(1 << 6)


struct mailmsgstage_flags {
	uint		useclen:1 ;
	uint		useclines:1 ;
} ;

struct mailmsgstage_head {
	cchar		*tmpfname ;
	char		*mapdata ;
	vechand		*mlp ;
	size_t		tflen ;
	size_t		mapsize ;
	MAILMSGSTAGE_FL	f ;
	uint		magic ;
	int		nmsgs ;
	int		tfd ;
	int		to ;
} ;

typedef MAILMSGSTAGE		mailmsgstage ;
typedef MAILMSGSTAGE_FL		mailmsgstage_fl ;

EXTERNC_begin

extern int mailmsgstage_start(mailmsgstage *,int,int,int) noex ;
extern int mailmsgstage_count(mailmsgstage *) noex ;
extern int mailmsgstage_clen(mailmsgstage *,int) noex ;
extern int mailmsgstage_clines(mailmsgstage *,int) noex ;
extern int mailmsgstage_bodyget(mailmsgstage *,int,off_t,cchar **) noex ;
extern int mailmsgstage_bodyread(mailmsgstage *,int,off_t,char *,int) noex ;
extern int mailmsgstage_envcount(mailmsgstage *,int) noex ;
extern int mailmsgstage_envaddress(mailmsgstage *,int,int,cchar **) noex ;
extern int mailmsgstage_envdate(mailmsgstage *,int,int,cchar **) noex ;
extern int mailmsgstage_envremote(mailmsgstage *,int,int,cchar **) noex ;
extern int mailmsgstage_hdrcount(mailmsgstage *,int,cchar *) noex ;
extern int mailmsgstage_hdrikey(mailmsgstage *,int,int,cchar **) noex ;
extern int mailmsgstage_hdriline(mailmsgstage *,int,cchar *,int,
		int,cchar **) noex ;
extern int mailmsgstage_hdrival(mailmsgstage *,int,cchar *,int,cchar **) noex ;
extern int mailmsgstage_hdrval(mailmsgstage *,int,cchar *,cchar **) noex ;
extern int mailmsgstage_flags(mailmsgstage *,int) noex ;
extern int mailmsgstage_finish(mailmsgstage *) noex ;

EXTERNC_end


#endif /* MAILMSGSTAGE_INCLUDE */


