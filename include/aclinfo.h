/* aclinfo HEADER */
/* lang=C20 */

/* ACL information */
/* version %I% last-modified %G% */


/* Copyright © 2005 David A­D­ Morano.  All rights reserved. */

#ifndef	ACLINFO_INCLUDE
#define	ACLINFO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* system types */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<clanguage.h>
#include	<localmisc.h>

#include	"acltypes.h"


#define	ACLINFO		struct aclinfo_head


struct aclinfo {
	uid		uid ;
	gid		gid ;
	int		type ;
	int		soltype ;
	int		op ;		/* add or subtract */
	int		perm ;		/* permission bits */
} ;

typedef ACLINFO		aclinfo ;

EXTERNC_begin

extern int	aclinfo_mksol(aclinfo *) noex ;
extern int	aclinfo_isdeftype(aclinfo *) noex ;
extern int	aclinfo_isidtype(aclinfo *) noex ;

EXTERNC_end


#endif /* ACLINFO_INCLUDE */


