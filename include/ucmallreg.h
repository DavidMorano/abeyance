/* ucmallreg HEADER */
/* lang=C20 */

/* support object for UNIX® C-language library Memory-Allocation management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This include provides the array indices for accessing the
	various memory-allocation information elements.

*******************************************************************************/

#ifndef	UCMALLREG_INCLUDE
#define	UCMALLREG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define		UCMALLREG_CUR	struct ucmallreg_cursor
#define		UCMALLREG_ENT	struct ucmallreg_entry


struct ucmallreg_cursor {
	void		*mcp ;		/* Mall-Cursor-Pointer */
} ;

struct ucmallreg_entry {
	caddr_t		addr ;
	size_t		asize ;
} ;

typedef	UCMALLREG_CUR	ucmallreg_cur ;
typedef	UCMALLREG_ENT	ucmallreg_ent ;

EXTERNC_begin

extern int ucmallreg_curbegin(ucmallreg_cur *) noex ;
extern int ucmallreg_curend(ucmallreg_cur *) noex ;
extern int ucmallreg_curenum(ucmallreg_cur *,ucmallreg_ent *) noex ;

EXTERNC_end


#endif /* UCMALLREG_INCLUDE */


