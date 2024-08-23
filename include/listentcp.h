/* listentcp HEADER */
/* lang=C20 */

/* listen on a TCP port w/ a socket */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	LISTENTCP_INCLUDE
#define	LISTENTCP_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>

EXTERNC_begin

extern int	listentcp(int,cchar *,cchar *,int) noex ;

EXTERNC_end


#endif /* LISTENTCP_INCLUDE */


