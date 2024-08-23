/* uclibmemalloc HEADER */
/* lang=C20 */

/* memory allocation facility (for library use) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UCLIBMEMALLOC_INCLUDE
#define	UCLIBMEMALLOC_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int uc_libmallocstrw(cchar *,int,cchar **) noex ;
extern int uc_libmallocsys(int,char **) noex ;
extern int uc_libmalloc(int,void *) noex ;
extern int uc_libvalloc(int,void *) noex ;
extern int uc_libcalloc(int,int,void *) noex ;
extern int uc_librealloc(cvoid *,int,void *) noex ;
extern int uc_libfree(cvoid *) noex ;

EXTERNC_end


#endif /* UCLIBMEMALLOC_INCLUDE */


