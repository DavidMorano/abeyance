/* vecpstr HEADER */
/* lang=C20 */

/* vector-packed-string */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VECPSTR_INCLUDE
#define	VECPSTR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<vechand.h>


/* object defines */
#define	VECPSTR_MAGIC		0x88776215
#define	VECPSTR			struct vecpstr_head
#define	VECPSTR_CH		struct vecpstr_chunk
#define	VECPSTR_FL		struct vecpstr_flags
#define	VECPSTR_DEFENTS		10

/* options */
#define	VECPSTR_ODEFAULT	0
#define	VECPSTR_OREUSE		(1 << 0)	/* reuse empty slots */
#define	VECPSTR_OCOMPACT	(1 << 1)	/* means NOHOLES */
#define	VECPSTR_OSWAP		(1 << 2)	/* use swapping */
#define	VECPSTR_OSTATIONARY	(1 << 3)	/* entries should not move */
#define	VECPSTR_OCONSERVE	(1 << 4)	/* conserve space */
#define	VECPSTR_OSORTED		(1 << 5)	/* keep sorted */
#define	VECPSTR_OORDERED	(1 << 6)	/* keep ordered */


struct vecpstr_flags {
	uint		issorted:1 ;
	uint		oreuse:1 ;
	uint		onoholes:1 ;
	uint		oswap:1 ;
	uint		ostationary:1 ;
	uint		ocompact:1 ;
	uint		osorted:1 ;
	uint		oordered:1 ;
	uint		oconserve:1 ;
	uint		stsize:1 ;
} ;

struct vecpstr_chunk {
	char		*tab ;
	int		tabsize ;	/* tab-bytes allocated extent */
	int		tablen ;	/* tab-bytes amount used */
	int		count ;		/* number of items */
} ;

struct vecpstr_head {
	cchar		**va ;
	VECPSTR_CH	*ccp ;
	uint		magic ;
	VECPSTR_FL	f ;
	vechand		*clp ;		/* chunk-list-pointer */
	int		chsize ;
	int		an ;		/* suggested add-number */
	int		c ;		/* total item count */
	int		i ;		/* index */
	int		n ;		/* extent */
	int		fi ;		/* first-index */
	int		stsize ;	/* string table size */
} ; /* end struct (vecpstr_head) */

typedef VECPSTR		vecpstr ;
typedef VECPSTR_CH	vecpstr_ch ;

EXTERNC_begin

typedef int (*vecpstr_vcmp)(cchar **,cchar **) noex ;

extern int vecpstr_start(vecpstr *,int,int,int) noex ;
extern int vecpstr_finish(vecpstr *) noex ;
extern int vecpstr_add(vecpstr *,cchar *,int) noex ;
extern int vecpstr_adduniq(vecpstr *,cchar *,int) noex ;
extern int vecpstr_addkeyval(vecpstr *,cchar *,int,cchar *,int) noex ;
extern int vecpstr_store(vecpstr *,cchar *,int,cchar **) noex ;
extern int vecpstr_already(vecpstr *,cchar *,int) noex ;
extern int vecpstr_get(vecpstr *,int,cchar **) noex ;
extern int vecpstr_getlast(vecpstr *,cchar **) noex ;
extern int vecpstr_del(vecpstr *,int) noex ;
extern int vecpstr_delall(vecpstr *) noex ;
extern int vecpstr_count(vecpstr *) noex ;
extern int vecpstr_sort(vecpstr *,vecpstr_vcmp) noex ;
extern int vecpstr_search(vecpstr *,cchar *,vecpstr_vcmp,cchar **) noex ;
extern int vecpstr_find(vecpstr *,cchar *) noex ;
extern int vecpstr_findn(vecpstr *,cchar *,int) noex ;
extern int vecpstr_finder(vecpstr *,cchar *,vecpstr_vcmp,cchar **) noex ;
extern int vecpstr_findaddr(vecpstr *,cchar *) noex ;
extern int vecpstr_getsize(vecpstr *) noex ;
extern int vecpstr_strsize(vecpstr *) noex ;
extern int vecpstr_strmk(vecpstr *,char *,int) noex ;
extern int vecpstr_recsize(vecpstr *) noex ;
extern int vecpstr_recmk(vecpstr *,int *,int) noex ;
extern int vecpstr_recmkstr(vecpstr *,int *,int,char *,int) noex ;
extern int vecpstr_avmkstr(vecpstr *,cchar **,int,char *,int) noex ;
extern int vecpstr_indlen(vecpstr *) noex ;
extern int vecpstr_indsize(vecpstr *) noex ;
extern int vecpstr_indmk(vecpstr *,int (*)[3],int,int) noex ;
extern int vecpstr_audit(vecpstr *) noex ;
extern int vecpstr_getvec(vecpstr *,mainv *) noex ;
extern int vecpstr_finish(vecpstr *) noex ;
/* extras (so-called) */
extern int vecpstr_addpathclean(vecpstr *,cchar *,int) noex ;
extern int vecpstr_addpath(vecpstr *,cchar *,int) noex ;
extern int vecpstr_addcspath(vecpstr *) noex ;
extern int vecpstr_adds(vecpstr *,cchar *,int) noex ;
extern int vecpstr_addsubdirs(vecpstr *,cchar *) noex ;
extern int vecpstr_loaddirs(vecpstr *,cchar *) noex ;
extern int vecpstr_adduniqs(vecpstr *,cchar *,int) noex ;
extern int vecpstr_adduniqs(vecpstr *,cchar *,int) noex ;
extern int vecpstr_envadd(vecpstr *,cchar *,cchar *,int) noex ;
extern int vecpstr_envadds(vecpstr *,cchar *,int) noex ;
extern int vecpstr_envset(vecpstr *,cchar *,cchar *,int) noex ;
extern int vecpstr_envget(vecpstr *,cchar *,cchar **) noex ;
extern int vecpstr_envfile(vecpstr *,cchar *) noex ;
extern int vecpstr_foilcmp(vecpstr *,vecpstr *) noex ;
extern int vecpstr_loadfile(vecpstr *,int,cchar *) noex ;
extern int vecpstr_loadgrusers(vecpstr *,gid_t) noex ;
extern int vecpstr_srvargs(vecpstr *,cchar *) noex ;
extern int vecpstr_svcargs(vecpstr *,int *,cchar *) noex ;

EXTERNC_end


#endif /* VECPSTR_INCLUDE */


