/* langstate SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++11 */

/* Language (parse) State (object) */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-06-29, David A­D­ Morano
	This was really made from scratch, but was inspired by
	previous code of a similar nature, dating back a long time
	(likely to the 1980s).  Various programs that I have made
	over the earlier decades (of my career) have used code like
	this object (but that previous code was not objectified).

	= 2016-06-29, David A­D­ Morano
	I updated this to add the C++11 'noexcept' where appropriate.

	= 2017-10-19, David A­D­ Morano
	Enhanced to ignore characters within character literals.

*/

/* Copyright © 2008,2016,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	langstate

	Description:
	This object is used to track the parse state of C-language
	type source text.

	Notes:
	1. The subroutine (member function) |langstate_procln()|
	is really quite useless.  The reason is because a partcially
	"clear" line, a line that has both comments (or literals)
	and no special state, is not really usefull for practivally
	anything.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<ascii.h>
#include	<mkchar.h>
#include	<localmisc.h>

#include	"langstate.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |memclear(3u)| */

/* local defines */


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

namespace {
    class item {
	int		ln ;		/* line number */
	int		it ;		/* 0=opening, 1=closing */
    public:
	item(int aln,int ait) noex : ln(aln), it(ait) { } ;
	int type() const noex { 
	    return it ; 
	} ;
	int line() const noex { 
	    return ln ; 
	} ;
    } ; /* end struct (item) */
} /* end namespace */


/* forward references */

template<typename ... Args>
static int langstate_ctor(langstate *op,Args ... args) noex {
    	LANGSTATE	*hop = op ;
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = memclear(hop) ; /* dangerous */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (langstate_ctor) */

static int langstate_dtor(langstate *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (langstate_dtor) */

template<typename ... Args>
static int langstate_magic(langstate *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == LANGSTATE_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (langstate_magic) */


/* local variables */


/* exported variables */


/* exported subroutines */

int langstate_start(langstate *op) noex {
	int		rs ;
	if ((rs = langstate_ctor(op)) >= 0) {
	    op->fl.clear = true ;
	    op->magic = LANGSTATE_MAGIC ;
	    if (rs < 0) {
		langstate_dtor(op) ;
	    }
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (langstate_start) */

int langstate_finish(langstate *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = langstate_magic(op)) >= 0) {
	    {
		rs1 = langstate_dtor(op) ;
		if (rs >= 0) rs = rs1 ;
	    }
	    op->magic = 0 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (langstate_finish) */

int langstate_proc(langstate *op,int ln,int ch) noex {
	int		rs ;
	int		f = false ; /* return-value */
	if ((rs = langstate_magic(op)) >= 0) {
	    f = op->fl.clear ;
	    if (op->fl.comment) {
	        if ((op->pch == CH_STAR) && (ch == CH_SLASH)) {
		    op->fl.comment = false ;
		    op->fl.clear = true ;
		    op->line = 0 ;
	        }
	    } else if (op->fl.quote) {
	        if (op->fl.skip) {
		    op->fl.skip = false ;
	        } else {
		    if (ch == CH_BSLASH) {
		        op->fl.skip = true ;
	            } else if (ch == CH_DQUOTE) {
		        op->fl.quote = false ;
		        op->fl.clear = true ;
		        op->line = 0 ;
		    }
	        }
	    } else if (op->fl.literal) {
	        if (op->fl.skip) {
		    op->fl.skip = false ;
	        } else {
		    if (ch == CH_BSLASH) {
		        op->fl.skip = true ;
	            } else if (ch == CH_SQUOTE) {
		        op->fl.literal = false ;
		        op->fl.clear = true ;
		        op->line = 0 ;
		    }
	        }
	    } else {
	        switch (ch) {
	        case CH_STAR:
		    if (op->pch == CH_SLASH) {
		        op->fl.comment = true ;
		        op->fl.clear = false ;
		        op->line = ln ;
		        f = false ;
		    }
		    break ;
	        case CH_DQUOTE:
		    if ((op->pch != CH_BSLASH) && (op->pch != CH_SQUOTE)) {
		        op->fl.quote = true ;
		        op->fl.clear = false ;
		        op->line = ln ;
		        f = false ;
		    }
		    break ;
	        case CH_SQUOTE:
		    if (op->pch != CH_BSLASH) {
		        op->fl.literal = true ;
		        op->fl.clear = false ;
		        op->line = ln ;
		        f = false ;
		    }
		    break ;
	        } /* end switch */
	    } /* end if */
	    op->pch = ch ;
	} /* end if (langstate_magic) */
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (langstate_proc) */

int langstate_procln(langstate *op,int ln,cchar *lp,int ll) noex {
	int		rs ;
	int		f = false ; /* return-value */
	if ((rs = langstate_magic(op,lp)) >= 0) {
	    while (ll && *lp) {
		cint ch = mkchar(*lp) ;
		if ((rs = langstate_proc(op,ln,ch)) > 0) {
		    if (!f) f = true ;
		}
		if (rs < 0) break ;
	    } /* end while */
	} /* end if (magic) */
	return (rs >= 0) ? f : rs ;
} /* end subroutine (langstate_procln) */

int langstate_getstat(langstate *op,langstate_info *sbp) noex {
	int		rs ;
	int		type = langstatetype_clear ;
	if ((rs = langstate_magic(op,sbp)) >= 0) {
	    memclear(sbp) ; /* dangerous */
	    sbp->line = op->line ;
	    if (op->fl.comment) {
	        type = langstatetype_comment ;
	    } else if (op->fl.quote) {
	        type = langstatetype_quote ;
	    } else if (op->fl.literal) {
	        type = langstatetype_literal ;
	    }
	    sbp->type = type ;
	} /* end if (magic) */
	return (rs >= 0) ? type : rs ;
}
/* end subroutine (langstate_getstat) */

int langstate_code(langstate *op) noex {
	int		rs ;
	int		f = false ;
	if ((rs = langstate_magic(op)) >= 0) {
	    f = op->fl.clear || op->fl.quote || op->fl.literal ;
	} /* end if (magic) */
	return (rs >= 0) ? f : rs ;
} /* end subroutine (langstate_code) */


/* local subroutines */

int langstate::proc(int ln,int ch) noex {
	return langstate_proc(this,ln,ch) ;
}

int langstate::procln(int ln,cchar *lp,int ll) noex {
	return langstate_procln(this,ln,lp,ll) ;
}

int langstate::getstat(langstate_info *sbp) noex {
	return langstate_getstat(this,sbp) ;
}

void langstate::dtor() noex {
	if (cint rs = finish ; rs < 0) {
	    ulogerror("langstate",rs,"fini-finish") ;
	}
} /* end method (langstate::dtor) */

langstate::operator int () noex {
    	int		rs ;
	if ((rs = langstate_magic(this)) >= 0) {
	    rs = line ;
	}
	return rs ;
} /* end method (langstate::operator) */

langstate_co::operator int () noex {
	int		rs = SR_BUGCHECK ;
	if (op) {
	    switch (w) {
	    case langstatemem_start:
	        rs = langstate_start(op) ;
	        break ;
	    case langstatemem_finish:
	        rs = langstate_finish(op) ;
	        break ;
	    case langstatemem_code:
	        rs = langstate_code(op) ;
	        break ;
	    } /* end switch */
	} /* end if (non-null) */
	return rs ;
} /* end method (langstate_co::operator) */


