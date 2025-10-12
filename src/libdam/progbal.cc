/* progbal SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* program character balance */
/* version %I% last-modified %G% */


/* revision history:

	= 2016-02-01, David A­D­ Morano
	This was really made from scratch.

*/

/* Copyright © 2016 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	progbal

	Description:
	We determine if the character balance in the input (given
	a piece at a time) is correct or not.

		progbal_start
		progbal_load
		progbal_finish

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<vector>
#include	<new>
#include	<usystem.h>
#include	<six.h>			/* |sochr(3uc)| */
#include	<ascii.h>
#include	<mkchar.h>
#include	<ischarx.h>
#include	<localmisc.h>

#include	"progbal.h"


/* local defines */


/* namespaces */

using namespace		std ;		/* yes, we want punishment! */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */

static cchar	chopen[] = { CH_LPAREN, CH_LBRACE, CH_LBRACK, '\0' } ;
static cchar	chclose[] = { CH_RPAREN, CH_RBRACE, CH_RBRACK, '\0' } ;


/* exported variables */


/* exported subroutines */

int progbal_start(PROGBAL *op) {
	int		rs = SR_OK ;

	if (op == NULL) return SR_FAULT ;

	memset(op,0,sizeof(PROGBAL)) ;

	return rs ;
}
/* end subroutine (progbal_start) */

/* returns if all of the input was balanced */
int progbal_finish(PROGBAL *op) {
	int		rs = SR_OK ;
	int		f_bal ;

	if (op == NULL) return SR_FAULT ;

	if (op->magic != PROGBAL_MAGIC) return SR_NOTOPEN ;

	f_bal = (!op->f_fail) ;
	if (f_bal) {
	    int	i ;
	    for (i = 0 ; i < PROGBAL_NCH ; i += 1) {
		f_bal = (op->counts[i] == 0) ;
		if (!f_bal) break ;
	    } /* end for */
	}

	op->magic = 0 ;
	return (rs >= 0) ? f_bal : rs ;
}
/* end subroutine (progbal_finish) */

int progbal_load(PROGBAL *op,cchar *sp,int sl) {
	int		rs = SR_OK ;
	int		f_fail = FALSE ;

#if	CF_DEBUGS
	debugprintf("progbal_load: ent\n") ;
#endif

	if (op == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

	if (op->magic != PROGBAL_MAGIC) return SR_NOTOPEN ;

	if (sl < 0) sl = strlen(sp) ;

	while (sl-- && *sp) {
	    cint	ch = MKCHAR(*sp++) ;
	    int		w ;
	    switch (ch) {
	    case CH_LPAREN:
	    case CH_LBRACE:
	    case CH_LBRACK:
		w = sichr(chopen,-1,ch) ;
		op->counts[w] += 1 ;
		break ;
	    case CH_RPAREN:
	    case CH_RBRACE:
	    case CH_RBRACK:
		w = sichr(chclose,-1,ch) ;
		if (op->counts[w] > 0) {
		    op->counts[w] -= 1 ;
		} else {
		    f_fail = TRUE ;
		}
		break ;
	    } /* end switch */
	    if (f_fail) break ;
	} /* end while */

	return rs ;
}
/* end subroutine (progbal_load) */


/* private subroutines */


