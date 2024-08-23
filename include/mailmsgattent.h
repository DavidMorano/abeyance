/* mailmsgattent HEADER */
/* lang=C20 */

/* mail-message attachment entry object management */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSGATTENT_INCLUDE
#define	MAILMSGATTENT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<contypevals.h>		/* content-type values */
#include	<mimetypes.h>
#include	<localmisc.h>


#define	MAILMSGATTENT_MAGIC	0x49827261
#define	MAILMSGATTENT		struct mailmsgattent_head


struct mailmsgattent_head {
	cchar		*type ;		/* content-type */
	cchar		*subtype ;
	cchar		*attfname ;	/* attachment-filename */
	cchar		*auxfname ;	/* auxiliary-filename */
	cchar		*ext ;
	cchar		*encoding ;	/* content-encoding */
	cchar		*description ;
	uint		magic ;
	int		clen ;		/* content-length */
	int		clines ;	/* content-lines */
	int		cte ;		/* content-transfer-encoding */
	int		f_plaintext ;
} ;

typedef MAILMSGATTENT	mailmsgattent ;

EXTERNC_begin

extern int mailmsgattent_start(MAILMSGATTENT *,cc *,cc *,cc *,int) noex ;
extern int mailmsgattent_type(MAILMSGATTENT *,MIMETYPES *) noex ;
extern int mailmsgattent_typeset(MAILMSGATTENT *,cc *,cc *) noex ;
extern int mailmsgattent_isplaintext(MAILMSGATTENT *) noex ;
extern int mailmsgattent_finish(MAILMSGATTENT *) noex ;
extern int mailmsgattent_code(MAILMSGATTENT *,cc *) noex ;
extern int mailmsgattent_setcode(MAILMSGATTENT *,int) noex ;
extern int mailmsgattent_analyze(MAILMSGATTENT *,cc *) noex ;

EXTERNC_end


#endif /* MAILMSGATTENT_INCLUDE */


