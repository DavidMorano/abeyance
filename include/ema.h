/* ema HEADER */
/* lang=C20 */

/* E-Mail Address */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-03, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	EMA_INCLUDE
#define	EMA_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<vechand.h>
#include	<localmisc.h>


#define	EMA		struct ema_head
#define	EMA_ENT		struct ema_entry
#define	EMA_FL		struct ema_flags
#define	EMA_MAGIC	0x73169284
#define	EMADEFENTS	4


enum emnatypes {
	ematype_reg,			/* regular */
	ematype_pcs,			/* PCS list */
	ematype_lalias,			/* local alias */
	ematype_salias,			/* system alias */
	ematype_group,			/* RFC-822 mail-address "group" */
	ematype_overlast
} ;

enum emaparts {
	emapart_address,
	emapart_route,
	emapart_comment,
	emapart_overlast
} ;

struct ema_head {
	vechand		*elp ;
	uint		magic ;
	int		n ;
} ;

struct ema_flags {
	uint		error:1 ;	/* address parse error */
	uint		expanded:1 ;	/* list has been expanded */
} ;

struct ema_s {
	cchar		*pp ;
	int		pl ;
} ;

struct ema_entry {
	cchar		*op ;		/* original address */
	cchar		*ap ;		/* regular address part */
	cchar		*rp ;		/* route-address part (if any) */
	cchar		*cp ;		/* comment */
	EMA		*listp ;
	EMA_FL		f ;
	int		type ;		/* mailing list type */
	int		n ;		/* number in list */
	int		ol, al, rl, cl ;
} ;

typedef EMA		ema ;
typedef EMA_ENT		ema_ent ;

EXTERNC_begin

extern int ema_starter(ema *,cchar *,int) noex ;
extern int ema_start(ema *) noex ;
extern int ema_parse(ema *,cchar *,int) noex ;
extern int ema_addent(ema *,ema_ent *) noex ;
extern int ema_addents(ema *,ema *) noex ;
extern int ema_get(ema *,int,ema_ent **) noex ;
extern int ema_getbestaddr(ema *,int,cchar **) noex ;
extern int ema_count(ema *) noex ;
extern int ema_finish(ema *) noex ;

EXTERNC_end


#endif /* EMA_INCLUDE */


