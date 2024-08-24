/* sysvar HEADER */
/* lang=C20 */

/* SYSVAR management */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSVAR_INCLUDE
#define	SYSVAR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<vecstr.h>
#include	<modload.h>
#include	<localmisc.h>

#include	"sysvars.h"


#define	SYSVAR_MAGIC	0x99447243
#define	SYSVAR		struct sysvar_head
#define	SYSVAR_CUR	struct sysvar_cursor
#define	SYSVAR_CALLS	struct sysvar_callsubs
#define	SYSVAR_FL	struct sysvar_flags

#define	SYSVAR_OPREFIX	SYSVARS_OPREFIX		/* prefix match */


struct sysvar_cursor {
	void	*scp ;		/* SO-cursor pointer */
	uint	magic ;
} ;

EXTERNC_begin
    struct sysvar_callsubs {
	int	(*open)(void *,cchar *,cchar *) ;
	int	(*count)(void *) ;
	int	(*curbegin)(void *,void *) ;
	int	(*fetch)(void *,cchar *,int,void *,char *,int) ;
	int	(*enumerate)(void *,void *,char *,int,char *,int) ;
	int	(*curend)(void *,void *) ;
	int	(*audit)(void *) ;
	int	(*close)(void *) ;
    } ;
EXTERNC_end

struct sysvar_flags {
	uint		defaults:1 ;
} ;

struct sysvar_head {
	void		*obj ;			/* object pointer */
	MODLOAD		loader ;
	vecstr		defaults ;
	SYSVAR_CALLS	call ;
	SYSVAR_FL	f ;
	uint		magic ;
	int		objsize ;		/* object size */
	int		cursize ;		/* cursor size */
} ;

typedef SYSVAR		sysvar ;
typedef SYSVAR_CUR	sysvar_cur ;
typedef SYSVAR_CALLS	sysvar_calls ;
typedef SYSVAR_FL	sysvar_fl ;

EXTERNC_begin

extern int sysvar_open(sysvar *,cchar *,cchar *) ;
extern int sysvar_count(sysvar *) ;
extern int sysvar_curbegin(sysvar *,sysvar_cur *) ;
extern int sysvar_fetch(sysvar *,cchar *,int,sysvar_cur *,char *,int) ;
extern int sysvar_enum(sysvar *,sysvar_cur *,char *,int,char *,int) ;
extern int sysvar_curend(sysvar *,sysvar_cur *) ;
extern int sysvar_audit(sysvar *) ;
extern int sysvar_close(sysvar *) ;

EXTERNC_end


#endif /* SYSVAR_INCLUDE */


