/* termtrans HEADER */
/* lang=C20 */

/* terminal-character-translation management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TERMTRANS_INCLUDE
#define	TERMTRANS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stddef.h>
#include	<uiconv.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


#define	TERMTRANS	struct termtrans_head
#define	TERMTRANS_FL	struct termtrans_flags
#define	TERMTRANS_MAGIC	0x67298363
#define	TERMTRANS_NCS	"UCS-4"


struct termtrans_flags {
	uint		dummy:1 ;
} ;

struct termtrans_head {
	void		*cvp ;		/* character-vector-pointer */
	void		*lvp ;		/* line-vector-pointer */
	UICONV		id ;
	TERMTRANS_FL	f ;
	uint		magic ;
	uint		termattr ;	/* mask of terminal attributes */
	int		ncols ;		/* terminal columns */
	int		ncol ;
} ;

typedef TERMTRANS	termtrans ;
typedef TERMTRANS_FL	termtrans_fl ;

EXTERNC_begin

extern int termtrans_start(termtrans *,cchar *,cchar *,int,int) noex ;
extern int termtrans_load(termtrans *,const wchar_t *,int) noex ;
extern int termtrans_getline(termtrans *,int,cchar **) noex ;
extern int termtrans_finish(termtrans *) noex ;

EXTERNC_end


#endif /* TERMTRANS_INCLUDE */


