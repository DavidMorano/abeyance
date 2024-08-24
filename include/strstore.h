/* strstore HEADER */
/* lang=C20 */

/* string-store */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRSTORE_INCLUDE
#define	STRSTORE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<vechand.h>
#include	<lookaside.h>
#include	<hdb.h>


#define	STRSTORE_MAGIC		0x42114682
#define	STRSTORE		struct strstore_head
#define	STRSTORE_CUR		struct strstore_cursor
#define	STRSTORE_CHUNK		struct strstore_chunk

#define	STRSTORE_STARTLEN	10
#define	STRSTORE_CHUNKSIZE	512


struct strstore_cursor {
	int		i ;
} ;

struct strstore_chunk {
	char		*cdata ;
	int		csz ;		/* allocated buffer length */
	int		i ;		/* index length */
	int		c ;		/* item count within chunk */
} ;

struct strstore_head {
	STRSTORE_CHUNK	*ccp ;		/* current chunk pointer */
	vechand		*clp ;		/* chunk-list-pointer */
	vechand		*nlp ;		/* number-list-pointer */
	lookaside	*lap ;		/* look-aside-pointer */
	hdb		*hlp ;		/* hash-list-pointer */
	uint		magic ;
	int		chsize ;
	int		totalsize ;
	int		c ;		/* total count */
} ;

typedef STRSTORE	strstore ;
typedef STRSTORE_CUR	strstore_cur ;

EXTERNC_begin

extern int	strstore_start(strstore *,int,int) noex ;
extern int	strstore_already(strstore *,cchar *,int) noex ;
extern int	strstore_add(strstore *,cchar *,int) noex ;
extern int	strstore_adduniq(strstore *,cchar *,int) noex ;
extern int	strstore_store(strstore *,cchar *,int,cchar **) noex ;
extern int	strstore_curbegin(strstore *,strstore_cur *) noex ;
extern int	strstore_enum(strstore *,strstore_cur *,cchar **) noex ;
extern int	strstore_curend(strstore *,strstore_cur *) noex ;
extern int	strstore_count(strstore *) noex ;
extern int	strstore_size(strstore *) noex ;
extern int	strstore_finish(strstore *) noex ;

extern int	strstore_strsize(strstore *) noex ;
extern int	strstore_strmk(strstore *,char *,int) noex ;
extern int	strstore_recsize(strstore *) noex ;
extern int	strstore_recmk(strstore *,int *,int) noex ;
extern int	strstore_indlen(strstore *) noex ;
extern int	strstore_indsize(strstore *) noex ;
extern int	strstore_indmk(strstore *,int (*)[3],int,int) noex ;

EXTERNC_end


#endif /* STRSTORE_INCLUDE */


