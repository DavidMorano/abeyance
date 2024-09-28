/* svcfile HEADER */
/* lang=C++20 */

/* service- file manager */
/* version %I% last-modified %G% */


/* revision history:

	- 2004-05-25, David A­D­ Morano
	This subroutine was adopted for use as a service-table file
	processor.

*/

/* Copyright © 2004 David A­D­ Morano.  All rights reserved. */

#ifndef	SVCFILE_INCLUDE
#define	SVCFILE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<limits.h>
#include	<netdb.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<hdb.h>
#include	<vecobj.h>
#include	<vechand.h>
#include	<localmisc.h>		/* |MAXHOSTNAMELEN| */


#define	SVCFILE_MAGIC		0x31415926
#define	SVCFILE			struct svcfile_head
#define	SVCFILE_CUR		struct svcfile_cursor
#define	SVCFILE_ENT		struct svcfile_entry


struct svcfile_cursor {
	hdb_cur		ec ;
	int		i ;
} ;

struct svcfile_head {
	vecobj		files ;		/* files */
	vecobj		svcnames ;
	hdb		entries ;
	time_t		checktime ;
	uint		magic ;
	int		ncursors ;
} ;

struct svcfile_entry {
	cchar		*(*keyvals)[2] ;
	cchar		*svc ;
	int		nkeys ;
	int		sz ;
	int		fi ;		/* file index */
} ;

typedef SVCFILE		svcfile ;
typedef SVCFILE_CUR	svcfile_cur ;
typedef SVCFILE_ENT	svcfile_ent ;

EXTERNC_begin

extern int svcfile_open(svcfile *,cchar *) noex ;
extern int svcfile_fileadd(svcfile *,cchar *) noex ;
extern int svcfile_curbegin(svcfile *,svcfile_cur *) noex ;
extern int svcfile_curend(svcfile *,svcfile_cur *) noex ;
extern int svcfile_enumsvc(svcfile *,svcfile_cur *,char *,int) noex ;
extern int svcfile_enum(svcfile *,svcfile_cur *,
		svcfile_ent *,char *,int) noex ;
extern int svcfile_fetch(svcfile *,cchar *,svcfile_cur *,
		svcfile_ent *,char *,int) noex ;
extern int svcfile_match(svcfile *,cchar *) noex ;
extern int svcfile_check(svcfile *,time_t) noex ;
extern int svcfile_close(svcfile *) noex ;

EXTERNC_end


#endif /* SVCFILE_INCLUDE */


