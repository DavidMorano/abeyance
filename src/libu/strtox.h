/* strtox HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* numeric-character conversion */
/* version %I% last-modified %G% */


/* revision history:

	= 2005-10-02, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2005 David A­D­ Morano.  All rights reserved. */

#ifndef	STRTOX_INCLUDE
#define	STRTOX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<stdintx.h>


EXTERNC_begin

extern int		strtoxi(cchar *,char **,int) noex ;	/* 32-bits */
extern uint		strtoxui(cchar *,char **,int) noex ;	/* 32-bits */

extern long		strtoxl(cchar *,char **,int) noex ;	/* 64-bits */
extern ulong		strtoxul(cchar *,char **,int) noex ;	/* 64-bits */

extern longlong		strtoxll(cchar *,char **,int) noex ;	/* 128-bits */
extern ulonglong	strtoxull(cchar *,char **,int) noex ;	/* 128-bits */

#ifdef	COMMENT /* this is a 256-bit integer; but it does not yet exist */
#ifdef	__cplusplus
extern intmax		strtoxim(cchar *,char **,int) noex ;	/* 256-bits */
extern uintmax		strtoxuim(cchar *,char **,int) noex ;	/* 256-bits */
extern int512_t		strtos256(cchar *,char **,int) noex ;	/* 512-bits */
extern uint512_t	strtou256(cchar *,char **,int) noex ;	/* 512-bits */
#endif /* __cplusplus */
#endif /* COMMENT */

EXTERNC_end


#endif /* STRTOX_INCLUDE */


