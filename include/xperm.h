/* xsperm HEADER */
/* lang=C20 */

/* stat-perm (Status-Permissions) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-05, David A­D­ Morano
	This module was adapted from assembly lanauge.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

	We check for specified permissions on a file given an IDS
	object (for the user to check permissions for) and the
	|stat(2)| of the file in question.

******************************************************************************/

#ifndef	XPERM_INCLUDE
#define	XPERM_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<usystem.h>
#include	<ids.h>
#include	<vecstr.h>


EXTERNC_begin

extern int sperm(ids *,USTAT *,int) noex ;
extern int perm(cchar *,uid_t,gid_t,gid_t *,int) noex ;
extern int fperm(int,uid_t,gid_t,gid_t *,int) noex ;
extern int permsched(mainv,vecstr *,char *,int,cc *,mode_t) noex ;

EXTERNC_end


#endif /* XPERM_INCLUDE */


