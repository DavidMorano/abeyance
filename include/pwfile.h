/* pwfile HEADER */
/* lang=C++20 */

/* open a 'passwd' formatted file for access */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PWFILE_INCLUDE
#define	PWFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<vecitem.h>
#include	<hdb.h>
#include	<pwentry.h>


#define	PWFILE_MAGIC	0x98127643
#define	PWFILE		struct pwfile_head
#define	PWFILE_FL	struct pwfile_flags
#define	PWFILE_CUR	struct pwfile_cursor
#define	PWFILE_ENT	pwentry

#define	PWFILE_RECLEN	PWENTRY_BUFLEN
#define	PWFILE_ENTLEN	PWENTRY_BUFLEN

/* are these even needed? */
#define	PWFILE_NAMELEN	32		/* max username length */
#define	PWFILE_PASSLEN	32		/* max normal password length */
#define	PWFILE_COMLEN	128		/* max comment field length */


struct pwfile_cursor {
	hdb_cur		*hcp ;
	int		i ;
} ;

struct pwfile_flags {
	uint		locked:1 ;	/* locked */
	uint		locked_cur:1 ;	/* locked for cursor operations */
	uint		locked_explicit:1 ;	/* locked explicitly by user */
} ;

struct pwfile_head {
	cchar		*fname ;
	vecitem		*alp ;
	hdb		*ulp ;		/* user-list-pointer */
	time_t		readtime ;
	PWFILE_FL	f ;
	uint		magic ;
	int		lfd ;
} ;

typedef PWFILE		pwfile ;
typedef	PWFILE_FL	pwfile_fl ;
typedef PWFILE_CUR	pwfile_cur ;
typedef	PWFILE_ENT	pwfile_ent ;

EXTERNC_begin

extern int pwfile_open(pwfile *,cchar *) noex ;
extern int pwfile_curbegin(pwfile *,pwfile_cur *) noex ;
extern int pwfile_curend(pwfile *,pwfile_cur *) noex ;
extern int pwfile_curenum(pwfile *,pwfile_cur *,pwfile_ent *,char *,int) noex ;
extern int pwfile_fetchuser(pwfile *,cchar *,pwfile_cur *,
		pwfile_ent *,char *,int) noex ;
extern int pwfile_lock(pwfile *,int,int) noex ;
extern int pwfile_close(pwfile *) noex ;

EXTERNC_end


#endif /* PWFILE_INCLUDE */


