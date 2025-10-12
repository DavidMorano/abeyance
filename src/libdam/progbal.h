/* progbal HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* language totken balance checker support */
/* version %I% last-modified %G% */


/* revision history:

	= 2016-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2016 David A­D­ Morano.  All rights reserved. */

#ifndef	PROGBAL_INCLUDE
#define	PROGBAL_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>


#define	PROGBAL_MAGIC	0x13f3c203
#define	PROGBAL		struct progbal_head
#define	PROGBAL_NCH	3


struct progbal_head {
	uint		magic ;
	int		counts[PROGBAL_NCH] ;
	int		f_fail ;
} ;

EXTERNC_begin

extern int progbal_start(PROGBAL *) noex ;
extern int progbal_load(PROGBAL *,cchar *,int) noex ;
extern int progbal_read(PROGBAL *,char *,int) noex ;
extern int progbal_finish(PROGBAL *) noex ;

EXTERNC_end


#endif /* PROGBAL_INCLUDE */


