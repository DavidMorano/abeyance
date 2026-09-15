/* quote HEADER (XXX junk -- copy from CALYEARS) */
/* charset=ISO8859-1 */
/* lang=C20 (conformance reviewed) */

/* quote database operations */
/* version %I% last-modified %G% */


/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	QUOTE_INCLUDE
#define	QUOTE_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vechand.h>
#include	<vecstr.h>


#define	QUOTE		struct quote_head
#define	QUOTE_FL	struct quote_flags
#define	QUOTE_OBJ	struct quote_object
#define	QUOTE_CUR	struct quote_cursor
#define	QUOTE_MAGIC	0x99447245
#define	QUOTE_OPREFIX	0x01		/* perform a "prefix" match */


struct quote_object {
	char		*name ;
	uint		objsize ;
	uint		cursize ;
} ; /* end struct */

struct quote_cursor {
	void		*results ;
	uint		nresults ;
	uint		magic ;
	int		i ;
} ; /* end struct */

struct quote_flags {
	uint		vind : 1 ;		/* index is loaded */
} ; /* end struct */

struct quote_head {
	cchar		*pr ;
	cchar		*tmpdname ;
	char		**dirnames ;
	char		*dirstrtab ;
	vechand		dirs ;			/* directories */
	vecstr		tmpfiles ;
	QUOTE_FL	fl ;
	uint		magic ;
	int		nentries ;
	int		ncursors ;
} ; /* end struct */

typedef	QUOTE		quote ;
typedef	QUOTE_FL	quote_fl ;
typedef	QUOTE_OBJ	quote_obj ;
typedef	QUOTE_CUR	quote_cur ;

EXTERNC_begin

extern int quote_open(quote *,cchar *,cchar **,cchar **) noex ;
extern int quote_count(quote *) noex ;
extern int quote_curbegin(quote *,quote_cur *) noex ;
extern int quote_lookup(quote *,quote_cur *,int,cchar **) noex ;
extern int quote_read(quote *,quote_cur *,char *,int) noex ;
extern int quote_curend(quote *,quote_cur *) noex ;
extern int quote_check(quote *,time_t) noex ;
extern int quote_audit(quote *) noex ;
extern int quote_close(quote *) noex ;

EXTERNC_end


#endif /* QUOTE_INCLUDE */


