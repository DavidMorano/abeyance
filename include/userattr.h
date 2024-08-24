/* userattr HEADER */
/* lang=C20 */

/* USERATTR operating system data-base support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin.

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX system types that the brain-damaged
	MacOS operating system does NOT have.  We are trying in a very
	small way to make up for some of the immense brain-damage within
	the Apple Darwin operating system.

*******************************************************************************/

#ifndef	USERATTR_INCLUDE
#define	USERATTR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<secdb.h>		/* <- money shot (at least partly) */


/* USERATTR begin */
#if	defined(SYSHAS_USERATTR) && (SYSHAS_USERATTR > 0)

#if	defined(OSNAME_Sunos) && (OSNAME_SunOS > 0)

#include	<user_attr.h>		/* <- money shot */

#ifndef	TYPEDEF_USERATTR
#define	TYPEDEF_USERATTR
typedef userattr_t		userattr ;
#endif

#endif /* defined(OSNAME_Sunos) && (OSNAME_SunOS > 0) */

#else /* defined(SYSHAS_USERATTR) && (SYSHAS_USERATTR > 0) */

#ifndef	STRUCT_USERATTR
#define	STRUCT_USERATTR			/* structure follows */
#define	TYPEDEF_USERATTR		/* typedef follows */
	typedef struct userattr_s {
		char   *name;
		char   *qualifier;
		char   *res1;
		char   *res2;
		kva_t  *attr;
	} userattr ;			/* -> typedef USERATTR */
#endif /* STRUCT_USERATTR */

EXTERNC_begin

extern void setuserattr() noex ;
extern void enduserattr() noex ;
extern void free_userattr(userattr *) noex ;
extern userattr *getuserattr() noex ;
extern userattr *getusernam(cchar *) noex ;
extern userattr *getuseruid(uid_t) noex ;

EXTERNC_end

#endif /* defined(SYSHAS_USERATTR) && (SYSHAS_USERATTR > 0) */
/* USERATTR end */


#endif /* USERATTR_INCLUDE */


