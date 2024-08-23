/* snx HEADER */
/* lang=C20 */

/* counted c-string operations */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SNX_INCLUDE
#define	SNX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* types (see below) */
#include	<stdarg.h>		/* |va_list| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<sncpy.h>
#include	<sncpyx.h>		/* repeat? */
#include	<sncpyxc.h>		/* repeat? */
#include	<sncpyxw.h>		/* repeat? */
#include	<snxxx.h>
#include	<snuuid.h>
#include	<snadd.h>
#include	<sntmtime.h>
#include	<snflags.h>
#include	<snuuid.h>
#include	<snclean.h>


EXTERNC_begin

extern int snfsflags(char *,int,ulong) noex ;
extern int snopenflags(char *,int,int) noex ;
extern int snpollflags(char *,int,int) noex ;
extern int snxtilook(char *,int,int) noex ;
extern int sninetaddr(char *,int,int,cchar *) noex ;
extern int snsigabbr(char *,int,uint) noex ;
extern int snabbr(char *,int,cchar *,int) noex ;
extern int snshellunder(char *,int,pid_t,cchar *) noex ;
extern int snfilemode(char *,int,mode_t) noex ;
extern int sntid(char *,int,pthread_t) noex ;
extern int snerrabbr(char *,int,int) noex ;
extern int snwvprintf(char *,int,cchar *,va_list) noex ;
extern int snwprintf(char *,int,cchar *,...) noex ;
extern int snrealname(char *,int,cchar **,int) noex ;
extern int snloadavg(char *,int,uint,int,int,int) noex ;
extern int snkeyval(char *,int,cchar *,int,cchar *,int) noex ;

EXTERNC_end


#endif /* SNX_INCLUDE */


