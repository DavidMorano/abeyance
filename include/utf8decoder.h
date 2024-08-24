/* utf8decoder HEADER */
/* lang=C20 */

/* UTF-8 decoder */
/* version %I% last-modified %G% */


/* revision history:

	= 2016-06-29, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 2016 David A­D­ Morano.  All rights reserved. */

#ifndef	UTF8DECODER_INCLUDE
#define	UTF8DECODER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stddef.h>		/* for |wchar_t| */
#include	<wchar.h>		/* for |wchar_t| */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


#define	UTF8DECODER_MAGIC	0x13f3c205
#define	UTF8DECODER		struct utf8decoder_head


struct utf8decoder_head {
	void		*outbuf ;	/* output-buffer */
	uint		magic ;
	int		rem ;		/* remaining bytes */
	wchar_t		code ;		/* UNICODE® code point */
} ;

typedef UTF8DECODER	utf8decoder ;

EXTERNC_begin

extern int utf8decoder_start(utf8decoder *) noex ;
extern int utf8decoder_load(utf8decoder *,cchar *,int) noex ;
extern int utf8decoder_read(utf8decoder *,wchar_t *,int) noex ;
extern int utf8decoder_finish(utf8decoder *) noex ;

EXTERNC_end


#endif /* UTF8DECODER_INCLUDE */


