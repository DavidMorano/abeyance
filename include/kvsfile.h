/* kvsfile HEADER */
/* lang=C20 */

/* perform access table file related functions */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-23, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	KVSFILE_INCLUDE
#define	KVSFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<time.h>		/* <- for |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vecobj.h>
#include	<hdb.h>
#include	<localmisc.h>		/* <- REALNAMELEN */


#define	KVSFILE			struct kvsfile_head
#define	KVSFILE_CUR		struct kvsfile_cursor
#define	KVSFILE_MAGIC		0x31415926
#define	KVSFILE_KEYLEN		REALNAMELEN
#define	KVSFILE_DEFENTS		100
#define	KVSFILE_DEFFILES	10


struct kvsfile_cursor {
	hdb_cur		*ecp ;
	int		i ;
} ;

struct kvsfile_head {
	vecobj		*flp ;
	vecobj		*klp ;
	hdb		*kvlp ;		/* indexed by key-value */
	hdb		*elp ;		/* indexed by key */
	time_t		ti_check ;
	uint		magic ;
} ;

typedef KVSFILE		kvsfile ;
typedef KVSFILE_CUR	kvsfile_cur ;

EXTERNC_begin

extern int kvsfile_open(kvsfile *,int,cchar *) noex ;
extern int kvsfile_fileadd(kvsfile *,cchar *) noex ;
extern int kvsfile_curbegin(kvsfile *,kvsfile_cur *) noex ;
extern int kvsfile_curend(kvsfile *,kvsfile_cur *) noex ;
extern int kvsfile_curenumkey(kvsfile *,kvsfile_cur *,char *,int) noex ;
extern int kvsfile_curenum(kvsfile *,kvsfile_cur *,char *,int,char *,int) noex ;
extern int kvsfile_fetch(kvsfile *,cchar *,kvsfile_cur *,char *,int) noex ;
extern int kvsfile_check(kvsfile *,time_t) noex ;
extern int kvsfile_close(kvsfile *) noex ;

EXTERNC_end


#endif /* KVSFILE_INCLUDE */


