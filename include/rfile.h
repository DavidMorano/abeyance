/* rfile HEADER */
/* lang=C20 */

/* subroutine to open a FD to a remotely executing command */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	RFILE_INCLUDE
#define	RFILE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>

#include	<rex.h>
#include	<netfile.h>


EXTERNC_begin

extern int rfile(cc *,rex_au *,cc *,int,mode_t) noex ;

EXTERNC_end


#endif /* RFILE_INCLUDE */


