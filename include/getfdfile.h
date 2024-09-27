/* getfdfile HEADER */
/* lang=C20 */

/* try to divine a file-descriptor out of a file-name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-23, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETFDFILE_INCLUDE
#define	GETFDFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#ifndef	FD_STDIN
#define	FD_STDIN	0
#endif
#ifndef	FD_STDOUT
#define	FD_STDOUT	1
#endif
#ifndef	FD_STDERR
#define	FD_STDERR	2
#endif
#ifndef	FD_STDLOG
#define	FD_STDLOG	3
#endif


EXTERNC_begin

extern int getfdfilex(cchar *,int) noex ;

EXTERNC_end

#ifdef	__cplusplus

static inline int getfdfile(cchar *sp,int sl = -1) {
	return getfdfilex(sp,sl) ;
}

#else /* __cplusplus */

static inline int getfdfile(cchar *sp,int sl) {
	return getfdfilex(sp,sl) ;

#endif /* __cplusplus */


#endif /* GETFDFILE_INCLUDE */


