/* setstr HEADER */
/* lang=C20 */

/* a set object for c-strings */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-12-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SETSTR_INCLUDE
#define	SETSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<hdb.h>


#define	SETSTR		HDB
#define	SETSTR_CUR	HDB_CUR


typedef SETSTR		setstr ;
typedef SETSTR_CUR	setstr_cur ;

EXTERNC_begin

extern int setstr_start(setstr *,int) noex ;
extern int setstr_already(setstr *,cchar *,int) noex ;
extern int setstr_add(setstr *,cchar *,int) noex ;
extern int setstr_del(setstr *,cchar *,int) noex ;
extern int setstr_count(setstr *) noex ;
extern int setstr_curbegin(setstr *,setstr_cur *) noex ;
extern int setstr_enum(setstr *,setstr_cur *,cchar **) noex ;
extern int setstr_curend(setstr *,setstr_cur *) noex ;
extern int setstr_finish(setstr *) noex ;

EXTERNC_end


#endif /* SETSTR_INCLUDE */


