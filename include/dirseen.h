/* dirseen HEADER */
/* lang=C20 */

/* unique directory manager */
/* version %I% last-modified %G% */


/* revision history:

	= 2006-09-10, David A­D­ Morano
	I created this from hacking something that was similar that was
	originally created for a PCS program.

*/

/* Copyright © 2006 David A­D­ Morano.  All rights reserved. */

#ifndef	DIRSEEN_INCLUDE
#define	DIRSEEN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<usystem.h>
#include	<vecobj.h>


#define	DIRSEEN		struct dirseen_head
#define	DIRSEEN_CUR	struct dirseen_cursor
#define	DIRSEEN_MAGIC	0x09854123
#define	DIRSEEN_NDEF	10


struct dirseen_cursor {
	int		i ;
} ;

struct dirseen_head {
	vecobj		*dlistp ;
	uint		magic ;
	int		strsize ;
} ;

#ifdef	__cplusplus
enum dirseenmems {
	dirseenmem_start,
	dirseenmem_count,
	dirseenmem_finish,
	dirseenmem_overlast
} ;
struct dirseen_iter {
	cchar		**va = nullptr ;
	int		i = -1 ;
	int		ii = -1 ;
	dirseen_iter() = default ;
	dirseen_iter(cchar **ov,int oi,int oii) noex : va(ov), i(oi) {
	    ii = oii ;
	} ;
	dirseen_iter(const dirseen_iter &oit) noex {
	    if (this != &oit) {
		va = oit.va ;
		i = oit.i ;
		ii = oit.ii ;
	    }
	} ;
	dirseen_iter &operator = (const dirseen_iter &oit) noex {
	    if (this != &oit) {
		va = oit.va ;
		i = oit.i ;
		ii = oit.ii ;
	    }
	    return *this ;
	} ;
	bool operator != (const dirseen_iter &) noex ;
	bool operator == (const dirseen_iter &) noex ;
	cchar *operator * () noex {
	    cchar	*rp = nullptr ;
	    if (i < ii) rp = va[i] ;
	    return rp ;
	} ;
	dirseen_iter operator + (int) const noex ;
	dirseen_iter operator += (int) noex ;
	dirseen_iter operator ++ () noex ; /* pre */
	dirseen_iter operator ++ (int) noex ; /* post */
	void increment(int = 1) noex ;
} ; /* end struct dirseen_iter) */
struct dirseen ;
struct dirseen_co {
	dirseen		*op = nullptr ;
	int		w = -1 ;
	void operator () (dirseen *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	int operator () () noex ;
	operator int () noex {
	    return operator () () ;
	} ;
} ; /* end struct (dirseen_co) */
struct dirseen : dirseen_head {
	dirseen_co	start ;
	dirseen_co	count ;
	dirseen_co	finish ;
	dirseen() noex {
	    start(this,dirseenmem_start) ;
	    count(this,dirseenmem_count) ;
	    finish(this,dirseenmem_finish) ;
	} ;
	dirseen(const dirseen &) = delete ;
	dirseen &operator = (const dirseen &) = delete ;
	int add(cchar *,int,USTAT *) noex ;
	void dtor() noex ;
	~dirseen() noex {
	    dtor() ;
	} ;
} ; /* end struct (dirseen) */
typedef DIRSEEN_CUR	dirseen_cur ;
#else	/* __cplusplus */
typedef DIRSEEN		dirseen ;
typedef DIRSEEN_CUR	dirseen_cur ;
#endif /* __cplusplus */

EXTERNC_begin

extern int dirseen_start(dirseen *) noex ;
extern int dirseen_add(dirseen *,cchar *,int,USTAT *) noex ;
extern int dirseen_havename(dirseen *,cchar *,int) noex ;
extern int dirseen_havedevino(dirseen *,USTAT *) noex ;
extern int dirseen_count(dirseen *) noex ;
extern int dirseen_curbegin(dirseen *,dirseen_cur *) noex ;
extern int dirseen_curend(dirseen *,dirseen_cur *) noex ;
extern int dirseen_curenum(dirseen *,dirseen_cur *,char *,int) noex ;
extern int dirseen_finish(dirseen *) noex ;

EXTERNC_end


#endif /* DIRSEEN_INCLUDE */


