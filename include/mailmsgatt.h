/* mailmsgatt HEADER */
/* lang=C20 */

/* mail-message attachment object processing */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MAILMSGATT_INCLUDE
#define	MAILMSGATT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<vecitem.h>
#include	<mimetypes.h>
#include	<contentencodings.h>

#include	<mailmsgattent.h>


#define	MAILMSGATT		VECITEM


typedef MAILMSGATT		mailmsgatt ;

EXTERNC_begin

extern int mailmsgatt_start(mailmsgatt *) noex ;
extern int mailmsgatt_finish(mailmsgatt *) noex ;
extern int mailmsgatt_add(mailmsgatt *,cchar *,cchar *,cchar *,int) noex ;
extern int mailmsgatt_count(mailmsgatt *) noex ;
extern int mailmsgatt_enum(mailmsgatt *,int,mailmsgattent **) noex ;
extern int mailmsgatt_typeatts(mailmsgatt *,MIMETYPES *) noex ;

EXTERNC_end


#endif /* MAILMSGATT_INCLUDE */


