/* splitfname HEADER */
/* lang=C20 */

/* split a file-name into its 'dirname" and its 'basename' */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SPLITFNAME_INCLUDE
#define	SPLITFNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	SPLITFNAME	struct splitfname_head


struct splitfname_head {
	cchar		*dp ;
	cchar		*bp ;
	int		dl ;
	int		bl ;
} ;

#ifdef	__cplusplus
struct splitfname : splitfname_head {
	splitfname() noex : splitfname_head{} { } ;
	splitfname(const splitfname &) = delete ;
	splitfname &operator = (const splitfname &) = delete ;
	int operator () (cchar *,int = -1) noex ;
} ; /* end struct (splitfname) */
#else /* __cplusplus */
typedef SPLITFNAME		splitfname ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	splitfname_split(splitfname *,cchar *,int) noex ;

EXTERNC_end


#endif /* SPLITFNAME_INCLUDE */


