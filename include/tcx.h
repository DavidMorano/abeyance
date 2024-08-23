/* tcx HEADER */
/* lang=C20 */

/* Teerminal-Control-X (perform various terminal-control functions ) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TCX_INCLUDE
#define	TCX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* |uid_t| + |gid_t| */
#include	<termios.h>		/* |WINSIZE| */
#include	<utypedefs.h>
#include	<utypealiases.h>	/* |WINSIZE| */
#include	<clanguage.h>


EXTERNC_begin

extern int tcsetown(int,cchar *,uid_t,gid_t,mode_t) noex ;
extern int tcsetlines(int,int) noex ;
extern int tcgetlines(int) noex ;
extern int tcsetws(int,WINSIZE *) noex ;
extern int tcsetws(int,WINSIZE *) noex ;
extern int tcsetmesg(int,int) noex ;
extern int tcsetbiff(int,int) noex ;
extern int tcpeek(int,char *,int) noex ;

EXTERNC_end


#endif /* TCX_INCLUDE */


