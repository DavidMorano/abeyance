/* acltypes HEADER */
/* lang=C++20 */

/* ACL types (types of ACLs) */
/* version %I% last-modified %G% */


/* revision history:

	= 2005-02-24, David A­D­ Morano
        This was created along w/ the '.c' file.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ACLTYPES_INCLUDE
#define	ACLTYPES_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	ACLTYPES	struct acltypes


enum acltypes {
	acltype_user,
	acltype_group,
	acltype_other,
	acltype_mask,
	acltype_defuser,
	acltype_defgroup,
	acltype_defother,
	acltype_defmask,
	acltype_overlast
} ;


EXTERNC_begin

extern int	getacltype(cchar *,int) noex ;

EXTERNC_end


#endif /* ACLTYPES_INCLUDE */


