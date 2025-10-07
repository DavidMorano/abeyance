/* langproc SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* computer-language text processor */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */

/* revision history:

	= 2016-06-29, David A­D­ Morano
	This was really made from scratch.

*/

/* Copyright © 2016 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	langproc

	Names:
	langproc_start
	langproc_proc
	langproc_count
	langproc_curbegin
	langproc_curend
	langproc_curenum
	langproc_finish

	Description:
	This object both processes lines and remembers any lines
	that meet a certain criteria.  I Process characters (a line
	at a time) for balanced pairs.  I record line numbers so
	that when we are left with some sort of unbalance, we can
	report the associated line numbers.

	Dependencies:
	langstate

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<new>			/* |nothrow(3c++)| */
#include	<vector>
#include	<string>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<strnul.hh>
#include	<ascii.h>		/* |CH_SP| */
#include	<mkchar.h>
#include	<localmisc.h>

#include	"langproc.h"

#pragma		GCC dependency		"mod/libutil.ccm"
#pragma		GCC dependency		"mod/ureserve.ccm"
#pragma		GCC dependency		"mod/debug.ccm"

import libutil ;			/* |resumelife(3u)| */
import ureserve ;			/* |vecstr(3u)| */
import debug ;

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif


/* imported namespaces */

using std::string ;			/* type */
using std::nothrow ;			/* constant */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

template<typename ... Args>
local int langproc_ctor(langproc *op,Args ... args) noex {
    	cnothrow	nt{} ;
	cnullptr	np{} ;
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = SR_NOMEM ;
	    op->magic = 0 ;
	    op->lvp = nullptr ;
	    if (langstate *lsp ; (lsp = new(nt) langstate) != np) {
		op->lsp = lsp ;
		if (vecstr *lvp ; (lvp = new(nt) vecstr) != np) {
		    op->lvp = lvp ;
		    rs = SR_OK ;
		}
		if (rs < 0) {
		    delete lsp ;
		    op->lsp = nullptr ;
		}
	    } /* end if (new-langstate) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (langproc_ctor) */

local int langproc_dtor(langproc *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	    if (op->lvp) {
		vecstr *lvp = resumelife<vecstr>(op->lvp) ;
		delete lvp ;
		op->lvp = nullptr ;
	    }
	    if (op->lsp) {
		delete op->lsp ;
		op->lsp = nullptr ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (langproc_dtor) */

template<typename ... Args>
local inline int langproc_magic(langproc *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == LANGPROC_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (langproc_magic) */


/* local variables */

cbool		f_debug = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int langproc_start(langproc *op) noex {
	int		rs ;
	if ((rs = langproc_ctor(op)) >= 0) {
	    if ((rs = langstate_start(op->lsp)) >= 0) {
		vecstr *lvp = resumelife<vecstr>(op->lvp) ;
		if ((rs = lvp->start) >= 0) {
		    op->magic = LANGPROC_MAGIC ;
		}
		if (rs < 0) {
		    langstate_finish(op->lsp) ;
		}
	    } /* end if (langstate_start) */
	    if (rs < 0) {
		langproc_dtor(op) ;
	    }
	} /* end if (langproc_ctor) */
	return rs ;
}
/* end subroutine (langproc_start) */

int langproc_finish(langproc *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = langproc_magic(op)) >= 0) {
	    if (op->lvp) {
		vecstr *lvp = resumelife<vecstr>(op->lvp) ;
	        delete lvp ;
	        op->lvp = nullptr ;
	    }
	    if (op->lsp) {
	        rs1 = langstate_finish(op->lsp) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    {
		rs1 = langproc_dtor(op) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    op->magic = 0 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (langproc_finish) */

int langproc_proc(langproc *op,int ln,cchar *sp,int sl) noex {
	cnullptr	np{} ;
	int		rs ;
	int		c = 0 ; /* return-value */
	if_constexpr (f_debug) {
	    strnul s(sp,sl) ;
	    debprintf(__func__,"ent ln=%d s=>%s<\n",ln,ccp(s)) ;
	}
	if ((rs = langproc_magic(op,sp)) >= 0) {
	    rs = SR_BUGCHECK ;
	    if (vecstr *lvp ; (lvp = resumelife<vecstr>(op->lvp)) != np) {
		langstate *lsp = op->lsp ;
		string	tmp ;
		bool	frm = false ;
		rs = SR_OK ;
	        while ((rs >= 0) && sl && *sp) {
		    cint	ch = mkchar(*sp) ;
		    if ((rs = lsp->proc(ln,ch)) >= 0) {
			if ((rs = lsp->code) > 0) {
			    try {
			        if (frm) {
			            tmp += char(CH_SP) ;
			            c += 1 ;
				    frm = false ;
			        } /* end if (previous non-clear) */
			        tmp += char(ch) ;
			        c += 1 ;
			    } catch (...) {
			        rs = SR_NOMEM ;
			    }
			} else if (rs == 0) {
			    frm = true ;
			} /* end if */
		    } else if (rs == 0) {
			frm = true ;
		    } /* end if (langstate_proc) */
		    sp += 1 ;
		    sl -= 1 ;
	        } /* end while */
		if ((rs >= 0) && (c > 0)) {
		    rs = lvp->add(&tmp) ;
		}
	    } /* end if (vecstr) */
	} /* end if (magic) */
	if_constexpr (f_debug) {
	    debprintf(__func__,"ret rs=%d c=%d\n",rs,c) ;
	}
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (langproc_proc) */

int langproc_count(langproc *op) noex {
	cnullptr	np{} ;
	int		rs ;
	int		c = 0 ; /* return-value */
	if ((rs = langproc_magic(op)) >= 0) {
	    rs = SR_BUGCHECK ;
	    if (vecstr *lvp ; (lvp = resumelife<vecstr>(op->lvp)) != np) {
	        rs = lvp->count ;
		c = rs ;
	    }
	} /* end if (magic) */
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (langproc_count) */

int langproc_curbegin(langproc *op,langproc_cur *curp) noex {
	int		rs ;
	if ((rs = langproc_magic(op,curp)) >= 0) {
	    curp->i = -1 ;
	} /* end if (magic) */
	return rs ;
} /* end subroutine (langproc_curbegin) */

int langproc_curend(langproc *op,langproc_cur *curp) noex {
	int		rs ;
	if ((rs = langproc_magic(op,curp)) >= 0) {
	    curp->i = -1 ;
	} /* end if (magic) */
	return rs ;
} /* end subroutine (langproc_curend) */

int langproc_curenum(langproc *op,langproc_cur *curp,cchar **rpp) noex {
	cnullptr	np{} ;
	int		rs ;
	int		len = 0 ; /* return-value */
	if ((rs = langproc_magic(op,curp,rpp)) >= 0) {
	    rs = SR_BUGCHECK ;
	    if_constexpr (f_debug) {
	        debprintf(__func__,"check\n") ;
	    }
	    if (vecstr *lvp ; (lvp = resumelife<vecstr>(op->lvp)) != np) {
		cint	idx = (curp->i >= 0) ? (curp->i + 1) : 0 ;
	        if_constexpr (f_debug) {
	            debprintf(__func__,"-> get()\n") ;
		}
		if (cchar *cp ; (rs = lvp->get(idx,&cp)) >= 0) {
		    *rpp = cp ;
		    len = lenstr(cp) ;
		    curp->i = idx ;
		}
	    } /* end if (non-null) */
	    if_constexpr (f_debug) {
	        debprintf(__func__,"check rs=%d\n",rs) ;
	    }
	} /* end if (magic) */
	if_constexpr (f_debug) {
	    debprintf(__func__,"ret rs=%d len=%d\n",rs,len) ;
	}
	return (rs >= 0) ? len : rs ;
}
/* end subroutine (langproc_curenum) */


/* local subroutines */

int langproc::proc(int ln,cchar *sp,int sl) noex {
	return langproc_proc(this,ln,sp,sl) ;
}

int langproc::curbegin(langproc_cur *curp) noex {
	return langproc_curbegin(this,curp) ;
}

int langproc::curend(langproc_cur *curp) noex {
	return langproc_curend(this,curp) ;
}

int langproc::curenum(langproc_cur *curp,cchar **rpp) noex {
	return langproc_curenum(this,curp,rpp) ;
}

void langproc::dtor() noex {
	if (cint rs = finish ; rs < 0) {
	    ulogerror("langproc",rs,"fini-finish") ;
	}
} /* end method (langproc::dtor) */

langproc::operator int () noex {
    	return langproc_count(this) ;
} /* end method (langproc::operator) */

langproc_co::operator int () noex {
	int		rs = SR_BUGCHECK ;
	if (op) {
	    switch (w) {
	    case langprocmem_start:
	        rs = langproc_start(op) ;
	        break ;
	    case langprocmem_finish:
	        rs = langproc_finish(op) ;
	        break ;
	    case langprocmem_count:
	        rs = langproc_count(op) ;
	        break ;
	    } /* end switch */
	} /* end if (non-null) */
	return rs ;
} /* end method (langproc_co::operator) */


