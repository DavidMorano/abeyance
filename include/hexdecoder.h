/* hexdecoder HEADER */
/* lang=C99 */

/* HEX decoder */
/* version %I% last-modified %G% */


/* revision history:

	= 2016-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2016 David A­D­ Morano.  All rights reserved. */

#ifndef	HEXDECODER_INCLUDE
#define	HEXDECODER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	HEXDECODER_MAGIC	0x13f3c202
#define	HEXDECODER		struct hexdecoder_head


struct hexdecoder_head {
	void		*outbuf ;	/* output-buffer */
	uint		magic ;
	int		rl ;		/* residue length ('0' or '1') */
	char		rb[2] ;		/* residue buffer */
} ;

typedef HEXDECODER	hexdecoder ;

EXTERNC_begin

extern int hexdecoder_start(HEXDECODER *) noex ;
extern int hexdecoder_load(HEXDECODER *,cchar *,int) noex ;
extern int hexdecoder_read(HEXDECODER *,char *,int) noex ;
extern int hexdecoder_finish(HEXDECODER *) noex ;

EXTERNC_end


#endif /* HEXDECODER_INCLUDE */


