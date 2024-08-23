/* ucsyspj HEADER */
/* lang=C20 */

/* additional operaring-system support for PEOJECT-DB access */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the MacOS operating system.

*******************************************************************************/

#ifndef	UCSYSPJ_INCLUDE
#define	UCSYSPJ_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#ifndef	PROJECT
#define	PROJECT		struct project
#endif

#ifndef	CPROJECT
#define	CPROJECT	const struct project
#endif

#if	defined(SYSHAS_PROJECT) && (SYSHAS_PROJECT > 0)

#include	<project.h>

#ifndef	TYPEDEF_PROJID
#define	TYPEDEF_PROJID	/* this typdef should already exist */
#endif

#else /* defined(SYSHAS_PROJECT) && (SYSHAS_PROJECT > 0) */

#ifndef	TYPEDEF_PROJID
#define	TYPEDEF_PROJID
typedef int	projid_t ;
#endif

struct project {
	char		*pj_name ;
	char		*pj_comment ;
	char		*pj_attr ;
	char		**pj_users ;
	char		**pj_groups ;
	projid_t	pj_projid ;
} ; /* end struct (project) */

#ifndef	SUBROUTINE_GETPROJID
#define	SUBROUTINE_GETPROJID

EXTERNC_begin

extern projid_t getprojid() noex ;

EXTERNC_end

#endif /* SUBROUTINE_GETPROJID */

#ifndef	SUBROUTINE_GETPJ
#define	SUBROUTINE_GETPJ

EXTERNC_begin

extern void	setprojent() noex ;
extern void	endprojent() noex ;
extern PROJECT	*getpjent() noex ;
extern PROJECT	*getpjnam(cchar *) noex ;
extern PROJECT	*getpjpid(projid_t) noex ;
extern PROJECT	*getpjdef(cchar *) noex ;

EXTERNC_end

#endif /* SUBROUTINE_GETPJ */

#endif /* defined(SYSHAS_PROJECT) && (SYSHAS_PROJECT > 0) */

EXTERNC_begin

extern int	getpjent_rp(PROJECT *,char *,int) noex ;
extern int	getpjnam_rp(PROJECT *,char *,int,cchar *) noex ;
extern int	getpjpid_rp(PROJECT *,char *,int,projid_t) noex ;
extern int	getpjdef_rp(PROJECT *,char *,int,cchar *) noex ;

EXTERNC_end


#endif /* UCSYSPJ_INCLUDE */


