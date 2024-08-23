/* emainfo HEADER */
/* lang=C++20 */


/* revision history:

	= 1998-02-12, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	EMAINFO_INCLUDE
#define	EMAINFO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


/* object defines */
#define	EMAINFO		struct emainfo_head

/* other defines */
#define	EMAINFO_TLOCAL		0
#define	EMAINFO_TUUCP		1
#define	EMAINFO_TARPA		2
#define	EMAINFO_TARPAROUTE	3

#define	EMAINFO_LOCALHOST	"*LOCAL*"


struct emainfo_head {
	cchar		*local ;
	cchar		*host ;
	int		type ;
	int		llen ;
	int		hlen ;
} ;

typedef	EMAINFO		emainfo ;

EXTERNC_begin

extern int	emainfo_load(emainfo *,cchar *,int) noex ;
extern int	emainfo_mktype(emainfo *,int,char *,int) noex ;

EXTERNC_end


#endif /* EMAINFO_INCLUDE */


