/* realname HEADER */
/* lang=C20 */

/* manipulate real names */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	REALNAME_INCLUDE
#define	REALNAME_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<dstr.h>
#include	<localmisc.h>		/* |REALNAMELEN| */


#define	REALNAME		struct realname_head
#define	REALNAME_LEN		struct realname_len
#define	REALNAME_ABV		struct realname_abv
#define	REALNAME_NNAMES		5
#define	REALNAME_NPARTS		REALNAME_NNAMES

#if	defined(REALNAMELEN)
#define	REALNAME_STORELEN	MAX(REALNAMELEN,100)
#else
#define	REALNAME_STORELEN	100
#endif /* defined(REALNAMELEN) */


struct realname_len {
	uchar		first ;
	uchar		m1 ;
	uchar		m2 ;
	uchar		m3 ;
	uchar		last ;
	uchar		store ;
} ;

struct realname_abv {
	uint		first:1 ;
	uint		m1:1 ;
	uint		m2:1 ;
	uint		m3:1 ;
	uint		last:1 ;
} ;

struct realname_head {
	cchar		*first ;
	cchar		*m1 ;
	cchar		*m2 ;
	cchar		*m3 ;
	cchar		*last ;
	REALNAME_LEN	len ;
	REALNAME_ABV	abv ;
	char		store[REALNAME_STORELEN + 1] ;
} ;

typedef REALNAME	realname ;

EXTERNC_begin

extern int	realname_start(realname *,cchar *,int) noex ;
extern int	realname_startparts(realname *,dstr *) noex ;
extern int	realname_startpieces(realname *,cchar **,int) noex ;
extern int	realname_startparse(realname *,cchar *,int) noex ;
extern int	realname_getlast(realname *,cchar **) noex ;
extern int	realname_getfirst(realname *,cchar **) noex ;
extern int	realname_getm1(realname *,cchar **) noex ;
extern int	realname_getm2(realname *,cchar **) noex ;
extern int	realname_getm3(realname *,cchar **) noex ;
extern int	realname_getpieces(realname *,cchar **) noex ;
extern int	realname_fullname(realname *,char *,int) noex ;
extern int	realname_name(realname *,char *,int) noex ;
extern int	realname_mailname(realname *,char *,int) noex ;
extern int	realname_mat(realname *,realname *) noex ;
extern int	realname_matlast(realname *,char *,int) noex ;
extern int	realname_matfirst(realname *,char *,int) noex ;
extern int	realname_matm1(realname *,char *,int) noex ;
extern int	realname_matm2(realname *,char *,int) noex ;
extern int	realname_finish(realname *) noex ;

EXTERNC_end


#endif /* REALNAME_INCLUDE */


