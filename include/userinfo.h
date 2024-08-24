/* userinfo HEADER */
/* lang=C++20 */

/* get user information from various databases */
/* version %I% last-modified %G% */


/* revision history:

	= 1997-07-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1997 David A­D­ Morano.  All rights reserved. */

#ifndef	USERINFO_INCLUDE
#define	USERINFO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<localmisc.h>		/* |MAXHOSTNAMELEN| */


#define	USERINFO		struct userinfo_head
#define	USERINFO_MAGIC		0x33216271
#define	USERINFO_LEN		((3 * 2048) + MAXHOSTNAMELEN)
#define	USERINFO_LOGIDLEN	15


struct userinfo_head {
	cchar		*sysname ;	/* UNAME OS system-name */
	cchar		*release ;	/* UNAME OS release */
	cchar		*version ;	/* UNAME OS version */
	cchar		*machine ;	/* UNAME machine */
	cchar		*nodename ;	/* OS nodename (no domain) */
	cchar		*domainname ;	/* INET domain */
	cchar		*username ;	/* PASSWD username */
	cchar		*password ;	/* PASSWD password */
	cchar		*gecos ;	/* PASSWD GECOS field */
	cchar		*homedname ;	/* PASSWD (home) directory */
	cchar		*shell ;	/* PASSWD SHELL */
	cchar		*organization ;	/* GECOS organization */
	cchar		*gecosname ;	/* GECOS name */
	cchar		*account ;	/* GECOS account */
	cchar		*bin ;		/* GECOS printer-bin */
	cchar		*office ;	/* GECOS office */
	cchar		*wphone ;	/* GECOS work-phone */
	cchar		*hphone ;	/* GECOS home-phone */
	cchar		*printer ;	/* GECOS printer */
	cchar		*realname ;	/* processed GECOS-name */
	cchar		*mailname ;	/* best compacted mail-name */
	cchar		*fullname ;	/* best fullname */
	cchar		*name ;		/* best compacted name */
	cchar		*groupname ;	/* login groupname */
	cchar		*projname ;	/* user project name */
	cchar		*tz ;		/* user time-zone */
	cchar		*md ;		/* mail-spool directory */
	cchar		*wstation ;	/* user weather-station */
	cchar		*logid ;	/* suggested ID for logging */
	cchar		*a ;		/* memory allocation */
	pid_t		pid ;
	uid_t		uid, euid ;
	gid_t		gid, egid ;
	uint		magic ;
	int		ostype ;
} ;

#ifdef	__cplusplus
enum userinfomems {
	userinfomem_finish,
	userinfomem_overlast
} ;
struct userinfo ;
struct userinfo_cos {
	userinfo	*op = nullptr ;
	void operator () (userinfo *p) noex {
	    op = p ;
	} ;
	operator int () noex ;
	int operator () (ccharp = nullptr) noex ;
} ;
struct userinfo_co {
	userinfo	*op = nullptr ;
	int		w = -1 ;
	void operator () (userinfo *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (userinfo_co) */
struct userinfo : userinfo_head {
	userinfo_cos	start ;
	userinfo_co	finish ;
	userinfo() noex {
	    start(this) ;
	    finish(this,userinfomem_finish) ;
	} ;
	userinfo(const userinfo &) = delete ;
	userinfo &operator = (const userinfo &) = delete ;
	void dtor() noex ;
	~userinfo() noex {
	    dtor() ;
	} ;
} ; /* end struct (userinfo) */
#else	/* __cplusplus */
typedef USERINFO	userinfo ;
#endif /* __cplusplus */

EXTERNC_begin

extern int userinfo_start(userinfo *,cchar *) noex ;
extern int userinfo_finish(userinfo *) noex ;
extern int userinfo_data(userinfo *,char *,int,cchar *) noex ;

EXTERNC_end


#endif /* USERINFO_INCLUDE */


