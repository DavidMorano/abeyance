/* ucsysgr HEADER */
/* lang=C20 */

/* additional operaring-system support for GROUP-DB access */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This file contains the UNIX system types that the brain-damaged
	Apple Darwin operating system does NOT have.  We are trying
	in a very small way to make up for some of the immense
	brain-damage within the Apple Darwin operating system.

	The idea here is that each OS needs to supply two types of
	possibly interfaces.  One interface to be supplied is the
	normal non-reentrant type interfaces IF your OS is missing
	those interfaces.  If your OS already has those exported,
	then you do not have to supply there here.  The second type
	of interface is the POSIX variant is whatever reentrant
	interfaces your OS alread has.  Your OS has either its own
	type of reentrant interface OR it has the POSIX standard
	reentrant interface OR, in the case of Solaris and Illumos,
	both standard POSIX and non-standard POSIX reentrant
	interfaces are supplied for some subroutines.

*******************************************************************************/

#ifndef	UCSYSGR_INCLUDE
#define	UCSYSGR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<grp.h>


/* GETGRXXXR begin */

#ifndef	GROUP
#define	GROUP	struct group
#endif

#ifndef	CGROUP
#define	CGROUP	const struct group
#endif

EXTERNC_begin

extern int	getgrent_rp(GROUP *,char *,int) noex ;
extern int	getgrnam_rp(GROUP *,char *,int,cchar *) noex ;
extern int	getgrgid_rp(GROUP *,char *,int,gid_t) noex ;

EXTERNC_end

/* GETGRXXXR end */


#endif /* UCSYSGR_INCLUDE */


