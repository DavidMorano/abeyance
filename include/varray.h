/* varray HEADER */
/* lang=C20 */

/* object implementing variable-length array of elements */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VARRAY_INCLUDE
#define	VARRAY_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<lookaside.h>


#define	VARRAY		struct varray_head
#define	VARRAY_DEFENTS	10


struct varray_head {
	void		**va ;
	lookaside	*lap ;
	int		esize ;		/* element size */
	int		c ;		/* count of items in array */
	int		n ;		/* extent of array */
	int		imax ;		/* maximum used */
} ;

typedef VARRAY		varray ;

EXTERNC_begin

typedef int (*varray_vcmp)(cvoid **,cvoid **) noex ;

extern int varray_start(varray *,int,int) noex ;
extern int varray_enum(varray *,int,void *) noex ;
extern int varray_acc(varray *,int,void *) noex ;
extern int varray_mk(varray *,int,void *) noex ;
extern int varray_del(varray *,int) noex ;
extern int varray_delall(varray *) noex ;
extern int varray_count(varray *) noex ;
extern int varray_find(varray *,void *) noex ;
extern int varray_search(varray *,void *,varray_vcmp,void *) noex ;
extern int varray_audit(varray *) noex ;
extern int varray_finish(varray *) noex ;

EXTERNC_end


#endif /* VARRAY_INCLUDE */


