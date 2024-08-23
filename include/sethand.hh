/* sethand HEADER */
/* lang=C++98 */

/* SETHAND object */
/* version %I% last-modified %G% */

#define	CF_DEL		1		/* delete */

/* revision history:

	= 1998-12-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object is a container that implements a "set" semantic
	on its entries. The thing that is different is that the
	entries are stored as pointers to the actual entries. This
	allows for entries to be created outside of the container
	and passed around as usch, and then entered into the container
	as may be needed.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstring>
#include	<new>
#include	<utility>
#include	<functional>
#include	<set>
#include	<string>
#include	<stdexcept>
#include	<usystem.h>
#include	<hdb.h>
#include	<localmisc.h>

#include	"returnstatus.h"


#define	SETHAND_DEFENTS	10


extern "C" uint	elfhash(cvoid *,int) noex ;
extern "C" int	strnncmp(cchar *,int,cchar *,int) noex ;

class sethandent {
	int		osize = 0 ;
protected:
	int		kl = 0 ;
	int		vl = 0 ;
	cvoid	*kp = nullptr ;
	cvoid	*vp = nullptr ;
public:
	virtual int	getkey(cvoid **rpp) const {
	    if (rpp != nullptr) *rpp = (cvoid *) kp ;
	    return kl ;
	} ;
	virtual int	getval(cvoid **rpp) const {
	    if (rpp != nullptr) *rpp = (cvoid *) vp ;
	    return vl ;
	} ;
	virtual uint	hash() {
	   int		hv = 0 ;
	   if (kp != nullptr) hv = elfhash(kp,kl) ;
	   return hv ;
	} ;
	virtual int	cmp(sethandent *e1p,sethandent *e2p) {
	    int		rc = 0 ;
	    int		k1l, k2l ;
	    cvoid	*v1p, *v2p ;
	    if ((k1l = e1p->getkey(&v1p)) >= 0) {
	        if ((k2l = e2p->getkey(&v2p)) >= 0) {
	    	    cchar	*c1p = (cchar *) v1p ;
	    	    cchar	*c2p = (cchar *) v2p ;
		    rc = strnncmp(c1p,k1l,c2p,k2l) ;
		}
	    }
	    return rc ;
	} ;
	virtual int	setosize(int aosize) {
	    osize = aosize ;
	    return SR_OK ;
	} ;
	virtual int	getosize() const {
	    return osize ;
	} ;
	sethandent() { } ;
	sethandent(cvoid *akp,int akl,cvoid *avp,int avl) :
	    kl(akl), vl(avl), kp(akp), vp(avp) {
	} ;
	~sethandent() {
	    kp = nullptr ;
	    vp = nullptr ;
	    kl = 0 ;
	    vl = 0 ;
	} ;
} ; /* end class (sethandent) */

class sethand ;

class sethand_it {
	hdb_cur		cur ;
	friend		sethand ;
} ;

class sethand {
	hdb		list ;
	int		f_started = FALSE ;
	int		n = 0 ;
	int		at = 0 ;
public:
	typedef sethand_it iterator ;
	sethand(int an = SETHAND_DEFENTS) : n(an) { } ;
	sethand(int an,int aat) : n(an), at(aat) { } ;
	~sethand() {
	    if (f_started) {
		f_started = FALSE ;
		hdb_finish(&list) ;
	    }
	} ;
	int		begin(int an) {
	    int		rs ;
	    n = an ;
	    if ((rs = hdb_start(&list,n,at,nullptr,nullptr)) >= 0) {
		f_started = TRUE ;
	    }
	    return rs ;
	} ;
	int		begin() {
	    int		rs ;
	    if ((rs = hdb_start(&list,n,at,nullptr,nullptr)) >= 0) {
		f_started = TRUE ;
	    }
	    return rs ;
	} ;
	int		end() {
	    int		rs = SR_OK ;
	    if (f_started) {
		f_started = FALSE ;
		rs = hdb_finish(&list) ;
	    }
	    return rs ;
	} ;
	int		itbegin(sethand_it *itp) {
	    return hdb_curbegin(&list,&itp->cur) ;
	} ;
	int		itend(sethand_it *itp) {
	    return hdb_curend(&list,&itp->cur) ;
	} ;
	int itfetch(sethand_it *itp,sethandent **rpp,cchar *kp,int kl) {
	    hdb_dat	key, val ;
	    hdb_cur	*curp = &itp->cur ;
	    int		rs ;
	    key.buf = kp ;
	    key.len = kl ;
	    if ((rs = hdb_fetch(&list,key,curp,&val)) >= 0) {
		if (rpp != nullptr) *rpp = (sethandent *) val.buf ;
		rs = val.len ;
	    }
	    return rs ;
	} ;
	int itenum(sethand_it *itp,sethandent **rpp) {
	    hdb_dat	key, val ;
	    hdb_cur	*curp = &itp->cur ;
	    int		rs ;
	    if ((rs = hdb_enum(&list,curp,&key,&val)) >= 0) {
		if (rpp != nullptr) *rpp = (sethandent *) val.buf ;
		rs = val.len ;
	    }
	    return rs ;
	} ;
	int add(const sethandent *ep) {
	    cint	os = ep->getosize() ;
	    int		rs = SR_OK ;
	    int		kl ;
	    cvoid	*kp ;
	    if ((kl = ep->getkey(&kp)) >= 0) {
		hdb_dat	key, val ;
		cint	rsn = SR_NOTFOUND ;
		key.buf = kp ;
		key.len = kl ;
		if ((rs = hdb_fetch(&list,key,nullptr,&val)) == rsn) {
		    val.buf = ep ;
		    val.len = os ;
	            if ((rs = hdb_store(&list,key,val)) >= 0) {
			rs = 1 ;
		    }
		}
	    }
	    return rs ;
	} ;
	sethand& operator += (const sethandent *ep) {
	    int	rs = add(ep) ;
	    if (rs < 0) {
		returnstatus a(rs) ;
		throw a ;
	    }
	    return (*this) ;
	} ;
} ; /* end class (sethand) */


