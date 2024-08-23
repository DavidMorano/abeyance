/* mkaddr HEADER */
/* lang=C20 */

/* make a character (8-bit) out of an integer */
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

#ifndef	MKADDR_INCLUDE
#define	MKADDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int mkaddrbest(char *,int,cchar *,int) noex ;
extern int mkaddrfrom(char *,int,cchar *,int) noex ;
extern int mkaddrname(char *,int,cchar *,int) noex ;
extern int mkaddrdisp(char *,int,cchar *,int) noex ;

EXTERNC_end


#endif /* MKADDR_INCLUDE */


