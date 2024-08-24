/* li SUPPORT */
/* lang=C++20 */

/* long (64 bit) interger arithmetic object module */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-06, David A­D­ Morano

	This object module was originally written.  There is no
	64-bit native integer support on Sun computers!


*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	li

	Description:
	This is a crude attempt to create some 64 bit integer support
	for machines that do not have it embedded.  Short of a Cray
	or an Amdahl computer, I know of no others at this time
	that natively support 64-bit integer operations.  Have we
	become too dependent on our beloved Amdahls?  This object
	module is a little lean (in terms of the manipulations
	allowed on the object) but it is enough for some crude
	64-bit operations.  Feel free to enhance this object as you
	may like!!  Oh, one last thing.  This code assumes that a
	'long' is 32 bits! If a 'long' ever gets longer I think
	that the code will still work, but then you may as well
	switch to using the longer 'long's themselves!

*******************************************************************************/

#include	<envstandards.h>
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<localmisc.h>

#include	"li.h"


/* local defines */

#define	BIT31(a)	(((a) >> 31) & 1)


/* local structures */


/* forward references */

extern "C" {
    int		li_add3(LI *a,LI *b,LI *c) noex ;
}


/* local structures */


/* exported variables */


/* exported subroutines */

int li_load(LI *a,int a1,int a0) noex {
	a->l = a0 ;
	a->u = a1 ;
	return 0 ;
}
/* end subroutine (li_load) */

int li_store(LI *a,int *a1p,int *a0p) noex {
	*a0p = a->l ;
	*a1p = a->u ;
	return 0 ;
}
/* end subroutine (li_store) */

int li_zero(LI *a) noex {
	a->l = 0 ;
	a->u = 0 ;
	return 0 ;
}
/* end subroutine (li_zero) */

/* add a = b + c */
int li_add3(LI *a,LI *b,LI *c) noex {
	int		f ;
	a->l = b->l + c->l ;
	a->u = b->u + c->u ;
	f = false ;
	f = f || ((BIT31(b->l) || BIT31(c->l)) && (! BIT31(a->l))) ;
	f = f || (BIT31(b->l) && BIT31(c->l)) ;
	if (f) {
	    a->u += 1 ;
	}
	f = false ;
	f = f || ((BIT31(b->u) || BIT31(c->u)) && (! BIT31(a->u))) ;
	f = f || (BIT31(b->u) && BIT31(c->u)) ;
	return f ;
}
/* end subroutine (li_add3) */

/* add a = a + b */
int li_add2(LI *a,LI *b) noex {
	LI	c ;
	c = *a ;
	return li_add3(a,b,&c) ;
}
/* end subroutine (li_add2) */


