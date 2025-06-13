/* openxsvc (open-x-service) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* interface component for UNIX® library-3c */
/* open a x-service */


/* revision history:

	= 1998-07-10, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Object:
	openxsvc

	Description:
	This subroutine opens what is referred to as a "facility-service."
	Facility services are services provided by "facilities."
	Facilities are normally or usually really a software
	distribution that has its own source-root or program-root.
	Examples of software distributions within AT&T are:

	NCMP
	PCS (Personal Communication Services)
	EXPTOOLS (Experimental Tools)
	LOCAL
	REXEC (Remote Execution)
	POST
	EXTRA
	AST (Advanced Software Technologies)
	GNU

	Facilities are stored in the filesystem hierarchy rooted
	at a certain place.  Facilities are usually rooted at one
	of the following locations in the system filesystem hierarchy:

	/usr
	/usr/add-on
	/opt

	Facility services are represented in the filesystem as files
	with names of the form:

	<facility>§<svc>[­<arg(s)>

	These sorts of file names are often actually stored in the
	filesystem as symbolic links.

	Synopsis:
	int uc_openfsvc(cc *pr,cc *prn,cc *svc,int of,mode_t om,
		mainv argv,mainv envv,int to) noex

	Arguments:
	pr		program-root
	prn		facility name
	svc		service name
	of		open-flags
	om		open-mode
	argv		array of arguments
	envv		attay of environment
	to		time-out

	Returns:
	<0		error
	>=0		file-descriptor

	Notes:
	Facility services are implemented with loadable shared-object
	files.  Each service has a file of the same name as the
	service name itself.  The file is a shared-object with a
	global symbol of a callable subroutine with the name
	'opensvc_<svc>' where <svc> is the service name.  The
	subroutine looks like:

	int opensvc_<svc>(cc *pr,cc *prn,int of,mode_t om,
		mainv argv,mainv envv,int to) noex

	Multiple services can be actually implemented in the same
	shared-object.  But the actual file of that object should
	be linked to other files, each with the filename of a service
	to be implemented.  These links are required because this
	code only searches for services by searching for files with
	the names of the services.

*******************************************************************************/

#ifndef	INCLUDE_OPENXSVC
#define	INCLUDE_OPENXSVC

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


struct openxsvc {
    	cchar		*prefix{} ;
	cchar		*pr ;
	cchar		*prn ;
	cchar		*svc ;
	mainv		argv ;
	mainv		envv ;
	int		of ;
	int		to ;
	mode_t		om ;
	openxsvc() = default ;
	openxsvc(const openxsvc *sop) noex {
	    pr		= sop->pr ;
	    prn		= sop->prn ;
	    svc		= sop->svc ;
	    argv	= sop->argv ;
	    envv	= sop->envv ;
	    of		= sop->of ;
	    to		= sop->to ;
	    om		= sop->om ;
	} ; /* end ctor */
	openxsvc(const openxsvc &so) noex : openxsvc(&so) { } ;
	openxsvc(cc *apr,cc *aprn,cc *asvc,int aof,mode_t aom,
		mainv aargv,mainv aenvv,int ato) noex {
	    pr		= apr ;
	    prn		= aprn ;
	    svc		= asvc ;
	    argv	= aargv ;
	    envv	= aenvv ;
	    of		= aof ;
	    to		= ato ;
	    om		= aom ;
	} ; /* end ctor */
} ; /* end struct (openxsvc) */

#endif /* INCLUDE_OPENXSVC */


