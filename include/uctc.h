/* uctc HEADER */
/* lang=C20 */

/* LIBUC Teermina-Control functions */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCTC_INCLUDE
#define	UCTC_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<termios.h>		/* |TERMIOS| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>	/* |TERMIOS| */
#include	<usysrets.h>


EXTERNC_begin

extern int uc_tcdrain(int) noex ;
extern int uc_tcflow(int,int) noex ;
extern int uc_tcflush(int,int) noex ;
extern int uc_tcattrget(int,TERMIOS *) noex ;
extern int uc_tcattrset(int,int,const TERMIOS *) noex ;
extern int uc_tcgetpgrp(int) noex ;
extern int uc_tcgetsid(int) noex ;
extern int uc_tcsetpgrp(int,pid_t) noex ;

EXTERNC_end


#endif /* UCTC_INCLUDE */


