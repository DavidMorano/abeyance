/* ctfield SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* subroutines to parse a line into ctfields */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-07-01, David A­D­ Morano
	This code module was originally written in C language copied
	(roughly) from a prior VAX® assembly language version (circa
	1980 perhaps).  This is why is looks so "ugly"!

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	ctfield

	Description:
	The arguments to this routine are:

	- address of return status block
	- address of terminator block


	The function return is:
	>=0	length of ctfield just parsed out (length of CTFIELD!)
	<0	invalid ctfield block pointer was passwd

	The return status block outputs are:
	- length remaining in string
	- address of reminaing string
	- len of substring
	- address of substring
	- terminator character

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<ascii.h>
#include	<baops.h>
#include	<char.h>
#include	<localmisc.h>

#include	"ctfield.h"


/* local defines */

/* quote characters '\"' and '\'' */
constexpr char		quotes[] = {
	0x00, 0x00, 0x00, 0x00,
	0x84, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
} ;

/* shell characters */
#ifdef	COMMENT
constexpr char		metas[] = {
	0x00, 0x02, 0x00, 0x00,
	0x41, 0x03, 0x00, 0x58,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
} ;
#endif /* COMMENT */

/* 'double quote', 'back slash', 'pound', 'back accent', et cetera */
constexpr char		doubles[] = {
	0x00, 0x00, 0x00, 0x00,
	0x14, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10,
	0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
} ;

/* default parse terminators */
constexpr char		dterms[] = {
	0x00, 0x04, 0x00, 0x00,
	0x7A, 0x10, 0x00, 0x7C,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
} ;

constexpr char		shterms[] = {
	0x00, 0x00, 0x00, 0x00,
	0x09, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
} ;


/* exported variables */


/* exported subroutines */

int ctfieldterms(uchar *terms,int f_retain,cchar *s) noex {
    	int		rs = SR_FAULT ;
	if (terms) {
	    if (! f_retain)  {
	        for (int i = 0 ; i < 32 ; i += 1)  {
	            terms[i] = '\0' ;
	        }
	    }
	    while (*s) {
	        BASET(terms,(*s & 0xFF)) ;
	        s += 1 ;
	    } /* end while */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (ctfieldterms) */

/* ACTUAL OBJECT */
/* initialize a ctfield status block with a buffer and buffer length */
int ctfield_start(ctfield *fsbp,cchar *lp,int ll) noex {

	if (fsbp == NULL) return SR_FAULT ;

	fsbp->fp = NULL ;
	fsbp->flen = 0 ;
	fsbp->term = 0 ;		/* is this the best idea?? */
	if (lp == NULL) {
	    fsbp->lp = NULL ;
	    fsbp->rlen = -1 ;
	    return SR_FAULT ;
	}

	if (ll < 0)
	    ll = strlen(lp) ;

/* remove leading white space */

	while ((ll > 0) && isspace(*lp)) {
	    lp += 1 ;
	    ll -= 1 ;
	} /* end while */

	if (*lp == '\0') ll = 0 ;

	fsbp->lp = (char *) lp ;
	fsbp->rlen = ll ;
	return ll ;
}
/* end subroutine (ctfield_start) */

int ctfield_get(ctfield *fsbp,cchar *terms) noex {
	int		lr ;
	int		c ;
	int		qe, term ;
	int		flen = 0 ;
	unsigned char	*sp, *sap ;

	if (fsbp == NULL) return SR_FAULT ;

	if (fsbp->lp == NULL) return SR_NOTOPEN ;

/* get the parameters */

	lr = fsbp->rlen ;
	sp = (unsigned char *) fsbp->lp ;

	if (terms == NULL)
	    terms = (uchar *) dterms ;

/* skip all initial white space */

	while ((lr > 0) && CHAR_ISWHITE(*sp & 0xFF)) {
	    sp += 1 ;
	    lr -= 1 ;
	} /* end while */

	sap = sp ;
	flen = -1 ;
	term = 0 ;
	if (lr > 0) {

	flen = 0 ;

/* the character is not blank space -- is it a quote? */

	c = *sp & 0xFF ;
	if (BATST(quotes,c)) {

/* it is a quote character, so we prepare to extract it */

	    qe = c ;			/* set default quote end */
	    sp += 1 ;
	    lr -= 1 ;			/* skip over quote character */
	    sap = sp ;	 		/* save ctfield address */

	    while ((lr > 0) && ((c = (*sp & 0xFF)) != qe)) {
	        sp += 1 ;
	        lr -= 1 ;
	    }

	    flen = sp - sap ;
	    sp += 1 ;
	    lr -= 1 ;			/* skip over quote character */

	} else if (! BATST(terms,c)) {

	    sap = sp++ ;	 	/* save ctfield address */
	    lr -= 1 ;
	    while (lr > 0) {

	        c = *sp & 0xFF ;

	        if (BATST(terms,c) || BATST(quotes,c))
	            break ;

	        if (CHAR_ISWHITE(c))
	            break ;

	        sp += 1 ;
	        lr -= 1 ;

	    } /* end while */

	    flen = sp - sap ;

	} /* end if (processing a ctfield) */

	if ((lr > 0) && CHAR_ISWHITE(*sp)) {

	    term = ' ' ;
	    while ((lr > 0) && CHAR_ISWHITE(*sp)) {
	        sp += 1 ;
	        lr -= 1 ;
	    } /* end while */

	} /* end if */

	c = *sp & 0xFF ;

	if ((lr > 0) && BATST(terms,c) && (! BATST(quotes,c))) {

	    term = c ;
	    sp += 1 ;
	    lr -= 1 ;

	} /* end if */

	} /* end if (postiive) */

	fsbp->rlen = lr ;		/* load length remaining in string */
	fsbp->lp = (char *) sp ;	/* address of remaining string */
	fsbp->flen = flen ;		/* length of ctfield */
	fsbp->fp = (flen >= 0) ? ((char *) sap) : NULL ;
	fsbp->term = term ;		/* terminating character */

	return flen ;			/* return length of ctfield */
}
/* end subroutine (ctfield_get) */

int ctfield_term(ctfield *fsbp,cchar *terms) noex {
	int		lr, flen ;
	int		c ;
	int		term ;
	unsigned char	*sp, *sap ;

	if (fsbp == NULL) return SR_FAULT ;

	if (fsbp->lp == NULL) return SR_NOTOPEN ;

/* get the parameters */

	lr = fsbp->rlen ;
	sp = (unsigned char *) fsbp->lp ;

	sap = sp ;
	if (terms == NULL)
	    terms = (uchar *) dterms ;

	term = 0 ;
	flen = -1 ;
	if (lr > 0) {

	flen = 0 ;

	c = *sp & 255 ;
	if (! BATST(terms,c)) {

	    sap = sp++ ;	 		/* save ctfield address */
	    lr -= 1 ;
	    while (lr > 0) {
	        c = *sp & 0xFF ;
	        if (BATST(terms,c)) break ;
	        sp += 1 ;
	        lr -= 1 ;
	    } /* end while */
	    flen = sp - sap ;

	} /* end if (processing a ctfield) */
	c = *sp & 0xFF ;
	if ((lr > 0) && BATST(terms,c)) {
	    term = c ;
	    sp += 1 ;
	    lr -= 1 ;
	} /* end if */

	} /* end if (positive) */

	fsbp->rlen = lr ;		/* load length remaining in string */
	fsbp->lp = (char *) sp ;	/* address of remaining string */
	fsbp->flen = flen ;		/* length of ctfield */
	fsbp->fp = (flen >= 0) ? ((char *) sap) : NULL ;
	fsbp->term = term ;		/* terminating character */

	return flen ;			/* return length of ctfield */
}
/* end subroutine (ctfield_term) */

/* get the next SHELL argument ctfield in this buffer */

/*
	Arguments:
	fsbp		ctfield status block pointer
	terms		bit array of terminating characters
	buf		buffer to store result
	buflen		length of buffer to hold result
*/

int ctfield_sharg(ctfield *fsbp,cchar *terms,char *buf,int buflen) noex {
	int		lr, flen ;
	int		qe, term ;
	unsigned char	*cp ;
	unsigned char	*bp = (unsigned char *) buf ;

	if (fsbp == NULL) return SR_FAULT ;

	if (fsbp->lp == NULL) return SR_NOTOPEN ;

/* get the parameters */

	lr = fsbp->rlen ;
	cp = (unsigned char *) fsbp->lp ;

	if (terms == NULL)
	    terms = (uchar *) shterms ;

/* skip all initial white space */

	while ((lr > 0) && CHAR_ISWHITE(*cp)) {
	    lr -= 1 ;
	    cp += 1 ;
	}

	flen = -1 ;			/* end-of-arguments indicator */
	term = 0 ;
	if (lr > 0) {

/* process the standard SHELL string */

	while (lr > 0) {

	    if (BATST(terms,*cp) & (! BATST(quotes,*cp)))
	        break ;

	    if (CHAR_ISWHITE(*cp))
	        break ;

	    if (*cp == '\"') {

	        qe = *cp++ ;
	        lr -= 1 ;
	        while (lr > 0) {

	            if ((*cp == '\\') && (lr > 1) && BATST(doubles,cp[1])) {

	                cp += 1 ;
	                lr -= 1 ;
	                if (buflen > 0) {
	                    *bp++ = *cp ;
	                    buflen -= 1 ;
	                }

	                cp += 1 ;
	                lr -= 1 ;

	            } else if (*cp == qe) {

	                cp += 1 ;
	                lr -= 1 ;
	                break ;

	            } else {

	                if (buflen > 0) {

	                    *bp++ = *cp ;
	                    buflen -= 1 ;
	                }

	                cp += 1 ;
	                lr -= 1 ;

	            } /* end if */

	        } /* end while (processing the quoted portion) */

	    } else if (*cp == '\'') {

	        qe = *cp++ ;
	        lr -= 1 ;
	        while (lr > 0) {

	            if (*cp == qe) {
	                cp += 1 ;
	                lr -= 1 ;
	                break ;
	            } else {
	                if (buflen > 0) {
	                    *bp++ = *cp ;
	                    buflen -= 1 ;
	                }
	                cp += 1 ;
	                lr -= 1 ;
	            }

	        } /* end while (processing the quoted portion) */

	    } else if ((*cp == '\\') && (lr > 1)) {

	        cp += 1 ;
	        lr -= 1 ;
	        if (buflen > 0) {
	            *bp++ = *cp ;
	            buflen -= 1 ;
	        }

	        cp += 1 ;
	        lr -= 1 ;

	    } else {

	        if (buflen > 0) {
	            *bp++ = *cp ;
	            buflen -= 1 ;
	        }

	        cp += 1 ;
	        lr -= 1 ;
	    }

	} /* end while (main loop) */

/* do the terminator processing */

	while ((lr > 0) && CHAR_ISWHITE(*cp)) {
	    cp += 1 ;
	    lr -= 1 ;
	} /* end while */

/* we are at the end */

	term = ' ' ;
	if (BATST(terms,*cp) && (! BATST(quotes,*cp))) {

	    term = *cp ;		/* save terminator */
	    lr -= 1 ;			/* skip over the terminator */
	    cp += 1 ;

	} /* end if */

	flen = (bp - ((unsigned char *) buf)) ;

	} /* end if (positive) */

	fsbp->rlen = lr ;		/* load length remaining in string */
	fsbp->lp = (char *) cp ;	/* address of remaining string */
	fsbp->flen = flen ;
	fsbp->fp = (char *) buf ;	/* ctfield sub-string address */
	fsbp->term = term ;		/* terminating character */

	return flen ;			/* return length of ctfield */
}
/* end subroutine (ctfield_sharg) */

int ctfield_finish(ctfield *fsbp) noex {
    	int		rs = SR_FAULT ;
	if (fsbp) {
	    rs = SR_NOTOPEN ;
	    if (fsbp->lp) {
		rs = SR_OK :
	    }
	}
	return rs ;
}
/* end subroutine (ctfield_finish) */


