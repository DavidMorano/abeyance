/* icalmk HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 */

/* make a iCalendar (ICS) database file */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ICALMK_INCLUDE
#define	ICALMK_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vecobj.h>


#define	ICALMK_MAGIC	0x88773422
#define	ICALMK		struct icalmk_head
#define	ICALMK_OBJ	struct icalmk_object
#define	ICALMK_ENT	struct icalmk_entry
#define	ICALMK_LN	struct icalmk_liner
#define	ICALMK_FL	struct icalmk_flags


struct icalmk_object {
	cchar		*name ;
	uint		objsize ;
} ;

struct icalmk_liner {
	uint		loff ;
	uint		llen ;
} ;

struct icalmk_entry {
	ICALMK_LN	*lines ;
	uint		voff ;
	uint		vlen ;
	uint		hash ;
	uchar		nlines, m, d ;
} ;

struct icalmk_flags {
	uint		viopen:1 ;
	uint		notsorted:1 ;
	uint		tmpfile:1 ;
	uint		creat:1 ;
	uint		excl:1 ;
	uint		none:1 ;
	uint		inprogress:1 ;
	uint		created:1 ;
} ;

struct icalmk_head {
	cchar		*calname ;
	cchar		*dbname ;
	cchar		*idname ;
	cchar 		*cyifname ;
	char		*nfname ;
	vecobj		verses ;
	vecobj		lines ;
	ICALMK_FL	f ;
	uint		pcitation ;
	uint		magic ;
	int		nentries ;
	int		operms ;
	int		nfd ;
	int		year ;
} ;

typedef	ICALMK		icalmk ;
typedef	ICALMK_OBJ	icalmk_obj ;
typedef	ICALMK_ENT	icalmk_en ;
typedef	ICALMK_LN	icalmk_ln ;
typedef	ICALMK_FL	icalmk_fl ;

EXTERNC_begin

extern int	icalmk_open(icalmk *,cchar *,cchar *,int,int,int,int) noex ;
extern int	icalmk_add(icalmk *,icalmk_ent *) noex ;
extern int	icalmk_close(icalmk *) noex ;

EXTERNC_end


#endif /* ICALMK_INCLUDE */


