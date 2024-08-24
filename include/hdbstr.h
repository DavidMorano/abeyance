/* hdbstr HEADER */
/* lang=C20 */

/* Key-Value Hash DataBase for Strings */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	HDBSTR_INCLUDE
#define	HDBSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<hdb.h>
#include	<localmisc.h>


#define	HDBSTR		hdb
#define	HDBSTR_CUR	hdb_cur
#define	HDBSTR_DAT	hdb_dat


typedef	HDBSTR		hdbstr ;
typedef	HDBSTR_CUR	hdbstr_cur ;
typedef	HDBSTR_DAT	hdbstr_dat ;

EXTERNC_begin

extern int hdbstr_start(hdbstr *,int) noex ;
extern int hdbstr_add(hdbstr *,cchar *,int,cchar *,int) noex ;
extern int hdbstr_curbegin(hdbstr *,hdbstr_cur *) noex ;
extern int hdbstr_curend(hdbstr *,hdbstr_cur *) noex ;
extern int hdbstr_fetch(hdbstr *,cchar *,int,hdbstr_cur *,cchar **) noex ;
extern int hdbstr_fetchrec(hdbstr *,cchar *,int,hdbstr_cur *,
				cchar **,cchar **,int *) noex ;
extern int hdbstr_getrec(hdbstr *,hdbstr_cur *,cchar **,cchar **,int *) noex ;
extern int hdbstr_enum(hdbstr *,hdbstr_cur *,cchar **,cchar **,int *) noex ;
extern int hdbstr_delkey(hdbstr *,cchar *,int) noex ;
extern int hdbstr_delcur(hdbstr *,hdbstr_cur *,int) noex ;
extern int hdbstr_next(hdbstr *,hdbstr_cur *) noex ;
extern int hdbstr_nextkey(hdbstr *,cchar *,int,hdbstr_cur *) noex ;
extern int hdbstr_count(hdbstr *) noex ;
extern int hdbstr_finish(hdbstr *) noex ;

EXTERNC_end


#endif /* HDBSTR_INCLUDE */


