/* ucenumxx HEADER */
/* lang=C20 */

/* enumerate system SYSDB-XX entries */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-24, David A­D­ Morano
	This object module was morphed from some previous one. I
	do not remember what the previous one was.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	We enumerate (reentrantly and thread safely) system SYSDB-XX
	entries from the system SYSDB-XX database.

*******************************************************************************/

#ifndef	UCENUMXX_INCLUDE
#define	UCENUMXX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<filemap.h>


#define	UCENUMXX	struct ucenumxx_head


struct ucenumxx_head {
	filemap		*fmp ;
	uint		magic ;
} ;

#ifdef	__cplusplus

typedef ucenumxx_head	ucenumxx ;

struct ucenumxxbase : ucenumxx {
	ucenumxx	*op ;
	uint		mxx ;
	int		open(cchar *) noex ;
	int		close() noex ;
	int		reset() noex ;
	ucenumxxbase(ucenumxx *p,uint m) noex : op(p), mxx(m) { } ;
} ; /* end struct (ucenumxxbase) */

template<typename TE>
struct ucenumxxco : ucenumxxbase {
	typedef ucenumxx	eo ;
	ucenumxxco(eo *p,uint m) noex : ucenumxxbase(p,m) { } ;
	int readent(TE *ep,char *bp,int bl) noex {
	    int		rs = SR_FAULT ;
	    int		len = 0 ;
	    if (op && ep && bp) {
	        rs = SR_NOTOPEN ;
	        if (op->magic == mxx) {
		    cchar	*lp ;
		    while ((rs = filemap_getln(op->fmp,&lp)) > 0) {
	    	        rs = ep->parse(bp,bl,lp,rs) ;
	    	        len = rs ;
	    	        if (len > 0) break ;
	    	        if (rs < 0) break ;
		    } /* end while */
	        } /* end if (open) */
	    } /* end if (non-null) */
	    return (rs >= 0) ? len : rs ;
        } ; /* end method (readent) */
} ; /* end struct-template (ucenumxxco) */

#endif /* __cplusplus */


#endif /* UCENUMXX_INCLUDE */


