/* qpdecoder HEADER */
/* lang=C20 */

/* Quoted-Printable (QP) decoder */
/* version %I% last-modified %G% */


/* revision history:

	= 2016-06-29, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 2016 David A­D­ Morano.  All rights reserved. */

#ifndef	QPDECODER_INCLUDE
#define	QPDECODER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usysrets.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	QPDECODER_MAGIC		0x13f3c205
#define	QPDECODER		struct qpdecoder_head
#define	QPDECODER_FL		struct qpdecoder_flags


struct qpdecoder_flags {
	uint		esc:1 ;
	uint		space:1 ;
} ;

struct qpdecoder_head {
	void		*outbuf ;	/* output-buffer */
	uint		magic ;
	int		rl ;		/* stage length */
	QPDECODER_FL	f ;
	char		rb[4+1] ;	/* stage buffer */
} ;

typedef QPDECODER	qpdecoder ;

EXTERNC_begin

extern int qpdecoder_start(QPDECODER *,int) noex ;
extern int qpdecoder_load(QPDECODER *,cchar *,int) noex ;
extern int qpdecoder_read(QPDECODER *,char *,int) noex ;
extern int qpdecoder_finish(QPDECODER *) noex ;

EXTERNC_end


#endif /* QPDECODER_INCLUDE */


