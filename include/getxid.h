/* getxid HEADER */
/* lang=C20 */

/* get certain system IDs based on a specified name */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-08-20, David A­D­ Morano
	This was written to collect this code into one subroutine.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETXID_INCLUDE
#define	GETXID_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int	getuid_name(cchar *,int) noex ;
extern int	getuid_user(cchar *,int) noex ;
extern int	getgid_name(cchar *,int) noex ;
extern int	getgid_group(cchar *,int) noex ;
extern int	getgid_def(cchar *,gid_t) noex ;
extern int	getpjid_name(cchar *,int) noex ;
extern int	getpjid_proj(cchar *,int) noex ;
extern int	getpjid_def(cchar *,projid_t) noex ;

EXTERNC_end


#endif /* GETXID_INCLUDE */


