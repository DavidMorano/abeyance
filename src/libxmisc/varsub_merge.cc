/* varsub_merge SUPPORT */
/* lang=C++20 */

/* variable manipulation (like for configuration files!) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-12, David A­D­ Morano
	This subroutine was written to replace some older variable
	substitution stuff from the old Automation Rsearch days
	with the old SAT tool stuff.

	= 2001-09-11, David A­D­ Morano
	This junk is not aging well!  And it was really rewritten
	from essentially scratch in 1997 (only a few years ago)!
	This code has many qualities that are common with crap code.
	When a new variable was "exported" from a configuration
	file and it did not have any value part specified, and when
	the same variable was not in the existing environment (like
	if a daemon is executed directly from |init(1m)| or something
	similar), then the variable name would end up in the exported
	environment variables list as just a variable key with no
	value!  I fixed this by not putting anything into the exported
	environment if it does not  have a value (at least a value
	of zero length).  I *think* that a nullptr value and and a
	zero-length value distinquish the case of the variable
	having an empty value string from one where it did not have
	any value specified at all.

*/

/* Copyright © 1998,2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	These routines operate on 'defined' and 'export'ed variables
	from a configuration file.  What we want to do is to perform
	a substitution on these variables from existing variables
	in the database or from the environment otherwise.  Variables
	that are already in the database get merged like in a path
	string with colon characters (':') separating the original
	values of the variables.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<climits>		/* |INT_MAX| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<estrings.h>
#include	<vecstr.h>
#include	<strwcpy.h>
#include	<strn.h>
#include	<mkchar.h>
#include	<ischarx.h>
#include	<localmisc.h>

#include	"varsub.h"


/* local defines */


/* external subroutines */

extern "C" {
    extern cchar	*getenv3(cchar *,int,cchar **) noex ;
}

extern "C" {
    int		varsub_merge(varsub *,vecstr *,char *,int) noex ;
}


/* external variables */


/* forward references */

static int	cmpkey(cchar *,cchar *,int) noex ;
static int	cmpvalue(cchar *,cchar *,int) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int varsub_merge(varsub *varp,vecstr *vsp,char *buf,int buflen) noex {
	int		rs = SR_OK ;
	int		i ;
	int		klen, vlen ;
	int		olen, nlen ;
	int		f_novalue = true ;
	int		f_done = false ;
	cchar		*kp, *vp ;
	cchar		*tp, *sp, *cp ;
	cchar		*ep ;
	char		*buf2  = nullptr ;
/* separate the string into its key and value */
	ep = buf ;
	kp = buf ;
	vp = nullptr ;
	vlen = -1 ;
	f_novalue = true ;
	if ((tp = strnchr(buf,buflen,'=')) != nullptr) {
	    klen = tp - buf ;
	    f_novalue = false ;
	    cp = buf + klen ;
	    vp = cp + 1 ;
	    vlen = strnlen(vp,(buflen - klen - 1)) ;
	} else {
	    klen = strnlen(buf,buflen) ;
	}
/* search for this key in the given vector string list (exports) */
	for (i = 0 ; (rs = vecstr_get(vsp,i,&sp)) >= 0 ; i += 1) {
	    if (sp != nullptr) {
	        if (cmpkey(sp,kp,klen) == 0) break ;
	    }
	} /* end for */
	nlen = klen + ((vlen >= 0) ? (vlen + 1) : 0) ;
	if (rs >= 0) {
	    if (vlen >= 0) {
/* we already had an entry like this one */
/* do we have this particular value in this variable's value list already? */
	        f_done = (cmpvalue(sp,vp,vlen) == 0) ;
/* prepare to add this new value to the end of the existing values! */
		if (! f_done) {
		    int	sz ;
	            olen = strlen(sp) ;
	            nlen = olen + ((vlen >= 0) ? (vlen + 1) : 0) ;
		    sz = (nlen + 1) ;
		    if ((rs = uc_malloc(sz,&buf2)) >= 0) {
	                ep = buf2 ;
	                kp = buf2 ;
	                strcpy(buf2,sp) ;
/* delete it from the vector string list */
	                vecstr_del(vsp,i) ;
/* delete the old one from the substitution array */
	                if (varp != nullptr) {
		            varsub_del(varp,kp,klen) ;
	                } /* end if (deleting from VARSUB DB) */
/* add this new part to the end of what we already have */
	                buf2[olen] = ':' ;
	                strwcpy((buf2 + olen + 1),vp,vlen) ;
	                vp = buf2 + klen + 1 ;
	                vlen = nlen - klen - 1 ;
		    } else {
		        buf2 = nullptr ;
		    } /* end if (m-a) */
		} /* end if (not done) */
	    } else {
	        f_done = true ;
	    }
	} else {
	    /* it did NOT exist already */
	    if (vlen < 0) {
	        vlen = 0 ;
	        if ((vp = getenv3(kp,klen,&ep)) != nullptr) {
		    /* others can figure out these lengths by themselves */
	            nlen = -1 ;
	            vlen = -1 ;
	        } /* end if (we had it as an environment variable) */
	    } /* end if (vlen < 0) */
	} /* end if */
	/* add the new variable to the various DBs */
	if ((rs >= 0) && (! f_done) && (vp != nullptr)) {
	    /* add the new string variable to the running string list */
	    if ((rs = vecstr_add(vsp,ep,nlen)) < 0) {
	        return rs ;
	    }
	    /* add the new string variable to the variable_substitution_array */
	    if ((varp != nullptr) && (vlen >= 0)) {
	        rs = varsub_add(varp,kp,klen,vp,vlen) ;
	    } /* end if (adding to the variable substitution VARSUB DB) */
	} /* end if (adding new variable to DBs) */
	if (buf2 != nullptr) {
	    uc_free(buf2) ;
	}
	return (rs >= 0) ? f_novalue : rs ;
}
/* end subroutine (varsub_merge) */


/* private subroutines */

/* our own key comparison routine (to handle the '=' character) */
static int cmpkey(cchar *s,cchar *k,int klen) noex {
	int		rc = -1 ;
	if ((strncmp(s,k,klen) == 0) && (s[klen] == '=')) {
	    rc = 0 ;
	}
	return rc ;
}
/* end subroutine (cmpkey) */

/* compare a new value with the exiting values of a variable */
static int cmpvalue(cchar *sp,cchar *vp,int vlen) noex {
	int		rc = -1 ;
	char		*cp ;
	if ((cp = strchr(sp,'=')) != nullptr) {
	    sp = (cp + 1) ;
	    while (*sp) {
	        bool	f = true ;
	        f = f && (strncmp(sp,vp,vlen) == 0) ;
	        f = f && ((sp[vlen] == '\0') || (sp[vlen] == ':')) ;
	        if (f) {
	            rc = 0 ;
		    break ;
	        }
	        if ((cp = strchr(sp,':')) == nullptr) {
	            break ;
	        }
	        sp = cp + 1 ;
	    } /* end while */
	} /* end if */
	return rc ;
}
/* end subroutine (cmpvalue) */


