/* contentencodings HEADER */
/* lang=C20 */

/* content-encodings for mail message headers */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-03, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CONTENTENCODINGS
#define	CONTENTENCODINGS


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


enum contentencodings {
	contentencoding_none,
	contentencoding_7bit,
	contentencoding_8bit,
	contentencoding_binary,
	contentencoding_base64,
	contentencoding_quoted,
	contentencoding_overlast
} ;

extern cchar	*contentencodings[] ;


#define	CF_NONE		contentencoding_none,
#define	CE_7BIT		contentencoding_7bit
#define	CE_8BIT		contentencoding_8bit
#define	CE_BINARY	contentencoding_binary
#define	CE_BASE64	contentencoding_base64
#define	CE_QUOTED	contentencoding_quoted
#define	CE_OVERLAST	contentencoding_overlast


#endif /* CONTENTENCODINGS */


