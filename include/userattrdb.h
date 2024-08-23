/* userattrdb HEADER */
/* lang=C20 */

/* user-attribute database management */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-06-05, David A­D­ Morano
	I wrote this so that both the old UDOMAIN facility and the
	newer user-attribute database capability of Sun Solaris®
	2.6 (first that I have seen of it) can be included into a
	single database lookup mechanism.

	= 2017-05-01, David A­D­ Morano
	I just noticed that I too out the UDOMAIN function and
	forgot to make a note here of it. Well I removed it a few
	years ago now but have forgotten exactly where it was
	removed. I removed it because the old UDOMAIN data-base was
	no longer really needed.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	USERATTRDB_INCLUDE
#define	USERATTRDB_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<usystem.h>
#include	<localmisc.h>
#include	<userattr.h>		/* <- money shot */


#define	USERATTRDB		struct userattrdb_head
#define	USERATTRDB_FL		struct userattrdb_flags
#define	USERATTRDB_MAGIC	0x99999898


struct userattrdb_flags {
	uint		sysdb:1 ;	/* OS database */
	uint		udomain:1 ;	/* UDOMAIN database */
} ;

struct userattrdb_head {
	cchar		*username ;	/* passed argument */
	cchar		*domain ;	/* cached */
	userattr	*uap ;		/* returned (allocated) */
	uint		magic ;
	USERATTRDB_FL	init, have ;
} ;

typedef USERATTRDB	userattrdb ;
typedef	USERATTRDB_FL	userattrdb_fl ;

EXTERNC_begin

extern int userattrdb_open(userattrdb *,cchar *) noex ;
extern int userattrdb_lookup(userattrdb *,char *,int,cchar *) noex ;
extern int userattrdb_close(userattrdb *) noex ;

EXTERNC_end


#endif /* USERATTRDB_INCLUDE */


