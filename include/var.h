/* var HEADER */
/* lang=C20 */

/* VAR management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VAR_INCLUDE
#define	VAR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>
#include	<modload.h>
#include	<localmisc.h>

#include	"vars.h"


#define	VAR_MAGIC	0x99447246
#define	VAR		struct var_head
#define	VAR_CUR		struct var_cursor
#define	VAR_INFO	struct var_information
#define	VAR_CALLS	struct var_callsubs

#define	VARINFO		struct varinfo


struct var_information {
	time_t		wtime ;
	time_t		mtime ;
	uint		nvars ;
	uint		nskip ;
} ;

struct var_cursor {
	void		*scp ;		/* SO-cursor pointer */
	uint		magic ;
} ;

struct var_callsubs {
	int	(*open)(void *,cchar *) ;
	int	(*opena)(void *,cchar **) ;
	int	(*count)(void *) ;
	int	(*curbegin)(void *,void *) ;
	int	(*fetch)(void *,cchar *,int,void *,char *,int) ;
	int	(*enumerate)(void *,void *,char *,int,char *,int) ;
	int	(*curend)(void *,void *) ;
	int	(*info)(void *,VARS_INFO *) ;
	int	(*audit)(void *) ;
	int	(*close)(void *) ;
} ;

struct var_head {
	modload		loader ;
	VAR_CALLS	call ;
	void		*obj ;		/* object pointer */
	uint		magic ;
	int		objsize ;	/* object size */
	int		cursize ;	/* cursor size */
} ;

struct varinfo {
	long		size ;
	time_t		mtime ;
} ;

typedef	VAR		var ;
typedef VAR_CUR		var_cur ;
typedef VAR_INFO	var_info ;
typedef VAR_CALLS	var_calls ;

EXTERNC_begin

extern int	var_open(var *,cchar *) noex ;
extern int	var_opena(var *,cchar **) noex ;
extern int	var_count(var *) noex ;
extern int	var_curbegin(var *,var_cur *) noex ;
extern int	var_fetch(var *,cchar *,int,var_cur *,char *,int) noex ;
extern int	var_enum(var *,var_cur *,char *,int,char *,int) noex ;
extern int	var_curend(var *,var_cur *) noex ;
extern int	var_info(var *,var_info *) noex ;
extern int	var_audit(var *) noex ;
extern int	var_close(var *) noex ;

extern int	varinfo(VARINFO *,cchar *,int) noex ;
extern int	varunlink(cchar *,int) noex ;

EXTERNC_end


#endif /* VAR_INCLUDE */


