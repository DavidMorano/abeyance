/* mtime HEADER */
/* charset=ISO8859-1 */
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
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<stdint.h>


#ifndef	TYPEDEF_MTIME
#define	TYPEDEF_MTIME
typedef int64_t		mtime_t ;
#endif

#ifndef	SUBROUTINE_UMTIME
#define	SUBROUTINE_UMTIME
EXTERNC_begin
extern mtime_t	umtime(void) noex ;
EXTERNC_end
#endif

#ifndef	OBJECT_GETMTIME
#define	OBJECT_GETMTIME
#ifdef	__cplusplus

struct usys_mtime {
	operator mtime_t () noex {
	    return umtime() ;
	} ;
	static mtime_t operator () () noex {
	    return umtime() ;
	} ;
} ; /* end struct (getustime) */

extern usys_mtime	mtime ;
extern usys_mtime	getmtime ;

#endif /* __cplusplus */
#endif /* OBJECT_GETMTIME */


#endif /* MTIME_INCLUDE */


