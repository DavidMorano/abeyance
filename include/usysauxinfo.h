/* usysauxinfo HEADER */
/* lang=C20 */

/* UNIX® system-auxillary-information */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	USYSAUXINFO_INCLUDE
#define	USYSAUXINFO_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>

#include	<usysauxinforeqs.h>


/* System-Auxillary-Information (SAI) */
#define	SAI_ARCHITECTURE	usysauxinforeq_architecture
#define SAI_MACHINE		usysauxinforeq_machine
#define	SAI_PLATFORM		usysauxinforeq_platform
#define	SAI_HWPROVIDER		usysauxinforeq_hwprovider
#define SAI_HWSERIAL		usysauxinforeq_hwserial
#define SAI_RPCDOMAIN		usysauxinforeq_rpcdomain
#define SAI_UUID		usysauxinforeq_uuid


namespace usysauxinfo {
    extern int ugetauxinfo(char *,int,int) noex ;
}


#endif /* __cplusplus */
#endif /* SYSUAUXINFO_INCLUDE */


