/* inetdomainname SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* get the local node name and INET domain name */
/* version %I% last-modified %G% */

#define	CF_GUESS	1	/* try to guess domain names? */
#define	CF_GETHE	0	/* use |gethe1()|? */

/* revision history:

	= 1998-07-01, David A­D­ Morano
	This code was originally written.

	= 1999-04-18, David A­D­ Morano
	This was modified to search in the following order:
		1. LOCALDOMAIN environment variable
		2. reading the file '/etc/resolv.conf'

*/

/* Copyright © 1998,1999 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	inetdomainname

	Description:
	Get (two items) the local host node name and INET domain name.

	Synopsis:
	int inetdomainname(char *nodename,char *domainname) noex

	Arguments:
	nodename	buffer to receive the local node name
	domainname	buffer to receive the local INET domain name

	Returns:
	- SR_OK		if OK
	- SR_NOTFOUND	if could not get something needed for correct operation


	The algorithm for finding the local nodename is:

	1. use the first component of the environment variable NODE

	2. use the first component of the nodename returned from the system


	NOTE: 
	Searching for the "current" domain is not an easy task and
	never has been.  There is no easy way to find out the domain
	part of the hostname for the current machine node.

	We use the following algorithm for finding the local domain:

	1. use the environment variable DOMAIN

	2. use the first component of the LOCALDOMAIN environment variable

	3. see if the environment variable NODE has a domain

	4. get the node name from the system and see if it has a domain

	5. lookup the system node name with the system resolver functions
	   and grab the first name for the current node that has a domain
	   attached

	6. use the domainname given in the resolver configuration file
           (keyword 'domain') if it is not corrupted

	7. use the first component of the 'search' keyword from the
	   resolver configuration file (NOT YET IMPLEMENTED !)

	8. we try to guess what the domain name is from the given node name

	9. return that we couln't find a domain for the current node !!

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/param.h>
#include	<sys/utsname.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstrings>		/* |strncasecmp(3c)| */
#include	<usystem.h>
#include	<filebuf.h>
#include	<sfx.h>
#include	<sncpyx.h>
#include	<strwcpy.h>
#include	<char.h>
#include	<localmisc.h>

#include	"inetdomainname.h"


/* local defines */

#define	BUFLEN		(MAXPATHLEN + (8 * 1024))
#define	RESOLVCONF	"/etc/resolv.conf"
#define	LOCALHOSTNAME	"localhost"
#define	VARNODE		"NODE"
#define	VARDOMAIN	"DOMAIN"

#define	filebufLEN	1024
#define	TO_READ		30


/* external subroutines */

#if	defined(BSD) && (! defined(EXTERN_STRNCASECMP))
extern int	strncasecmp(cchar *,cchar *,int) ;
#endif

extern "C" {
    extern char	*strshrink(char *) noex ;
}


/* external variables */


/* local structures */

struct guess {
	cchar		*node ;
	cchar		*domain ;
} ;


/* forward references */

static char	*findguess(char *) noex ;


/* local variables */

constexpr guess		ga[] = {
	{ "hammett", "ece.neu.com" },
	{ "gilmore", "ece.neu.com" },
	{ "dr", "dr.lucent.com" },
	{ "ho", "ho.lucent.com" },
	{ "mh", "mh.lucent.com" },
	{ "mt", "mt.lucent.com" },
	{ "cb", "cb.lucent.com" },
	{ nullptr, nullptr }
} ;


/* exported variables */


/* exported subroutines */

int inetdomainname(char *dbuf,int dlen,cchar *un,cchar *nodename) noex {
	struct utsname	uu ;
	struct hostent	he, *hep ;

	int	rs, rs1 ;
	int	i, len ;
	int	f_badresolv = FALSE ;
	int	f ;

	cchar	*dn = domainname ;
	cchar	*nn0, *nn1 ;
	cchar	*sp, *cp ;
	cchar	*cp1 ;

	char	buf[BUFLEN + 1] ;
	char	nodenamebuf[NODENAMELEN + 1], *nn = nodenamebuf ;


	if (nodename != nullptr)
	    nn = nodename ;

	nn[0] = '\0' ;
	un.nodename[0] = '\0' ;

/* try to get a nodename */

	nn0 = nn1 = getenv(VARNODE) ;

	if ((nn1 == nullptr) || (nn1[0] == '\0')) {

	    nn1 = uu.nodename ;
	    if (u_uname(&uu) < 0)
	        nn1[0] = '\0' ;

	} /* end if */

	if ((nn1 != nullptr) && (nn1[0] != '\0')) {
	    if ((cp = strchr(nn1,'.')) != nullptr) {
	        strwcpy(nn,nn1,(cp - nn1)) ;
	    } else {
	        strcpy(nn,nn1) ;
	    }
	} /* end if */

	if (nn[0] == '\0')
	    strcpy(nn,LOCALHOSTNAME) ;

	if (domainname == nullptr)
	    return SR_OK ;

/* try to get a domainname */

	dn[0] = '\0' ;

/* use the environment variable DOMAIN, if it exists */

	if ((dn[0] == '\0') &&
	    ((cp = getenv(VARDOMAIN)) != nullptr)) {

	    len = sfshrink(cp,-1,&cp1) ;

	    if (len <= MAXHOSTNAMELEN)
	        strwcpy(dn,cp1,len) ;

	} /* end if */

/* OK, we try LOCALDOMAIN */

	if ((dn[0] == '\0') &&
	    ((sp = getenv("LOCALDOMAIN")) != nullptr)) {

/* get the first domain name in the variable (there can be several !) */

	    while (CHAR_ISWHITE(*sp))
	        sp += 1 ;

	    cp = sp ;
	    while (*cp && (! CHAR_ISWHITE(*cp)) && (*cp != ':'))
	        cp += 1 ;

	    if ((cp - sp) <= MAXHOSTNAMELEN)
	        strwcpy(dn,sp,(cp - sp)) ;

	} /* end if (localdomain) */

/* use the environment variable NODE, if it exists */

	if ((dn[0] == '\0') &&
	    (nn0 != nullptr) && ((cp = strchr(nn0,'.')) != nullptr)) {

	    if (cp[1] != '\0')
	        strcpy(dn,(cp + 1)) ;

	} /* end if */

/* sse if the system nodename has a domain on it */

	if (dn[0] == '\0') {
	    if (nn1 == nullptr) {
	        nn1 = un.nodename ;
	        if (u_uname(&un) < 0) {
	            nn1[0] = '\0' ;
		}
	    }
	    if ((nn1[0] != '\0') && ((cp = strchr(nn1,'.')) != nullptr)) {
	        if (cp[1] != '\0') {
	            strcpy(dn,(cp + 1)) ;
		}
	    } /* end if */
	} /* end if */

/* OK, we do not have a domain name yet, try 'gethostbyname()' */

	f = (dn[0] == '\0') ;

	if (f) {

#if	CF_GETHE
	    rs = gethename(&he,buf,BUFLEN,nn) ;
#else
	    rs = uc_gethostbyname(&he,buf,BUFLEN,nn) ;
#endif

	    f = (rs >= 0) ;
	}

	if (f) {
	    hep = &he ;
	    if ((cp = strchr(hep->h_name,'.')) != nullptr) {

	        strcpy(dn,(cp + 1)) ;

	        return SR_OK ;

	    } /* end if */

	    for (i = 0 ; hep->h_aliases[i] != nullptr ; i += 1) {

	        if ((cp = strchr(hep->h_aliases[i],'.')) != nullptr) {

	            strcpy(dn,(cp + 1)) ;

	            return SR_OK ;

	        } /* end if */

	    } /* end for */

	} /* end if (use system resolver) */

/* resort to searching the RESOLVER configuration file ! */

	if ((dn[0] == '\0') && ((rs = u_open(RESOLVCONF,O_RDONLY,0666)) >= 0)) {
	    filebuf	b ;
	    int		fd = rs ;

	    rs = filebuf_start(&b,fd,0L,filebufLEN,0) ;
	    if (rs >= 0) {

	        while ((rs = filebuf_readln(&b,buf,BUFLEN,TO_READ)) > 0) {

	            len = rs ;
		    if (buf[len - 1] == '\n')
			len -= 1 ;

	            buf[len] = '\0' ;
	            cp = strshrink(buf) ;

	            if ((strncasecmp(cp,"domain",6) != 0) ||
	                (! CHAR_ISWHITE(cp[6]))) continue ;

	            cp += 7 ;
	            while (CHAR_ISWHITE(*cp))
	                cp += 1 ;

	            cp1 = cp ;
	            while ((*cp != '\0') && (! CHAR_ISWHITE(*cp)))
	                cp += 1 ;

	            if ((cp - cp1) <= 0) continue ;

	            if (strncmp(cp1,"..",2) != 0) {

	                strwcpy(dn,cp1,(cp - cp1)) ;

	                break ;

	            } else
	                f_badresolv = TRUE ;

	        } /* end while (reading lines) */

	        filebuf_finish(&b) ;
	    } /* end if (filebuf) */

	    u_close(fd) ;
	} /* end if (opened RESOLV file) */

/* OK, we try even harder (we guess) */

#if	CF_GUESS

	if (dn[0] == '\0') {

	    if ((cp = findguess(nn)) != nullptr) {

	        rs1 = sncpy1(dn,MAXHOSTNAMELEN,cp) ;

		if (rs1 < 0)
			dn[0] = '\0' ;

	    }

	} /* end if */
#endif /* CF_GUESS */


/* remove any stupid trailing dots from the domain name if any */

	if (dn[0] != '\0') {
	    len = strlen(dn) ;
	    while ((len > 1) && (dn[len - 1] == '.')) {
	        dn[--len] = '\0' ;
	    }
	} /* end if (trailing dot removal) */

	return ((dn[0] != '\0') ? SR_OK : SR_NOTFOUND) ;
}
/* end subroutine (inetdomainname) */


/* local subroutines */

/* try guessing with possible leading string matches on nodename */
static cchar *findguess(cchar *name) noex {
	int	i ; /* used-afterwards */
	for (i = 0 ; ga[i].node != nullptr ; i += 1) {
	    cchar	*sp = name ;
	    cchar	*gnp = ga[i].node ;
	    while (*gnp && (*gnp == *sp)) {
	        gnp += 1 ;
	        sp += 1 ;
	    } /* end while */
	    if (*gnp == '\0') break ;
	} /* end for */
	return ((ga[i].node != nullptr) ? ga[i].domain : nullptr) ;
}
/* end subroutine (findguess) */


