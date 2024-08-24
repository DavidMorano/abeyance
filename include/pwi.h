/* pwi HEADER */
/* lang=C20 */

/* PassWord Index manager */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PWI_INCLUDE
#define	PWI_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<ipasswd.h>
#include	<localmisc.h>


#define	PWI_MAGIC	0x99889998
#define	PWI		struct pwi_head
#define	PWI_CUR		struct pwi_cursor
#define	PWI_FL		struct pwi_flags


struct pwi_cursor {
	int		i ;
} ;

struct pwi_flags {
	uint		f:1 ;
} ;

struct pwi_head {
	ipasswd		db ;
	PWI_FL		f ;
	uint		magic ;
	int		i ;
} ;

typedef PWI		pwi ;
typedef PWI_FL		pwi_fl ;
typedef PWI_CUR		pwi_cur ;

EXTERNC_begin

extern int pwi_open(pwi *,cchar *,cchar *) noex ;
extern int pwi_lookup(pwi *,char *,int,cchar *) noex ;
extern int pwi_close(pwi *) noex ;

EXTERNC_end


#endif /* PWI_INCLUDE */


