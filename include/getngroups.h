/* getngroups HEADER */
/* lang=C20 */

/* get the maximum number of supplemetary groups allowed per process */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETNGROUPS_INCLUDE
#define	GETNGROUPS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#ifdef	__cplusplus

extern "C" {
    extern int getngroups(int) noex ;
    extern int getngroupsx(int = 0) noex ;
}

#else /* __cplusplus */

extern int getngroups() noex ;
extern int getngroupsx(int) noex ;

#endif /* __cplusplus */


#endif /* GETNGROUPS_INCLUDE */


