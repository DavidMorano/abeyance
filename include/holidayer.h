/* holidayer HEADER */
/* lang=C++20 */

/* access for the HOLIDAYER database */
/* version %I% last-modified %G% */


/* Copyright © 2016 David A­D­ Morano.  All rights reserved. */

#ifndef	HOLIDAYER_INCLUDE
#define	HOLIDAYER_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<usystem.h>
#include	<ids.h>
#include	<vechand.h>
#include	<localmisc.h>

#include	"holidays.h"


#define	HOLIDAYER_MAGIC	0x63328184
#define	HOLIDAYER	struct holidayer_head
#define	HOLIDAYER_FL	struct holidayer_flags
#define	HOLIDAYER_OBJ	struct holidayer_object
#define	HOLIDAYER_CUR	struct holidayer_cursor
#define	HOLIDAYER_CITE	HOLIDAYS_CITE


struct holidayer_object {
	cchar		*name ;
	uint		objsize ;
	uint		cursize ;
} ;

struct holidayer_cursor {
	uint		magic ;
	holidays_cur	hcur ;
	holidays	*hop ;
	uint		year ;
} ;

struct holidayer_flags {
	uint		hols:1 ;
} ;

struct holidayer_head {
	cchar		*pr ;
	ids		id ;
	vechand		hols ;
	HOLIDAYER_FL	f ;
	uint		magic ;
	uint		year ;
	int		ncursors ;
} ;

typedef	HOLIDAYER	holidayer ;
typedef	HOLIDAYER_FL	holidayer_fl ;
typedef	HOLIDAYER_OBJ	holidayer_obj ;
typedef	HOLIDAYER_CUR	holidayer_cur ;
typedef	HOLIDAYER_CITE	holidayer_cite ;

EXTERNC_begin

extern int holidayer_open(holidayer *,cchar *) noex ;
extern int holidayer_curbegin(holidayer *,holidayer_cur *) noex ;
extern int holidayer_curend(holidayer *,holidayer_cur *) noex ;
extern int holidayer_fetchcite(holidayer *,holidayer_cite *,
		holidayer_cur *,char *,int) noex ;
extern int holidayer_fetchname(holidayer *,uint,cchar *,int,
		holidayer_cur *,holidayer_cite *,char *,int) noex ;
extern int holidayer_enum(holidayer *,holidayer_cur *,
		holidayer_cite *,char *,int,uint) noex ;
extern int holidayer_check(holidayer *,time_t) noex ;
extern int holidayer_audit(holidayer *) noex ;
extern int holidayer_close(holidayer *) noex ;

EXTERNC_end


#endif /* HOLIDAYER_INCLUDE */


