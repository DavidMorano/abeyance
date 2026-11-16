/* strfilemk HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* STRFILEMK management */
/* version %I% last-modified %G% */

#define	CF_DEBUG	0		/* debugging */

/* revision history:

	- 1998-12-01, David A­D­ Morano
	This module was originally written for hardware CAD support.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strfilemk

	Description:
	This module implements an interface (a trivial one) that
	provides access to the STRFILEMKS object (which is dynamically
	loaded).

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* POSIX® system-types */
#include	<sys/stat.h>		/* POSIX® */
#include	<dlfcn.h>		/* POSIX® */
#include	<unistd.h>		/* POSIX® */
#include	<fcntl.h>		/* POSIX® */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstring>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<ucmem.h>		/* LIBUC */
#include	<vecstr.h>		/* LIBUC */
#include	<modload.h>		/* LIBUC */
#include	<sncpyx.h>		/* LIBUC */
#include	<mkpathx.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */

#include	"strfilemk.h"
#include	"strfilemks.h"

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |memclear(3u)| */

/* local defines */


#define	SFM		strfilemk
#define	SFM_FL		strfilemk_fl
#define	SFM_CA		strfilemk_calls
#define	SFM_MAG		STRFILEMK_MAGIC
#define	SFM_MOD		"strfilemks"
#define	SFM_OBJN	"strfilemks"

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* debugging */
#endif


/* imported namespaces */

using libuc::mem ;			/* variable */


/* local typedefs */

extern "C" {
        typedef int     (*soopen_f)	(void *,cchar *,int,mode_t,int) noex ;
        typedef int     (*soaddfile_f)	(void *,cchar *,int) noex ;
        typedef int     (*socount_f)	(void *) noex ;
        typedef int     (*sochgrp_f)	(void *,gid_t) noex ;
        typedef int     (*soabort_f)	(void *) noex ;
        typedef int     (*soclose_f)	(void *) noex ;
} ; /* end extern (C) */


/* external subroutines */


/* external variables */


/* local structures */

struct strfilemk_calls {
    soopen_f            open ;
    soaddfile_f		addfile ;
    socount_f           count ;
    sochgrp_f           chgrp ;
    soabort_f           abort ;
    soclose_f           close ;
} ; /* end struct (strfilemk_calls) */

typedef strfilemk_calls *	callsp ;


/* forward references */

template<typename ... Args>
local int strfilemk_ctor(SFM *op,Args ... args) noex {
	STRFILEMK	*hop = op ;
	cnullptr	np{} ;
	cnothrow	nt{} ;
	int		rs = SR_FAULT ;
	if (op && (args && ...)) ylikely {
	    memclear(hop) ;
	    rs = SR_NOMEM ;
	    if ((op->mlp = new(nt) modload) != np) ylikely {
		strfilemk_calls    *callp ;
                if ((callp = new(nt) strfilemk_calls) != np) ylikely {
                    op->callp = callp ;
                    rs = SR_OK ;
                } /* end if (new-strfilemk_calls) */
                if (rs < 0) {
                    delete op->mlp ;
                    op->mlp = nullptr ;
                } /* end if (error) */
	    } /* end if (new-modload) */
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (strfilemk_ctor) */

local int strfilemk_dtor(SFM *op) noex {
	int		rs = SR_FAULT ;
	if (op) ylikely {
	    rs = SR_OK ;
            if (op->callp) ylikely {
                strfilemk_calls    *callp = callsp(op->callp) ;
                delete callp ;
                op->callp = nullptr ;
            } /* end if (delete-calls) */
	    if (op->mlp) ylikely {
		delete op->mlp ;
		op->mlp = nullptr ;
	    } /* end if (delete-modload) */
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (strfilemk_dtor) */

template<typename ... Args>
local inline int strfilemk_magic(SFM *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) ylikely {
	    rs = (op->magval == SFM_MAG) ? SR_OK : SR_NOTOPEN ;
	} /* end if */
	return rs ;
} /* end subroutine (strfilemk_magic) */

local int	strfilemk_objloadbegin	(SFM *,cchar *,cchar *) noex ;
local int	strfilemk_objloadend	(SFM *) noex ;
local int	strfilemk_loadcalls	(SFM *,vecstr *) noex ;

local bool	isrequired(int) noex ;


/* local variables */

enum subs {
	sub_open,
	sub_addfile,
	sub_count,
	sub_chgrp,
	sub_abort,
	sub_close,
	sub_overlast
} ; /* end enum */

namespace {
    struct subnamer {
	cchar		*n[sub_overlast + 1] = {} ;
        consteval subnamer() noex {
	    n[sub_open]		= "open" ;
	    n[sub_addfile]	= "addfile" ;
	    n[sub_count]	= "count" ;
	    n[sub_chgrp]	= "chgrp" ;
	    n[sub_abort]	= "abort" ;
	    n[sub_close]	= "close" ;
	    n[sub_overlast]	= nullptr ;
	} ; /* end ctor */
    } ; /* end struct (subnamer) */
} /* end namespace */

static subnamer		subname ;
cbool                   f_debug         = CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int strfilemk_open(SFM *op,cc *dbn,int of,mode_t om,int n) noex {
	int		rs ;
        if ((rs = strfilemk_ctor(op,dbn)) >= 0) ylikely {
	    cchar	*pr = nullptr ;
            cchar       *objname = SFM_OBJN ;
            if (pr[0] && dbn[0]) ylikely {
                if ((rs = strfilemk_objloadbegin(op,pr,objname)) >= 0) ylikely {
                    strfilemk_calls *callp = callsp(op->callp) ;
                    rs = SR_NOSYS ;
                    if (cauto co = callp->open ; co) ylikely {
                        if ((rs = co(op->obj,dbn,of,om,n)) >= 0) ylikely {
                            op->magval = SFM_MAG ;
                        }
                    } /* end if (non-null) */
                    if (rs < 0) {
                        strfilemk_objloadend(op) ;
                    } /* end if (error) */
                } /* end if (objload-begin) */
            } /* end if (valid) */
            if (rs < 0) {
                strfilemk_dtor(op) ;
            } /* end if (error) */
        } /* end if (strfilemk_ctor) */
	return rs ;
} /* end subroutine (strfilemk_open) */

int strfilemk_close(SFM *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = strfilemk_magic(op)) >= 0) {
            rs = SR_BUGCHECK ;
            if (strfilemk_calls *callp = callsp(op->callp) ; callp) ylikely {
                rs = SR_OK ;
                if (cauto co = callp->close ; co) ylikely {
                    rs1 = co(op->obj) ;
                    if (rs >= 0) rs = rs1 ;
                } else {
                    rs = SR_NOSYS ;
                } /* end */
                {
                    rs1 = strfilemk_objloadend(op) ;
                    if (rs >= 0) rs = rs1 ;
                } /* end */
                {
                    rs1 = strfilemk_dtor(op) ;
                    if (rs >= 0) rs = rs1 ;
                } /* end */
                op->magval = 0 ;
            } /* end if (valid) */
	} /* end if (strfilemk_magic) */
	return rs ;
} /* end subroutine (strfilemk_close) */

int strfilemk_addfile(SFM *op,cchar *sp,int sl) noex {
	int		rs ;
	if ((rs = strfilemk_magic(op,sp)) >= 0) {
            strfilemk_calls   *callp = callsp(op->callp) ;
            if (cauto co = callp->addfile ; co) ylikely {
                rs = co(op->obj,sp,sl) ;
	    }
	} /* end if (strfilemk_magic) */
	return rs ;
} /* end subroutine (strfilemk_addfile) */

int strfilemk_count(SFM *op) noex {
        int             rs ;
        if ((rs = strfilemk_magic(op)) >= 0) ylikely {
            strfilemk_calls   *callp = callsp(op->callp) ;
	    rs = SR_NOSYS ;
            if (cauto co = callp->count ; co) ylikely {
                rs = co(op->obj) ;
            }
        } /* end if (strfilemk_magic) */
        return rs ;
} /* end subroutine (strfilemk_count) */

int strfilemk_chgrp(SFM *op,gid_t gid) noex {
	int		rs ;
	if ((rs = strfilemk_magic(op)) >= 0) {
            strfilemk_calls   *callp = callsp(op->callp) ;
	    rs = SR_NOSYS ;
            if (cauto co = callp->chgrp ; co) ylikely {
                rs = co(op->obj,gid) ;
            }
	} /* end if (strfilemk_magic) */
	return rs ;
} /* end subroutine (strfilemk_chgrp) */

int strfilemk_abort(SFM *op) noex {
	int		rs ;
	if ((rs = strfilemk_magic(op)) >= 0) {
            strfilemk_calls   *callp = callsp(op->callp) ;
	    rs = SR_NOSYS ;
            if (cauto co = callp->abort ; co) ylikely {
                rs = co(op->obj) ;
            }
	} /* end if (strfilemk_magic) */
	return rs ;
} /* end subroutine (strfilemk_abort) */


/* private subroutines */

local int strfilemk_objloadbegin(SFM *op,cchar *pr,cchar *objn) noex {
	modload		*mlp = op->mlp ;
	cint		vn = sub_overlast ;
	cint		vo = vecstrm.compact ;
	int		rs ;
	int		rs1 ;
	if (vecstr syms ; (rs = syms.start(vn,vo)) >= 0) ylikely {
	    if ((rs = syms.addsyms(objn,subname.n)) >= 0) ylikely {
	        if (mainv sv ; (rs = syms.getvec(&sv)) >= 0) ylikely {
	            cchar	*mn = SFM_MOD ;
	            cchar	*on = objn ;
	            int		mo = 0 ;
	            mo |= modloadm.libvar ;
	            mo |= modloadm.libprs ;
	            mo |= modloadm.libsdirs ;
	            mo |= modloadm.avail ;
	            if ((rs = modload_open(mlp,pr,mn,on,mo,sv)) >= 0) ylikely {
		        op->fl.modload = true ;
	                if (int mv[2] ; (rs = modload_getmva(mlp,mv,2)) >= 0) {
			    cint	osz = mv[0] ;
	                    op->objsz = mv[0] ;
	                    op->cursz = mv[1] ;
			    if (void *vp ; (rs = mem.mall(osz,&vp)) >= 0) {
	                        op->obj = vp ;
	                        rs = strfilemk_loadcalls(op,&syms) ;
	                        if (rs < 0) {
	                            mem.free(op->obj) ;
	                            op->obj = nullptr ;
	                        } /* end if (error) */
	                    } /* end if (memory-allocation) */
	                } /* end if (modload_getmva) */
	                if (rs < 0) {
		            op->fl.modload = false ;
	                    modload_close(mlp) ;
	                } /* end if (error) */
	            } /* end if (modload_open) */
		} /* end if (vecstr_getvec) */
	    } /* end if (vecstr_addsyms) */
	    rs1 = syms.finish ;
	    if (rs >= 0) rs = rs1 ;
	    if ((rs < 0) && op->fl.modload) {
		op->fl.modload = false ;
		modload_close(mlp) ;
	    } /* end if (error) */
	} /* end if (vecstr-syms) */
	return rs ;
} /* end subroutine (strfilemk_objloadbegin) */

local int strfilemk_objloadend(SFM *op) noex {
	int		rs = SR_OK ;
	int		rs1 ;
	if (op->obj) {
	    rs1 = mem.free(op->obj) ;
	    if (rs >= 0) rs = rs1 ;
	    op->obj = nullptr ;
	} /* end if (memory-release) */
	if (op->mlp && op->fl.modload) {
	    op->fl.modload = false ;
	    rs1 = modload_close(op->mlp) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if */
	return rs ;
} /* end subroutine (strfilemk_objloadend) */

local int strfilemk_loadcalls(SFM *op,vecstr *slp) noex {
	modload		*mlp = op->mlp ;
	cint		rsn = SR_NOTFOUND ;
	int		rs = SR_OK ;
	int		rs1 ;
	int		c = 0 ;
	cchar		*sname{} ;
	for (int i = 0 ; (rs1 = slp->get(i,&sname)) >= 0 ; i += 1) ylikely {
	    if (cvoid *snp{} ; (rs = modload_getsym(mlp,sname,&snp)) >= 0) {
                strfilemk_calls   *callp = callsp(op->callp) ;
                c += 1 ;
                switch (i) {
                case sub_open:
                    callp->open		= soopen_f(snp) ;
                    break ;
                case sub_chgrp:
                    callp->chgrp	= sochgrp_f(snp) ;
                    break ;
                case sub_addfile:
                    callp->addfile	= soaddfile_f(snp) ;
                    break ;
                case sub_count:
                    callp->count	= socount_f(snp) ;
                    break ;
                case sub_abort:
                    callp->abort	= soabort_f(snp) ;
                    break ;
                case sub_close:
                    callp->close	= soclose_f(snp) ;
                    break ;
                } /* end switch */
            } else if (rs == rsn) {
                if (! isrequired(i)) rs = SR_OK ;
            } /* end if (it had the call) */
	    if (rs < 0) break ;
	} /* end for (vecstr_get) */
	if ((rs >= 0) && (rs1 != rsn)) rs = rs1 ;
	return (rs >= 0) ? c : rs ;
} /* end subroutine (strfilemk_loadcalls) */

local bool isrequired(int i) noex {
	bool		f = false ;
	switch (i) {
	case sub_open:
	case sub_addfile:
	case sub_close:
	    f = true ;
	    break ;
	} /* end switch */
	return f ;
} /* end subroutine (isrequired) */


