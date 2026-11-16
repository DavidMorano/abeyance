/* main SUPPORT (repos) */
/* lang=C++20 */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstring>
#include	<cstdio>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<strn.h>
#include	<strwcmp.h>
#include	<localmisc.h>		/* |LINEBUFLEN| */


/* local defines */

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	2048
#endif

/* external subroutines */


/* forward references */

static bool hmat(cchar *,int) noex ;
static bool rmat(cchar *,int,cchar *) noex ;

/* exported subroutines */

int main(int argc,mainv argv,mainv) {
	FILE		*ifp = stdin ;
	FILE		*ofp = stdout ;
	cint		llen = LINEBUFLEN ;
	int		f = 0 ;
	char		lbuf[LINEBUFLEN+1] ;
	cchar		*name = "REPOS" ;
	if (argc > 1) {
	    name = argv[1] ;
	}
	while (fgets(lbuf,llen,ifp) != nullptr) {
	   int	ll = strlen(lbuf) ;
	   if (lbuf[ll-1] == '\n') ll -= 1 ;
	   if (hmat(lbuf,ll)) {
		f = rmat(lbuf,ll,name) ;
	   }
 	   if (f) {
		if (strstr(lbuf,"enabled=1") != nullptr) {
		    fprintf(ofp,"enabled=0\n") ;
		} else {
		    fprintf(ofp,"%s",lbuf) ;
		}
	   } else {
		fprintf(ofp,"%s",lbuf) ;
	    }
	} /* end while */
	return 0 ;
}
/* end subroutine (main) */

/* local subrouines */

static bool hmat(cchar *sp,int sl) noex {
	bool		f = 0 ;
	if (cchar *tp ; (tp = strnchr(sp,sl,'{')) != nullptr) {
	    sl -= ((tp+1)-sp) ;
	    sp = (tp+1) ;
	    if ((tp = strnchr(sp,sl,'}')) != nullptr) {
		f = 1 ;
	    }
	}
	return f ;
}

static bool rmat(cchar *sp,int sl,cchar *name) noex {
	int		cl ;
	bool		f = 0 ;
	cchar		*cp ;
	if (cchar *tp ; (tp = strnchr(sp,sl,'{')) != nullptr) {
	    cp = (tp+1) ;
	    sl -= ((tp+1)-sp) ;
	    sp = (tp+1) ;
	    if ((tp = strnchr(sp,sl,'}')) != nullptr) {
		cl = (tp-sp) ;
		f = (strwcmp(name,cp,cl) == 0) ;
	    }
	}
	return f ;
}
/* end subroutine (rmat) */


