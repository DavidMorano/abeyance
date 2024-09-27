/* strenv HEADER */
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
	strenv

	Description:
	Recommended usage within source code:
		#include	<strenv.hh>
		strenv	strpath(strenv_path) ;
		if (strpath != nullptr) {
			* do something w/ string-value pointer 'strpath' *
		}

*******************************************************************************/

#ifndef	STRENV_INCLUDE
#define	STRENV_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* first to configure */
#include	<usystem.h>


enum strenvs {
	strenv_path,
	strenv_fpath,
	strenv_incpath,
	strenv_libpath,
	strenv_manpath,
	strenv_infopath,
	strenv_cdpath,
	strenv_tmpdir,
	strenv_maildir,
	strenv_node,
	strenv_domain,
	strenv_localdomain,
	strenv_username,
	strenv_user,
	strenv_logname,
	strenv_home,
	strenv_mail,
	strenv_organization,
	strenv_orgloc,
	strenv_orgcode,
	strenv_overlast
} ;

class strenv {
	cchar		*strp = nullptr ;
	cint		w ;
	int		facc = false ;
public:
	strenv(int aw) noex : w(aw) { } ;
	strenv() = delete ;
	strenv &operator = (const strenv &) = delete ;
	operator ccharp () noex ;
} ; /* end class (strenv) */


#endif	/* __cplusplus */
#endif /* STRENV_INCLUDE */


