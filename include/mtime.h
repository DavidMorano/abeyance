/* mtime HEADER */
/* lang=C20 */

/* Millisecond Time */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MTIME_INCLUDE
#define	MTIME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdint.h>


#ifndef	TYPEDEF_MTIME
#define	TYPEDEF_MTIME
typedef int64_t		mtime_t ;
#endif

#ifndef	SUBROUTINE_MTIME
#define	SUBROUTINE_MTIME
EXTERNC_begin
extern mtime_t	mtime(void) noex ;
EXTERNC_end
#endif

#ifndef	OBJECT_GETMTIME
#define	OBJECT_GETMTIME
#ifdef	__cplusplus

struct usys_mtime {
	operator mtime_t () noex {
	    return mtime() ;
	} ;
	static mtime_t operator () () noex {
	    return mtime() ;
	} ;
} ; /* end struct (getustime) */

extern usys_mtime	getmtime ;

#endif /* __cplusplus */
#endif /* OBJECT_GETMTIME */


#endif /* MTIME_INCLUDE */


