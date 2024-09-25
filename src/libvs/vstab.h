/* vstab HEADER */
/* lang=C20 */

/* vector-string structures (Vector String) */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VSTAB_INCLUDE
#define	VSTAB_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	VSTAB		struct vstab_head


struct vstab_head {
	void		**va ;
	int		i ;		/* highest index used so far */
	int		n ;		/* current extent of array */
	int		c ;		/* count of items in list */
	int		osize ;		/* object size */
} ;

typedef	VSTAB		vstab ;

EXTERNC_begin

extern int vstab_start(VSTAB *,int) noex ;
extern int vstab_getfd(VSTAB *,int,void **) noex ;
extern int vstab_getval(VSTAB *,int,void **) noex ;
extern int vstab_getkey(VSTAB *,int,void **) noex ;
extern int vstab_del(VSTAB *,int) noex ;
extern int vstab_count(VSTAB *) noex ;
extern int vstab_search(VSTAB *,cchar *,int (*)(),char **) noex ;
extern int vstab_find(VSTAB *,cchar *) noex ;
extern int vstab_findn(VSTAB *,cchar *,int) noex ;
extern int vstab_finder(VSTAB *,cchar *,int (*)(),char **) noex ;
extern int vstab_getvec(VSTAB *,cvoid ***) noex ;
extern int vstab_audit(VSTAB *) noex ;
extern int vstab_finish(VSTAB *) noex ;

EXTERNC_end


#endif /* VSTAB_INCLUDE */


