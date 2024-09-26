/* varsub HEADER */
/* lang=C20 */

/* module to handle variable substitution in strings */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VARSUB_INCLUDE
#define	VARSUB_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<vechand.h>
#include	<buffer.h>
#include	<bfile.h>
#include	<localmisc.h>


/* object defines */
#define	VARSUB			struct varsub_head
#define	VARSUB_FL		struct varsub_flags
#define	VARSUB_CUR		struct varsub_cursor
#define	VARSUB_MAGIC		91827364

/* initialization options */
#define	VARSUB_OBLANK		0	/* default, substitute blank */
#define	VARSUB_ONOBLANK		(1<<0)	/* substitute the key on failure */
#define	VARSUB_OBADNOKEY	(1<<1)	/* fail out on failure */
#define	VARSUB_OBRACE		(1<<2)	/* substitute on braces */
#define	VARSUB_OPAREN		(1<<3)	/* substitute on parentheses */


struct varsub_flags {
	uint		badnokey:1 ;
	uint		noblank:1 ;
	uint		brace:1 ;
	uint		paren:1 ;
	uint		sorted:1 ;
} ;

struct varsub_cursor {
	int		i ;
} ;

struct varsub_head {
	vechand		*slp ;
	VARSUB_FL	f ;
	uint		magic ;
	int		n ;		/* current allocated length */
	int		i ;		/* maximum length used */
	int		badline ;
} ;


typedef VARSUB		varsub ;
typedef	VARSUB_FL	varsub_fl ;
typedef VARSUB_CUR	varsub_cur ;

EXTERNC_begin

extern int	varsub_start(varsub *,int) noex ;
extern int	varsub_add(varsub *,cchar *,int,cchar *,int) noex ;
extern int	varsub_addva(varsub *,mainv) noex ;
extern int	varsub_addquick(varsub *,cchar *,int,cchar *,int) noex ;
extern int	varsub_addvaquick(varsub *,cchar **) noex ;
extern int	varsub_curbegin(varsub *,varsub_cur *) noex ;
extern int	varsub_curenum(varsub *,varsub_cur *,cchar **,cchar **) noex ;
extern int	varsub_curend(varsub *,varsub_cur *) noex ;
extern int	varsub_del(varsub *,cchar *,int) noex ;
extern int	varsub_fetch(varsub *,cchar *,int,cchar **) noex ;
extern int	varsub_exp(varsub *,char *,int,cchar *,int) noex ;
extern int	varsub_expbuf(varsub *,buffer *,cchar *,int) noex ;
extern int	varsub_expfile(varsub *,bfile *,bfile *) noex ;
extern int	varsub_finish(varsub *) noex ;

EXTERNC_end


#endif /* VARSUB_INCLUDE */


