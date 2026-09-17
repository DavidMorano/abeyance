/* env HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* environment management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ENV_INCLUDE
#define	ENV_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	setenv(cchar *name,cchar *value,int rewrite) noex ;
extern void	unsetenv(cchar *name) noex ;

EXTERNC_end


#endif /* ENV_INCLUDE */


