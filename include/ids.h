/* ids HEADER */
/* lang=C20 */

/* ID acquisition and stoage */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-23, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	IDS_INCLUDE
#define	IDS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* system types */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	IDS		struct ids_head


struct ids_head {
	gid_t		*gids ;
	uid_t		uid, euid ;
	gid_t		gid, egid ;
} ;

#ifdef	__cplusplus
enum idsmems {
	idsmem_load,
	idsmem_ngroups,
	idsmem_release,
	idsmem_refresh,
	idsmem_overlast
} ;
struct ids ;
struct ids_co {
	ids		*op{} ;
	int		w = -1 ;
	void operator () (ids *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (ids_co) */
struct ids : ids_head {
	ids_co		load ;
	ids_co		ngroups ;
	ids_co		release ;
	ids_co		refresh ;
	ids() noex {
	    load(this,idsmem_load) ;
	    ngroups(this,idsmem_ngroups) ;
	    release(this,idsmem_release) ;
	    refresh(this,idsmem_refresh) ;
	} ;
	ids(const ids &) = delete ;
	ids &operator = (const ids &) = delete ;
	int copy(const ids *) noex ;
	~ids() noex {
	    (void) int(release) ;
	} ;
} ; /* end struct (ids) */
#else	/* __cplusplus */
typedef IDS		ids ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	ids_load(ids *) noex ;
extern int	ids_ngroups(ids *) noex ;
extern int	ids_release(ids *) noex ;
extern int	ids_refresh(ids *) noex ;
extern int	ids_copy(ids *,const ids *) noex ;

EXTERNC_end


#endif /* IDS_INCLUDE */


