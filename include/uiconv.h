/* uiconv HEADER */
/* lang=C++20 */

/* UNIX® international conversion */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UICONV_INCLUDE
#define	UICONV_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	UICONV		struct uiconv_head
#define	UICONV_MAGIC	0x67298362


struct uiconv_head {
	void		*cdp ;
	uint		magic ;
} ;

typedef UICONV		uiconv ;

EXTERNC_begin

extern int	uiconv_open(uiconv *,cchar *,cchar *) noex ;
extern int	uiconv_trans(uiconv *,cchar **,int *,char **,int *) noex ;
extern int	uiconv_close(uiconv *) noex ;

EXTERNC_end


#endif /* UICONV_INCLUDE */


