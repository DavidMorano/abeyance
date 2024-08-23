/* snxxx HEADER */
/* lang=C20 */

/* counted c-string operations */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SNXXX_INCLUDE
#define	SNXXX_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern int snsds(char *,int,cchar *,cchar *) noex ;
extern int snscs(char *,int,cchar *,cchar *) noex ;
extern int snses(char *,int,cchar *,cchar *) noex ;
extern int snsdd(char *,int,cchar *,uint) noex ;
extern int snddd(char *,int,uint,uint) noex ;
extern int snsd(char *,int,cchar *,uint) noex ;

EXTERNC_end


#endif /* SNXXX_INCLUDE */


