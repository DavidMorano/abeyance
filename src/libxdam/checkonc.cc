/* checkonc SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* check for the ONC private key stuff */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-08-17, David A­D­ Morano
	This subroutine was taken from the LOGDIR/LOGNAME program
	(fist written for the SunOS 4.xx environment in 1989).  This
	is severly hacked to work in the strange environment of
	PCSPOLL!

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	checkonc

	Description:
	This subroutine checks that we have a decrypted ONC private
	key and that KEYSERV has it.

	Synopsis:
	int checkonc(cc *pr,cc *unetname,cc *uname,cc *afname) noex

	Arguments:
	pr		program root (for PCS)
	unetname	the user's ONC "netname"
	uname		username if known
	afname		authorization file name if known

	Returns:
	>=0		OK
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<rpc/rpc.h>
#include	<rpc/key_prot.h>	/* <- specific to the key-server */
#include	<unistd.h>
#include	<fcntl.h>
#include	<netdb.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<netfile.h>
#include	<vecstr.h>
#include	<localmisc.h>

#include	"checkonc.h"


/* local defines */

#ifndef	PWENTRY_BUFLEN
#define	PWENTRY_BUFLEN	256
#endif

#ifndef	VARPCS
#define	VARPCS		"PCS"
#endif

#ifndef	PCS
#define	PCS		"/usr/add-on/pcs"
#endif


/* external subroutines */

extern "C" {
    extern int	onckeyalready(cchar *) noex ;
    extern int	onckeygetset(cchar *,cchar *) noex ;
    extern int	havenis() noex ;
}


/* external variables */


/* local structures */


/* forward references */


/* local variables */

constexpr cpcchar	authfname[] = {
	".auth",
	"etc/auth",
	nullptr
} ;

constexpr cpcchar	netrcfname[] = {
	".netrc",
	"etc/netrc",
	nullptr
} ;


/* exported variables */


/* exported subroutines */

int checkonc(cc *pr,cc *unetname,cc *uname,cc *afname) noex {
	netfile		nfile ;
	vecstr		unames ;
	int	rs ;
	int	i, j, k ;
	int	nunames ;
	int	f_keyed ;
	int	f_uname ;

	cchar	*cp ;

	char	tmpfname[MAXPATHLEN + 2] ;
	char	nodename[NODENAMELEN + 1] ;
	char	domainname[MAXHOSTNAMELEN + 1] ;
	char	hostname[MAXHOSTNAMELEN + 2] ;
	char	netname[MAXNETNAMELEN + 1] ;
	char	a_username[LOGNAMELEN + 1] ;
	char	a_password[PASSWORDLEN + 1] ;


	rs = havenis() ;
	if (rs < 0)
	    goto ret0 ;

/* do we even have an ONC 'netname'? */

	if ((unetname == nullptr) || (unetname[0] == '\0')) {

	    netname[0] = '\0' ;
	    rs = getnetname(netname) ;

/* get out if we do not even have a 'netname'! (if the call "fails") */

	    if (rs == 0)
	        goto retnonetname ;

	} else
	    strwcpy(netname,unetname,MAXNETNAMELEN) ;

/* get out now if we have already given KEYSERV a key */

	rs = onckeyalready(netname) ;

	if (rs == SR_NOTSUP)
	    goto retnosup ;

	if (rs >= 0) {

	    goto retalready ;

	} /* end if (already key-logged-in) */

	f_uname = ((uname != nullptr) && (uname[0] != '\0')) ;

	if (! f_uname)
	    rs = vecstr_start(&unames,10,0) ;

	if (rs < 0)
	    goto ret0 ;

/* if we have an authorization file, use that first! */

	rs = SR_INVALID ;
	a_username[0] = '\0' ;
	if ((afname != nullptr) && (afname[0] != '\0')) {

	    if (authfile(afname,a_username,a_password) >= 0) {
	        if (a_password[0] != '\0') {
	            rs = onckeygetset(netname,a_password) ;
		}
	    }

	} /* end if (explicit authorization file) */

	if (rs >= 0)
	    goto done0 ;

/* accumulate possible usernames if we were not given one! */

	if ((a_username[0] != '\0') && (! f_uname))
	    vecstr_adduniq(&unames,a_username,-1) ;

/* try to get a program root if we do not have one already! */

	if (pr == nullptr)
	    pr = getenv(VARPCS) ;

	if (pr == nullptr)
	    pr = PCS ;

/* see if there is an authorization file at the program root */

	rs = SR_ACCESS ;
	for (i = 0 ; authfname[i] != nullptr ; i += 1) {

	    mkpath2(tmpfname,pr,authfname[i]) ;

	    if (authfile(tmpfname,a_username,a_password) >= 0) {

	        if (a_password[0] != '\0') {
	            rs = onckeygetset(netname,a_password) ;
	            if (rs >= 0) break ;
	        } /* end if (got an entry) */

	        if (! f_uname)
		    vecstr_adduniq(&unames,a_username,-1) ;

	    } /* end if */

	} /* end for */

	if (rs >= 0)
	    goto done1 ;

/* create the two most common names that this machine has (no NIS+ needed) */

	getnodedomain(nodename,domainname) ;

	hostname[0] = '\0' ;
	if (domainname[0] != '\0')
	    snsds(hostname,MAXHOSTNAMELEN,
	        nodename,domainname) ;

/* OK, now we have to do more work, look for a local NETRC file */

	nunames = (! f_uname) ? vecstr_count(&unames) : 0 ;

	f_keyed = false ;
	for (i = 0 ; netrcfname[i] != nullptr ; i += 1) {

	    mkpath2(tmpfname, pr,netrcfname[i]) ;

	    if ((rs = netfile_open(&nfile,tmpfname)) >= 0) {
	        NETFILE_ENT	*nep ;
	        for (j = 0 ; netfile_get(&nfile,i,&nep) >= 0 ; j += 1) {

	            if (nep == nullptr)
	                continue ;

	            if ((strcmp(nep->machine,nodename) != 0) &&
	                (strcmp(nep->machine,hostname) != 0))
	                continue ;

	            if (f_uname) {

	                if (strcmp(nep->login,uname) != 0)
	                    continue ;

	            } else if (nunames > 0) {

	                for (k = 0 ; (rs = vecstr_get(&unames,k,&cp)) >= 0 ; 
	                    k += 1) {

	                    if (cp == nullptr)
	                        continue ;

	                    if (strcmp(nep->login,cp) == 0)
	                        break ;

	                } /* end for */

	                if (rs < 0)
	                    continue ;

	            } /* end if */

	            if ((nep->password == nullptr) ||
	                (nep->password[0] == '\0'))
	                continue ;

	            rs = onckeygetset(netname,nep->password) ;

	            if (rs >= 0) {

	                f_keyed = true ;
	                break ;
	            }

	        } /* end for */

	        netfile_close(&nfile) ;

	    } /* end if */

	    if (f_keyed)
	        break ;

	} /* end for */

	if ((! f_keyed) && (rs >= 0))
	    rs = SR_ACCESS ;

/* we are done (for good or for bad) */
done1:
ret1:
	if (! f_uname)
	    vecstr_finish(&unames) ;

retalready:
retnosup:
retnonetname:
done0:
ret0:
	return rs ;
}
/* end subroutine (checkonc) */


