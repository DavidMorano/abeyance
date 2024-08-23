/* strtab HEADER */
/* lang=C20 */

/* string table object */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRTAB_INCLUDE
#define	STRTAB_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<vechand.h>
#include	<hdb.h>
#include	<lookaside.h>


#define	STRTAB			struct strtab_head
#define	STRTAB_CH		struct strtab_chunk

#define	STRTAB_AOBJ		lookaside
#define	STRTAB_MAGIC		0x88776215
#define	STRTAB_MINCHUNKSIZE	40


struct strtab_chunk {
	char		*cdata ;
	int		csz ;		/* allocated extent */
	int		cl ;		/* amount used */
	int		count ;		/* number of items */
} ;

struct strtab_head {
	STRTAB_CH	*chp ;
	vechand		*clp ;		/* chunk-list-pointer */
	hdb		*hlp ;		/* hash-list-pointer */
	lookaside	*lap ;		/* lookaside-list-pointer */
	uint		magic ;
	int		chsize ;
	int		stsize ;	/* "string table" size */
	int		count ;		/* total item count */
} ; /* end struct (strtab) */

typedef STRTAB		strtab ;
typedef STRTAB_CH	strtab_ch ;

EXTERNC_begin

extern int	strtab_start(strtab *,int) noex ;
extern int	strtab_finish(strtab *) noex ;
extern int	strtab_add(strtab *,cchar *,int) noex ;
extern int	strtab_addfast(strtab *,cchar *,int) noex ;
extern int	strtab_already(strtab *,cchar *,int) noex ;
extern int	strtab_count(strtab *) noex ;
extern int	strtab_strsize(strtab *) noex ;
extern int	strtab_strmk(strtab *,char *,int) noex ;
extern int	strtab_recsize(strtab *) noex ;
extern int	strtab_recmk(strtab *,int *,int) noex ;
extern int	strtab_indlen(strtab *) noex ;
extern int	strtab_indsize(strtab *) noex ;
extern int	strtab_indmk(strtab *,int (*)[3],int,int) noex ;

EXTERNC_end


#endif /* STRTAB_INCLUDE */


