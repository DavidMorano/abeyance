/* mimetypes HEADER */
/* lang=C20 */

/* manage a MIME-type database */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	MIMETYPES_INCLUDE
#define	MIMETYPES_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/param.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<hdb.h>
#include	<localmisc.h>		/* |MAXNAMELEN| */


/* object defines */
#define	MIMETYPES		hdb
#define	MIMETYPES_CUR		hdb_cur
#define	MIMETYPES_DAT		hdb_dat
#define	MIMETYPES_TYPELEN	MAXNAMELEN
#define	MIMETYPES_NUMKEYS	200	/* initial estimated number of keys */


typedef MIMETYPES	mimetypes ;
typedef MIMETYPES_CUR	mimetypes_cur ;
typedef MIMETYPES_DAT	mimetypes_dat ;

EXTERNC_begin

extern int mimetypes_start(mimetypes *) noex ;
extern int mimetypes_finish(mimetypes *) noex ;
extern int mimetypes_file(mimetypes *,cchar *) noex ;
extern int mimetypes_curbegin(mimetypes *,mimetypes_cur *) noex ;
extern int mimetypes_curend(mimetypes *,mimetypes_cur *) noex ;
extern int mimetypes_enum(mimetypes *,mimetypes_cur *,char *,char *) noex ;
extern int mimetypes_fetch(mimetypes *,cchar *,mimetypes_cur *,char *) noex ;
extern int mimetypes_find(mimetypes *,char *,cchar *) noex ;
extern int mimetypes_get(mimetypes *,char *,cchar *) noex ;

EXTERNC_end


#endif /* MIMETYPES_INCLUDE */


