/* malloclog HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* malloc logging */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MALLOCLOG_INCLUDE
#define	MALLOCLOG_INCLUDE


#include	<envstandards.h>
#include	<stdint.h>
#include	<usystem.h>


EXTERNC_begin

extern void	malloclog_alloc(cvoid *,int,cchar *) noex ;
extern void	malloclog_free(cvoid *,cchar *) noex ;
extern void	malloclog_realloc(cvoid *,cvoid *,int,cchar *) noex ;
extern void	malloclog_mark() noex ;
extern void	malloclog_dump() noex ;
extern void	malloclog_clear() noex ;
extern int	malloclog_printf(cchar *,...) noex ;

EXTERNC_end


#endif /* MALLOCLOG_INCLUDE */


