/* mklogid HEADER */
/* lang=C20 */

/* make a log-ID c-string, suitable for logging purposes */
/* version %I% last-modified %G% */


/* revision history:

  = 2000-05-14, David A-D- Morano
	This was written for Rightcore Network Services (RNS).
 
  = 2018-11-27, David A-D- Morano
	I created an inline version for the C language. We will
	likely do something for C++ at some other time.

  = 2023-10-23, David A-D- Morano
	At some point I added an inline (here) for the C++ language.

*/

/* Copyright (c) 1998,2018,23023 David A-D- Morano.  All rights reserved. */

#ifndef	MKLOGID_INCLUDE
#define	MKLOGID_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int	mklogid(char *,int,cchar *,int,int) noex ;
extern int	mkplogid(char *,int,cchar *,int) noex ;
extern int	mksublogid(char *,int,cchar *,int) noex ;

EXTERNC_end


#endif /* MKLOGID_INCLUDE */


