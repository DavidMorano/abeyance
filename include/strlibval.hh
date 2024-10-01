/* strlibval HEADER */
/* lang=C++20 */

/* provide a pointer to a library string-value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	strlibval

	Description:
	Recommended usage within source code:
		#include	<strlibval.hh>
		strlibval	strpath(strlibval_path) ;
		if (strpath != nullptr) {
			* do something w/ string-value pointer 'strpath' *
		}

*******************************************************************************/

#ifndef	STRLIBVAL_INCLUDE
#define	STRLIBVAL_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* first to configure */
#include	<usystem.h>


enum strlibvals {
	strlibval_logid,
	strlibval_logname,
	strlibval_logline,
	strlibval_utmpid,
	strlibval_utmpname,
	strlibval_utmpline,
	strlibval_path,
	strlibval_fpath,
	strlibval_incpath,
	strlibval_libpath,
	strlibval_manpath,
	strlibval_infopath,
	strlibval_cdpath,
	strlibval_tmpdir,
	strlibval_maildir,
	strlibval_node,
	strlibval_domain,
	strlibval_localdomain,
	strlibval_username,
	strlibval_user,
	strlibval_home,
	strlibval_mail,
	strlibval_organization,
	strlibval_orgloc,
	strlibval_orgcode,
	strlibval_overlast
} ;

class strlibval {
	cchar		*strp = nullptr ;
	char		*a = nullptr ;
	cint		w = -1 ;
	aflag		fmx ;
	aflag		fready ;
	ccharp cook() noex ;
	ccharp strtmpdir() noex ;
	ccharp strmaildir() noex ;
	ccharp strpath() noex ;
public:
	strlibval(int aw) noex : w(aw) { } ;
	strlibval() = delete ;
	strlibval &operator = (const strlibval &) = delete ;
	operator ccharp () noex ;
	void dtor() noex ;
	~strlibval() {
	    dtor() ;
	} ;
} ; /* end class (strlibval) */


#endif	/* __cplusplus */
#endif /* STRLIBVAL_INCLUDE */


