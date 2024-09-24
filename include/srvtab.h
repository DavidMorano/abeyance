/* srvtab HEADER */ 
/* lang=C20 */

/* perform service table file related functions */
/* version %I% last-modified %G% */


/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	SRVTAB_INCLUDE
#define	SRVTAB_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<time.h>		/* |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vecitem.h>


#define	SRVTAB_MAGIC	0x31415926
#define	SRVTAB		struct srvtab_head
#define	SRVTAB_FILE	struct srvtab_filer
#define	SRVTAB_ENT	struct srvtab_entry


struct srvtab_head {
	vecitem		e ;		/* server entries */
	cchar		*fname ;	/* server fname */
	time_t		opentime ;	/* time FD was cached */
	time_t		checktime ;	/* time last checked */
	time_t		mtime ;		/* last file modification */
	uint		magic ;
	int		fd ;		/* cached server file descriptor */
} ;

struct srvtab_filer {
	cchar		*fname ;
	time_t		opentime ;	/* time FD was cached */
	time_t		checktime ;	/* time last checked */
	time_t		mtime ;		/* file modification time */
	int		fd ;		/* also serves as "open" flag */
} ;

struct srvtab_entry {
	cchar		*service ;
	cchar		*matchcode ;
	cchar		*program ;
	cchar		*args ;
	cchar		*options ;
	cchar		*access ;
	cchar		*interval ;
	cchar		*addr ;
	cchar		*pass ;
	cchar		*username ;
	cchar		*groupname ;
	cchar		*groupnames[NGROUPS_MAX + 1] ;
	cchar		*project ;
	int		ngroups ;
	int		matchlen ;
} ;

typedef SRVTAB		srvtab ;
typedef SRVTAB_ENT	srvtab_ent ;

EXTERNC_begin

extern int srvtab_open(srvtab *,cchar *,vecitem *) noex ;
extern int srvtab_match(srvtab *,cchar *,srvtab_ent **) noex ;
extern int srvtab_find(srvtab *,cchar *,srvtab_ent **) noex ;
extern int srvtab_get(srvtab *,int,srvtab_ent **) noex ;
extern int srvtab_check(srvtab *,time_t,vecitem *) noex ;
extern int srvtab_close(srvtab *) noex ;

EXTERNC_end


#endif /* SRVTAB_INCLUDE */


