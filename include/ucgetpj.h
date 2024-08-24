/* ucgetpj HEADER */
/* lang=C20 */

/* UNIX® C-language system database access (UCGET) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCGETPJ_INCLUDE
#define	UCGETPJ_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<ucentpj.h>


EXTERNC_begin

extern int	uc_getpjbegin() noex ;
extern int	uc_getpjent(ucentpj *,char *,int) noex ;
extern int	uc_getpjnam(ucentpj *,char *,int,cchar *) noex ;
extern int	uc_getpjpid(ucentpj *,char *,int,projid_t) noex ;
extern int	uc_getpjdef(ucentpj *,char *,int,cchar *) noex ;
extern int	uc_getpjend() noex ;

EXTERNC_end


#endif /* UCGETPJ_INCLUDE */


