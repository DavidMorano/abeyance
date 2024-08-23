/* varnames HEADER */
/* lang=C++20 */

/* this is a database of commonly used environment variable names */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-04-11, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This object contains various commonly used environment variable
	names.

*******************************************************************************/

#ifndef	VARNAMES_INCLUDE
#define	VARNAMES_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


struct varnames {
	static const char logid[] ;
	static const char logname[] ;
	static const char logline[] ;
	static const char loghost[] ;
	static const char utmpid[] ;
	static const char utmpname[] ;
	static const char utmpline[] ;
	static const char utmphost[] ;
	static const char username[] ;
	static const char groupname[] ;
	static const char projname[] ;
	static const char user[] ;
	static const char group[] ;
	static const char cdpath[] ;
	static const char path[] ;
	static const char fpath[] ;
	static const char binpath[] ;
	static const char libpath[] ;
	static const char incpath[] ;
	static const char manpath[] ;
	static const char manxpath[] ;
	static const char infopath[] ;
	static const char architecture[] ;
	static const char sysname[] ;
	static const char release[] ;
	static const char version[] ;
	static const char machine[] ;
	static const char osname[] ;
	static const char ostype[] ;
	static const char osrelease[] ;
	static const char osnum[] ;
	static const char osrel[] ;
	static const char osvers[] ;
	static const char mail[] ;
	static const char node[] ;
	static const char cluster[] ;
	static const char domain[] ;
	static const char localdomain[] ;
	static const char lang[] ;
	static const char shell[] ;
	static const char shlvl[] ;
	static const char home[] ;
	static const char pwd[] ;
	static const char tmpdir[] ;
	static const char maildir[] ;
	static const char maildirs[] ;
	static const char uucppublic[] ;
	static const char lines[] ;
	static const char columns[] ;
	static const char display[] ;
	static const char term[] ;
	static const char termprogram[] ;
	static const char tz[] ;
	static const char printer[] ;
	static const char printerbin[] ;
	static const char pager[] ;
	static const char organization[] ;
	static const char orgloc[] ;
	static const char orgcode[] ;
	static const char office[] ;
	static const char name[] ;
	static const char fullname[] ;
	static const char mailname[] ;
	static const char tmout[] ;
	static const char editor[] ;
	static const char visual[] ;
	static const char random[] ;
} ; /* end struct (varnames) */


extern const varnames	varname ;


#endif	/* __cplusplus */
#endif /* VARNAMES_INCLUDE */


