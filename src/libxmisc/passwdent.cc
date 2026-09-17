/* passwdent SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* PASSWD structure management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Group:
	passwdent

	Description:
	These subroutines perform some PASSWD-structure management
	functions.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<storeitem.h>
#include	<sbuf.h>
#include	<sfx.h>
#include	<six.h>
#include	<cfdec.h>
#include	<localmisc.h>

#include	"passwdent.h"


/* local defines */

#define	PWE	PASSWDENT
#define	CPWE	CPASSWDENT
#define	SI	storeitem


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static int passwdent_parseone(PASSWD *,SI *,int,cchar *,int) noex ;
static int passwdent_parsedefs(PASSWD *,SI *,int) noex ;
static int si_copystr(SI *,char **,cchar *) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int passwdent_parse(PWE *pwp,char *pwbuf,int pwlen,cc *sp,int sl) noex {
	PASSWDENT	*hop = op ;
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (pwp && pwbuf && sp) {
	    storeitem	ib, *ibp = &ib ;
	    if (sl < 0) sl = strlen(sp) ;
	    memclear(hop) ;
	    if ((rs = storeitem_start(ibp,pwbuf,pwlen)) >= 0) {
	        int	fi = 0 ;
	        int	si ;
	        while ((si = sichr(sp,sl,':')) >= 0) {
	            rs = passwdent_parseone(pwp,ibp,fi++,sp,si) ;
	            sl -= (si+1) ;
	            sp += (si+1) ;
	            if (rs < 0) break ;
	        } /* end while */
	        if ((rs >= 0) && sl && sp[0]) {
	            rs = passwdent_parseone(pwp,ibp,fi++,sp,sl) ;
	        }
	        if (rs >= 0) {
	            rs = passwdent_parsedefs(pwp,ibp,fi) ;
		    fi = rs ;
	        }
	        if ((rs >= 0) && (fi < 6)) rs = SR_BADFMT ;
	        rs1 = storeitem_finish(ibp) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (storeitem) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (passwdent_parse) */

int passwdent_load(PWE *pwp,char *pwbuf,int pwlen,CPWE *spwp) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (pwp && pwbuf && spwp) {
	    storeitem	ib ;
	    memcpy(pwp,spwp,sizeof(PASSWDENT)) ;
	    if ((rs = storeitem_start(&ib,pwbuf,pwlen)) >= 0) {
	        si_copystr(&ib,&pwp->pw_name,spwp->pw_name) ;
	        si_copystr(&ib,&pwp->pw_passwd,spwp->pw_passwd) ;
	        si_copystr(&ib,&pwp->pw_gecos,spwp->pw_gecos) ;
	        si_copystr(&ib,&pwp->pw_dir,spwp->pw_dir) ;
	        si_copystr(&ib,&pwp->pw_shell,spwp->pw_shell) ;
	        rs1 = storeitem_finish(&ib) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (storeitem) */
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (passwdent_load) */

int passwdent_format(CPWE *pwp,char *rbuf,int rlen) noex {
	int		rs = SR_FAULT ;
	int		rs1 ;
	if (pwp && rbuf) {
	    if (sbuf b ; (rs = sbuf_start(&b,rbuf,rlen)) >= 0) {
	        for (int i = 0 ; i < 7 ; i += 1) {
	            int		v ;
	            if (i > 0) rs = sbuf_char(&b,':') ;
	            if (rs >= 0) {
	                switch (i) {
	                case 0:
	                    rs = sbuf_strw(&b,pwp->pw_name,-1) ;
	                    break ;
	                case 1:
	                    rs = sbuf_strw(&b,pwp->pw_passwd,-1) ;
	                    break ;
	                case 2:
	                    v = pwp->pw_uid ;
	                    rs = sbuf_deci(&b,v) ;
	                    break ;
	                case 3:
	                    v = pwp->pw_gid ;
	                    rs = sbuf_deci(&b,v) ;
	                    break ;
	                case 4:
	                    rs = sbuf_strw(&b,pwp->pw_gecos,-1) ;
	                    break ;
	                case 5:
	                    rs = sbuf_strw(&b,pwp->pw_dir,-1) ;
	                    break ;
	                case 6:
	                    rs = sbuf_strw(&b,pwp->pw_shell,-1) ;
	                    break ;
	                } /* end switch */
	            } /* end if */
	            if (rs < 0) break ;
	        } /* end for */
	        rs1 = sbuf_finish(&b) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (sbuf) */
	} /* endif (non-null) */
	return rs ;
}
/* end subroutine (passwdent_format) */

int passwdent_size(CPWE *pp) noex {
	int		size = 1 ;
	if (pp->pw_name) {
	    size += (strlen(pp->pw_name)+1) ;
	}
	if (pp->pw_passwd) {
	    size += (strlen(pp->pw_passwd)+1) ;
	}
	if (pp->pw_gecos) {
	    size += (strlen(pp->pw_gecos)+1) ;
	}
	if (pp->pw_dir) {
	    size += (strlen(pp->pw_dir)+1) ;
	}
	if (pp->pw_shell) {
	    size += (strlen(pp->pw_shell)+1) ;
	}
	return size ;
}
/* end subroutine (passwdent_size) */


/* local subroutines */

static int passwdent_parseone(PWE *pwp,SI *ibp,int fi,cchar *vp,int vl) noex {
	int		rs = SR_OK ;
	int		v ;
	cchar		**vpp = nullptr ;
	switch (fi) {
	case 0:
	    vpp = (cchar **) &pwp->pw_name ;
	    break ;
	case 1:
	    vpp = (cchar **) &pwp->pw_passwd ;
	    break ;
	case 2:
	    rs = cfdeci(vp,vl,&v) ;
	    pwp->pw_uid = v ;
	    break ;
	case 3:
	    rs = cfdeci(vp,vl,&v) ;
	    pwp->pw_gid = v ;
	    break ;
	case 4:
	    vpp = (cchar **) &pwp->pw_gecos ;
	    break ;
	case 5:
	    vpp = (cchar **) &pwp->pw_dir ;
	    break ;
	case 6:
	    vpp = (cchar **) &pwp->pw_shell ;
	    break ;
	} /* end switch */
	if ((rs >= 0) && vpp) {
	    cchar	*cp{} ;
	    if (int cl ; (cl = sfshrink(vp,vl,&cp)) >= 0) {
	        rs = storeitem_strw(ibp,cp,cl,vpp) ;
	    }
	}
	return rs ;
}
/* end subroutine (passwdent_parseone) */

static int passwdent_parsedefs(PASSWDENT *pwp,storeitem *ibp,int sfi) noex {
	int		rs = SR_OK ;
	if (sfi == 6) {
	    cchar	**vpp = (cchar **) &pwp->pw_shell ;
	    cchar	*sp = pwp->pw_name ;
	    cchar	*vp ;
	    vp = (sp + strlen(sp)) ;
	    sfi += 1 ;
	    rs = storeitem_strw(ibp,vp,0,vpp) ;
	}
	return (rs >= 0) ? sfi : rs ;
}
/* end subroutine (passwdent_parsedefs) */

static int si_copystr(SI *ibp,char **pp,cchar *p1) noex {
	int		rs = SR_OK ;
	cchar		**cpp = (cchar **) pp ;
	*cpp = nullptr ;
	if (p1) {
	    rs = storeitem_strw(ibp,p1,-1,cpp) ;
	}
	return rs ;
}
/* end subroutine (si_copystr) */


