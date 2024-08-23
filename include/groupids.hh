/* groupids HEADER */
/* lang=C++20 */

/* group-ID fetch (UNIX® group-IDs) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-23, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GROUPIDS_INCLUDE
#define	GROUPIDS_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<utypedefs.h>
#include	<clanguage.h>


enum groupidsmems {
	groupidsmem_ngroups,
	groupidsmem_finish,
	groupidsmem_overlast
} ;

struct groupids ;

struct groupids_ster {
	groupids	*op{} ;
	operator int () noex ;
	int operator () (gid_t ** = nullptr) noex ;
	void operator () (groupids *p) {
	    op = p ;
	} ;
} ; /* end struct (groupids_ster) */

struct groupids_co {
	groupids	*op{} ;
	int		w = -1 ;
	void operator () (groupids *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (groupids_co) */

struct groupids {
	groupids_ster	start ;
	groupids_co	ngroups ;
	groupids_co	finish ;
	gid_t		*gids = nullptr ;
	int		ng = 0 ;
	groupids() noex {
	    start(this) ;
	    ngroups(this,groupidsmem_ngroups) ;
	    finish(this,groupidsmem_finish) ;
	} ;
	groupids(const groupids &) = delete ;
	groupids &operator = (const groupids &) = delete ;
	int get(gid_t **) noex ;
	int istart(gid_t **) noex ;
	int ifinish() noex ;
	~groupids() noex {
	    (void) int(finish) ;
	} ;
} ; /* end struct (groupids) */


#endif	/* __cplusplus */
#endif /* GROUPIDS_INCLUDE */


