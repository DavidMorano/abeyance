/* comparse HEADER */
/* lang=C20 */

/* comment-parse (for RFC822) small strings (like for stupid RFC822 date) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-22, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	COMPARSE_INCLUDE
#define	COMPARSE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	COMPARSE_MAGIC		0x77811276
#define	COMPARSE		struct comparse_head
#define	COMPARSE_STR		struct comparse_string
#define	COMPARSE_LVALUE		MAILADDRLEN
#define	COMPARSE_LCOMMENT	LINEBUFLEN


struct comparse_string {
	cchar		*sp ;
	int		sl ;
} ;

struct comparse_head {
	COMPARSE_STR	val ;
	COMPARSE_STR	com ;
	uint		magic ;
} ;

typedef COMPARSE	comparse ;
typedef COMPARSE_STR	comparse_str ;

EXTERNC_begin

extern int comparse_start(COMPARSE *,cchar *,int) noex ;
extern int comparse_getval(COMPARSE *,cchar **) noex ;
extern int comparse_getcom(COMPARSE *,cchar **) noex ;
extern int comparse_finish(COMPARSE *) noex ;

EXTERNC_end


#endif /* COMPARSE_INCLUDE */


