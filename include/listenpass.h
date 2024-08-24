/* listenpass HEADER */
/* lang=C20 */

/* subroutine to listen on a FIFO for pass-FD requests */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	LISTENPASS_INCLUDE
#define	LISTENPASS_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>


EXTERNC_begin

extern int	listenpass(cchar *,mode_t,int) noex ;

EXTERNC_end


#endif /* LISTENPASS_INCLUDE */


