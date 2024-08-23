/* pwentry HEADER */
/* lang=C20 */

/* PW-ENTRY object and interface */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-00-00, David A.D. Morano
	This was originally written.

	= 2018-12-21, David A.D. Morano
	Added |pwentrybufsize(3dam)|.


***********************************************************************/

/* Copyright © 1998,2018 David A-D- Morano.  All rights reserved. */

#ifndef	PWENTRY_INCLUDE
#define	PWENTRY_INCLUDE	


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* system IDs */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#ifndef	PWENTRY
#define	PWENTRY		struct pwentry_head
#endif


struct pwentry_head {
	cchar		*username ;
	cchar		*password ;
	cchar		*gecos ;
	cchar		*dir ;
	cchar		*shell ;
	cchar		*organization ;
	cchar		*realname ;
	cchar		*account ;
	cchar		*bin ;
	cchar		*name_f ;
	cchar		*name_m1 ;
	cchar		*name_m2 ;
	cchar		*name_l ;
	cchar		*office ;
	cchar		*wphone ;
	cchar		*hphone ;
	cchar		*printer ;
	long		lstchg ;	/* password lastchanged date */
	long		daymin ;	/* min days between password changes */
	long		daymax ;	/* max days password is valid */
	long		warn ;		/* days to warn user to change passwd */
	long		inact ;		/* days the login may be inactive */
	long		expire ;	/* login expiration date */
	uint		flag ;		/* currently not being used */
	uid_t		uid ;
	gid_t		gid ;
} ;

typedef PWENTRY		pwentry ;

EXTERNC_begin

extern int	pwentry_start(pwentry *) noex ;
extern int	pwentry_finish(pwentry *) noex ;
extern int	pwentry_fieldpw(pwentry *,int,cchar *,int) noex ;
extern int	pwentry_mkextras(pwentry *) noex ;
extern int	pwentry_mkcopy(pwentry *,pwentry *,char *,int) noex ;

extern int	pwentrybufsize(void) noex ;

EXTERNC_end


#endif /* PWENTRY_INCLUDE */


