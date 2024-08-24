/* svckey HEADER */
/* lang=C++20 */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	SVCKEY_INCLUDE
#define	SVCKEY_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<svcfile.h>


#define	SVCKEY		struct svckey_head


enum svckeys {
	svckey_file,
	svckey_pass,
	svckey_so,
	svckey_p,
	svckey_a,
	svckey_u,
	svckey_g,
	svckey_interval,
	svckey_acc,
	svckey_opts,
	svckey_failcont,
	svckey_include,
	svckey_svc,
	svckey_overlast
} ;

struct svckey_head {
	cchar		*file ;
	cchar		*pass ;		/* pass-file (pipe) */
	cchar		*so ;		/* shared object */
	cchar		*p ;		/* program (execfname) */
	cchar		*a ;		/* arguments */
	cchar		*u ;		/* username */
	cchar		*g ;		/* group */
	cchar		*interval ;	/* interval */
	cchar		*acc ;		/* access */
	cchar		*opts ;		/* options */
	cchar		*failcont ;	/* fail-continue */
	cchar		*include ;
	cchar		*svc ;		/* service */
} ;

typedef	SVCKEY		svckey ;

EXTERNC_begin

extern int	svckey_load(svckey *,svcfile_ent *) noex ;

EXTERNC_end


#endif /* SVCKEY_INCLUDE */


