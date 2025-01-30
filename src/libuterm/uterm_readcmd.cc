/* uterm_readcmd SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* read a ANSI terminal command from the input (from the terminal) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	uterm_readcmd

	Description:
	This subroutine processes characters in order to determine
	what type of control sequence we have.  The first character
	of the sequence is provided when we are called.  Subsequent
	characters are read by us.

	Synopsis:
	int uterm_readcmd(uterm *utp,termcmd *ckp,int to,int ich) noex

	Arguments:
	utp		UTERM object-pointer 
	ckp		TERMCMD object pointer (for results)
	to		time-out
	ich		initial (first) character if any (zero if none)

	Returns:
	>=0		OK
	<0		error code (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/param.h>
#include	<climits>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<ascii.h>
#include	<cfdec.h>
#include	<sbuf.h>
#include	<ndigit.h>
#include	<ischarx.h>
#include	<localmisc.h>		/* |DIGBUFLEN| */

#include	"uterm.h"
#include	"termcmd.h"


/* local defines */

#define	SUB		struct sub

#ifndef	UC
#define	UC(ch)		((uchar)(ch))
#endif

#define	TR_OPTS		(FM_NOFILTER | FM_NOECHO | FM_RAWIN | FM_TIMED)


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

struct sub {
	termcmd		*ckp ;
	uterm		*utp ;
	int		to ;		/* time-out */
	int		pi ;		/* number-prameters envountered */
	int		ii ;		/* intermediate-str index (length) */
	int		di ;		/* device-str index (length) */
	int		ich ;		/* initial character */
	int		rlen ;		/* read-length */
	int		maxdig ;	/* maximum digits in TERMCMD_MAXPVAL */
	int		f_error:1 ;
} ;


/* forward subroutines */

static int sub_start(SUB *,uterm *,termcmd *,int,int) noex ;
static int sub_readch(SUB *) noex ;
static int sub_procesc(SUB *) noex ;
static int sub_procCSI(SUB *) noex ;
static int sub_proc_dcs(SUB *) noex ;
static int sub_proc_pf(SUB *) noex ;
static int sub_proc_reg(SUB *,int) noex ;
static int sub_procescmore(SUB *,int) noex ;
static int sub_loadparam(SUB *,cchar *,int) noex ;
static int sub_finish(SUB *) noex ;

static bool isinter(int) noex ;
static bool isfinalesc(int) noex ;
static bool isfinalcsi(int) noex ;
static bool isparam(int) noex ;
static bool iscancel(int) noex ;


/* local variables */

#ifdef	COMMENT
termcmdtype_reg,		/*     */
termcmdtype_esc,		/*     */
termcmdtype_csi,		/* '[' */
termcmdtype_dcs,		/* 'P' */
termcmdtype_pf,			/* 'O' */
termcmdtype_overlast
#endif /* COMMENT */

constexpr const uchar	cans[] = "\030\032\033" ;

#ifdef	COMMENT
static cint	alts[] = {
	    CH_DEL,		/* reg */
	    CH_DEL,		/* ESC */
	    '[',		/* CSI */
	    'P',		/* DCS */
	    'O',		/* PF (also SS3) */
	    0
} ;
#endif /* COMMENT */


/* exported variables */


/* exported subroutines */

int uterm_readcmd(uterm *utp,termcmd *ckp,int to,int ich) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	int		rv = 0 ;
	if (utp && ckp) {
	    if ((rs = termcmd_clear(ckp)) >= 0) {
	        SUB		si ;
	        if ((rs = sub_start(&si,utp,ckp,to,ich)) >= 0) {
	            rs = 0 ;
	            while (rs == 0) {
	                if ((rs = sub_readch(&si)) >= 0) {
	                    cint	ch = rs ;
	                    switch (ch) {
	                    case CH_ESC:
	                        rs = sub_procesc(&si) ;
	                        break ;
	                    case CH_CSI:
	                        rs = sub_procCSI(&si) ;
	                        break ;
	                    case CH_DCS:
	                        rs = sub_proc_dcs(&si) ;
	                        break ;
	                    case CH_SS3:
	                        rs = sub_proc_pf(&si) ;
	                        break ;
	                    default:
	                        rs = sub_proc_reg(&si,ch) ;
	                        break ;
	                    } /* end switch */
	                } /* end if (read first character) */
			rv = rs ;
	            } /* end while (repeating due to CANCEL) */
	            rs1 = sub_finish(&si) ;
	            if (rs >= 0) rs = rs1 ;
	        } /* end if (sub) */
	    } /* end if (clear) */
	} /* end if (non-null) */
	return (rs >= 0) ? rv : rs ;
}
/* end subroutine (uterm_readcmd) */


/* local subroutines */

static int sub_start(SUB *sip,uterm *utp,termcmd *ckp,int to,int ich) noex {
	int		rs = SR_OK ;
	memclear(sip) ;
	sip->maxdig = ndigit(TERMCMD_MAXPVAL,10) ;
	sip->ckp = ckp ;
	sip->utp = utp ;
	sip->to = to ;
	sip->ich = ich ;
	return rs ;
}
/* end subroutine (sub_start) */

static int sub_finish(SUB *sip) noex {
	int		rs = SR_FAULT ;
	if (sip) {
	    rs = SR_OK ;
	}
	return rs ;
}
/* end subroutine (sub_finish) */

static int sub_readch(SUB *sip) noex {
	int		rs = SR_OK ;
	int		rch = 0 ;

	if (sip->ich != 0) {
	    rch = sip->ich ;
	    sip->ich = 0 ;
	} else {
	    uterm	*utp = sip->utp ;
	    cint	ropts = TR_OPTS ;
	    cint	to = sip->to ;
	    char	rbuf[2] ;
	    rs = uterm_reade(utp,rbuf,1,to,ropts,NULL,NULL) ;
	    rch = (rbuf[0] & 0xff) ;
	    if (rs > 0) sip->rlen += 1 ;
	}

	return (rs >= 0) ? rch : rs ;
}
/* end subroutine (sub_readch) */

static int sub_procesc(SUB *sip) noex {
	termcmd		*ckp = sip->ckp ;
	int		rs ;

	ckp->name = termcmdtype_esc ;

	if ((rs = sub_readch(sip)) >= 0) {
	    cint	ch = rs ;
	    switch (ch) {
	    case '[':
	        rs = sub_procCSI(sip) ;
	        break ;
	    case 'P':
	        rs = sub_proc_dcs(sip) ;
	        break ;
	    case 'O':
	        rs = sub_proc_pf(sip) ;
	        break ;
	    default:
	        if (iscancel(ch)) {
	            termcmd_clear(ckp) ;
	            if (ch == CH_ESC) sip->ich = ch ;
	            rs = 0 ;	/* signal CANCEL */
	        } else {
	            rs = sub_procescmore(sip,ch) ;
	        } /* end if */
	        break ;
	    } /* end switch */
	} /* end if (sub_readch) */

	return rs ;
}
/* end subroutine (sub_procesc) */

static int sub_procescmore(SUB *sip,int ch) noex {
	termcmd		*ckp = sip->ckp ;
	cint		ilen = TERMCMD_ISIZE ;
	int		rs = SR_OK ;

	ckp->type = termcmdtype_esc ;
	ckp->istr[0] = '\0' ;
	ckp->dstr[0] = '\0' ;

	while (isinter(ch)) {
	    if (sip->ii < ilen) {
	        ckp->istr[sip->ii++] = ch ;
	    } else {
	        ckp->f.iover = true ;
	    }
	    rs = sub_readch(sip) ;
	    if (rs < 0) break ;
	    ch = rs ;
	} /* end while */
	ckp->istr[sip->ii] = 0 ;

	if (rs >= 0) {
	    if (isfinalesc(ch)) {
	        ckp->name = ch ;
	        rs = 1 ;		/* signal DONE */
	    } else if (iscancel(ch)) {
	        termcmd_clear(ckp) ;
	        ckp->name = 0 ;		/* error */
	        if (ch == CH_ESC) {
	            sip->ich = ch ;
	            rs = 0 ;		/* signal CANCEL w/ continue */
	        } else
	            rs = 1 ;		/* signal DONE w/ error */
	    } else {
	        ckp->name = 0 ;		/* error */
	        rs = 1 ;		/* signal DONE w/ error */
	    }
	} /* end if */

	return rs ;
}
/* end subroutine (sub_procescmore) */

static int sub_procCSI(SUB *sip) noex {
	termcmd		*ckp = sip->ckp ;
	int		rs ;

	ckp->type = termcmdtype_csi ;
	ckp->istr[0] = '\0' ;
	ckp->dstr[0] = '\0' ;

	if ((rs = sub_readch(sip)) >= 0) {
	    cint	ilen = TERMCMD_ISIZE ;
	    cint	dlen = DIGBUFLEN ;
	    int		dl = 0 ;
	    int		ch = rs ;
	    bool	f_expecting = false ;
	    bool	f_dover = false ;
	    bool	f_leadingzero = true ;
	    char	dbuf[DIGBUFLEN+1] = { 0 } ;

	    if (ch == '?') {
	        ckp->f.fpriv = true ;
	        rs = sub_readch(sip) ;
	        ch = rs ;
	    }

	    while ((rs >= 0) && isparam(ch)) {
	        if (isdigitlatin(ch)) {
	            if ((ch != '0') || (! f_leadingzero)) {
	                if (ch != '0') f_leadingzero = false ;
	                if (dl < dlen) {
	                    dbuf[dl++] = ch ;
	                } else {
	                    f_dover = true ;
	                }
	            }
	        } else if (ch == ';') {
	            f_expecting = true ;
	            if (f_dover) {
	                sip->f_error = true ;
	            } else {
	                rs = sub_loadparam(sip,dbuf,dl) ;
	                dbuf[0] = '\0' ;
	                dl = 0 ;
	            }
	        }
	        rs = sub_readch(sip) ;
	        ch = rs ;
	        if (rs < 0) break ;
	    } /* end while (loading parameters) */

	    if ((rs >= 0) && ((dl > 0) || f_expecting)) {
	        rs = sub_loadparam(sip,dbuf,dl) ;
	        dbuf[0] = '\0' ;
	        dl = 0 ;
	    } /* end if (loading the last parameter) */

	    while ((rs >= 0) && isinter(ch)) {
	        if (sip->ii < ilen) {
	            ckp->istr[sip->ii++] = ch ;
	        } else {
	            ckp->f.iover = true ;
	        }
	        rs = sub_readch(sip) ;
	        if (rs < 0) break ;
	        ch = rs ;
	    } /* end while */

	    if (rs >= 0) {
	        if (isfinalcsi(ch)) {
	            ckp->name = ch ;
	            rs = 1 ;		/* signal DONE */
	        } else if (iscancel(ch)) {
	            termcmd_clear(ckp) ;
	            ckp->name = 0 ;		/* error */
	            if (ch == CH_ESC) {
	                sip->ich = ch ;
	                rs = 0 ;		/* signal CANCEL w/ continue */
	            } else {
	                rs = 1 ;		/* signal DONE w/ error */
	            }
	        } else {
	            ckp->name = 0 ;		/* error */
	            rs = 1 ;		/* signal DONE w/ error */
	        }
	    } /* end if */

#ifdef	COMMENT
	    if ((rs >= 0) && (sip->pi > 0)) {
	        if (sip->pi < TERMCMD_NP) {
	            ckp->p[sip->pi] = TERMCMD_PEOL ;
	        }
	    }
#endif /* COMMENT */

	} /* end if (sub_readch) */

	return rs ;
}
/* end subroutine (sub_procCSI) */

static int sub_proc_dcs(SUB *sip) noex {
	termcmd		*ckp = sip->ckp ;
	int		rs ;

	ckp->type = termcmdtype_dcs ;
	ckp->istr[0] = '\0' ;
	ckp->dstr[0] = '\0' ;

	if ((rs = sub_readch(sip)) >= 0) {
	    cint	ilen = TERMCMD_ISIZE ;
	    cint	dlen = DIGBUFLEN ;
	    int		dl = 0 ;
	    int		ch = rs ;
	    bool	f_expecting = false ;
	    bool	f_dover = false ;
	    bool	f_leadingzero = true ;
	    char	dbuf[DIGBUFLEN+1] = { 0 } ;

	    if (ch == '?') {
	        ckp->f.fpriv = true ;
	        rs = sub_readch(sip) ;
	        ch = rs ;
	    }

	    while ((rs >= 0) && isparam(ch)) {
	        if (isdigitlatin(ch)) {
	            if ((ch != '0') || (! f_leadingzero)) {
	                if (ch != '0') f_leadingzero = false ;
	                if (dl < dlen) {
	                    dbuf[dl++] = ch ;
	                } else {
	                    f_dover = true ;
			}
	            }
	        } else if (ch == ';') {
	            f_expecting = true ;
	            if (f_dover) {
	                sip->f_error = true ;
	            } else {
	                rs = sub_loadparam(sip,dbuf,dl) ;
	                dbuf[0] = '\0' ;
	                dl = 0 ;
	            }
	        }
	        rs = sub_readch(sip) ;
	        ch = rs ;
	        if (rs < 0) break ;
	    } /* end while (loading parameters) */

	    if ((rs >= 0) && ((dl > 0) || f_expecting)) {
	        rs = sub_loadparam(sip,dbuf,dl) ;
	        dbuf[0] = '\0' ;
	        dl = 0 ;
	    } /* end if (loading the last parameter) */

	    while ((rs >= 0) && isinter(ch)) {
	        if (sip->ii < ilen) {
	            ckp->istr[sip->ii++] = ch ;
	        } else {
	            ckp->f.iover = true ;
	        }
	        rs = sub_readch(sip) ;
	        if (rs < 0) break ;
	        ch = rs ;
	    } /* end while */

	    if (rs >= 0) {
	        if (isfinalcsi(ch)) {
	            ckp->name = ch ;	/* no error */
	            rs = 1 ;		/* signal OK */
	        } else if (iscancel(ch)) {
	            termcmd_clear(ckp) ;
	            ckp->name = 0 ;		/* error (CANCEL) */
	            if (ch == CH_ESC) {
	                sip->ich = ch ;
	                rs = 0 ;		/* signal CANCEL w/ continue */
	            } else {
	                rs = 1 ;		/* signal w/ error */
	            }
	        } else {
	            ckp->name = 0 ;		/* error */
	            rs = 1 ;		/* signal w/ error */
	        }
	    } /* end if */

	    if ((rs >= 0) && (ckp->name != 0)) {
	        int	f_seenesc = false ;
	        cint	dlen = TERMCMD_DSIZE ;
	        while (rs >= 0) {
	            rs = sub_readch(sip) ;
	            if (rs < 0) break ;
	            ch = rs ;
	            if (f_seenesc) {
	                if (ch != CH_BSLASH) {
	                    sip->ich = ch ;
	                    rs = 0 ;		/* signal CANCEL */
	                }
	                break ;
	            }
	            if (ch == CH_ST) break ;
	            if (ch != CH_ESC) {
	                if (iscancel(ch)) {
	                    rs = 0 ;		/* signcal CANCEL */
	                    break ;
	                }
	                if (sip->di < dlen) {
	                    ckp->dstr[sip->di++] = ch ;
	                } else {
	                    ckp->f.dover = true ;
	                }
	            } else {
	                f_seenesc = true ;
	            }
	        } /* end while */
	    } /* end if */

#ifdef	COMMENT
	    if ((rs >= 0) && (sip->pi > 0)) {
	        if (sip->pi < TERMCMD_NP) {
	            ckp->p[sip->pi] = TERMCMD_PEOL ;
	        }
	    }
#endif /* COMMENT */

	} /* end if (sub_readch) */

	return rs ;
}
/* end subroutine (sub_proc_dcs) */

static int sub_proc_pf(SUB *sip) noex {
	termcmd		*ckp = sip->ckp ;
	int		rs ;

	ckp->type = termcmdtype_pf ;
	ckp->istr[0] = '\0' ;
	ckp->dstr[0] = '\0' ;

	if ((rs = sub_readch(sip)) >= 0) {
	    cint	ch = rs ;
	    if (isfinalcsi(ch)) {
	        ckp->name = ch ;
	        rs = 1 ;		/* signal DONE */
	    } else if (iscancel(ch)) {
	        termcmd_clear(ckp) ;
	        ckp->name = 0 ;		/* error */
	        if (ch == CH_ESC) {
	            sip->ich = ch ;
	            rs = 0 ;		/* signal CANCEL w/ continue */
	        } else {
	            rs = 1 ;		/* signal DONE w/ error */
	        }
	    } else {
	        ckp->name = 0 ;		/* error */
	        rs = 1 ;		/* signal DONE w/ error */
	    }
	} /* end if (sub_readch) */

	return rs ;
}
/* end subroutine (sub_proc_pf) */

static int sub_proc_reg(SUB *sip,int ich) noex {
	termcmd		*ckp = sip->ckp ;
	int		rs = 1 ;		/* signal DONE */

	ckp->type = termcmdtype_reg ;
	ckp->name = ich ;

	return rs ;
}
/* end subroutine (sub_proc_reg) */

static int sub_loadparam(SUB *sip,cchar *dbuf,int dl) noex {
	termcmd		*ckp = sip->ckp ;
	cint		nparams = TERMCMD_NP ;
	int		rs = SR_OK ;
	int		rs1 = SR_OK ;
	int		v = 0 ;

	if (dl > 0) {
	    if (dl > sip->maxdig) {
	        v = TERMCMD_MAXPVAL ;
	    } else {
	        rs1 = cfdeci(dbuf,dl,&v) ;
	    }
	}
	if (rs1 >= 0) {
	    if (v > TERMCMD_MAXPVAL) v = TERMCMD_MAXPVAL ;
	    if (sip->pi == nparams) {
	        int	i ;
	        for (i = 1 ; i < nparams ; i += 1) {
	            ckp->p[i-1] = ckp->p[i] ;
	        }
	        sip->pi -= 1 ;
	    }
	    ckp->p[sip->pi++] = v ;
	} else {
	    sip->f_error = true ;
	}

	return rs ;
}
/* end subroutine (sub_loadparam) */

static bool isinter(int ch) noex {
	return ((ch >= 0x20) && (ch <= 0x2F)) ;
}
/* end subroutines (isinter) */

static bool isfinalesc(int ch) noex {
	return ((ch >= 0x30) && (ch <= 0x7E)) ;
}
/* end subroutines (isfinalesc) */

static bool isfinalcsi(int ch) noex {
	return ((ch >= 0x40) && (ch <= 0x7E)) ;
}
/* end subroutines (isfinalcsi) */

static bool isparam(int ch) noex {
	return ((ch >= 0x30) && (ch <= 0x3F)) ;
}
/* end subroutines (isparam) */

static bool iscancel(int ch) noex {
	bool		f = false ;
	for (int i = 0 ; cans[i] ; i += 1) {
	    f = (ch == cans[i]) ;
	    if (f) break ;
	}
	return f ;
}
/* end subroutines (iscancel) */


