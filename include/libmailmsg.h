/* libmailmsg HEADER */
/* lang=C20 */

/* string-copy variant */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	LIBMAILMSG_INCLUDE
#define	LIBMAILMSG_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>

#include	<mailmsghdrs.h>
#include	<mailbox.h>
#include	<msgentry.h>

#include	<mailmsghdrfold.h>
#include	<mailmsghdrval.h>
#include	<mailmsgmatenv.h>
#include	<mailmsgmathdr.h>

#include	<mailmsgstage.h>
#include	<mbcache.h>
#include	<emainfo.h>

#include	<mhcom.h>
#include	<mcmsg.h>

#include	<hdrextnum.h>
#include	<contypevals.h>
#include	<headkeymat.h>
#include	<comparse.h>
#include	<whitelist.h>

#include	<mailmsgatt.h>
#include	<mailmsgattent.h>
#include	<mailmsgfrom.h>

#include	<mimetypes.h>


EXTERNC_begin

extern int	mailmsgheadkey(cchar *,int,cchar **) noex ;

EXTERNC_end


#endif /* LIBMAILMSG_INCLUDE */


