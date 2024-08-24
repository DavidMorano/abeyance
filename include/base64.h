/* base64 HEADER */
/* lang=C20 */

/* perform BASE64 encoding and decoding */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	BASE64_INCLUDE
#define	BASE64_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


extern const uchar	base64_et[] ;
extern const uchar	base64_dt[] ;

EXTERNC_begin

extern int		base64_e(cchar *,int,char *) noex ;
extern int		base64_d(cchar *,int,char *) noex ;

EXTERNC_end


#endif /* BASE64_INCLUDE */


