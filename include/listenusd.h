/* listenusd HEADER */
/* lang=C20 */

/* listen on a UNIX® Socket-Datagram port w/ a socket */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	LISTENUSD_INCLUDE
#define	LISTENUSD_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>

EXTERNC_begin

extern int	listenusd(cchar *,mode_t,int) noex ;

EXTERNC_end


#endif /* LISTENUSD_INCLUDE */


