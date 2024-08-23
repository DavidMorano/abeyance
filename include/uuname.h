/* uuname HEADER */
/* lang=C20 */

/* caller interface to a UUNAME database */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UUNAME_INCLUDE
#define	UUNAME_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<modload.h>
#include	<localmisc.h>

#include	"uunames.h"


#define	UUNAME_MAGIC	0x99447243
#define	UUNAME		struct uuname_head
#define	UUNAME_CUR	struct uuname_cursor
#define	UUNAME_CALLS	struct uuname_caller


struct uuname_cursor {
	void		*scp ;		/* SO-cursor pointer */
	uint		magic ;
} ;

extern "C" {
    struct uuname_caller {
	int	(*open)(void *,cchar *,cchar *) noex ;
	int	(*count)(void *) noex ;
	int	(*exists)(void *,cchar *,int) noex ;
	int	(*curbegin)(void *,void *) noex ;
	int	(*enumerate)(void *,void *,char *,int) noex ;
	int	(*curend)(void *,void *) noex ;
	int	(*audit)(void *) noex ;
	int	(*close)(void *) noex ;
    } ;
}

struct uuname_head {
	void		*obj ;		/* object pointer */
	modload		*loader ;
	UUNAME_CALLS	call ;
	uint		magic ;
	int		objsize ;	/* object size */
	int		cursize ;	/* cursor size */
} ;

typedef	UUNAME		uuname ;
typedef	UUNAME_CUR	uuname_cur ;
typedef	UUNAME_CALLS	uuname_calls ;

EXTERNC_begin

extern int uuname_open(uuname *,cchar *,cchar *) noex ;
extern int uuname_count(uuname *) noex  ;
extern int uuname_exists(uuname *,cchar *,int) noex ;
extern int uuname_curbegin(uuname *,uuname_cur *) noex ;
extern int uuname_enum(uuname *,uuname_cur *,char *,int) noex ;
extern int uuname_curend(uuname *,uuname_cur *) noex ;
extern int uuname_audit(uuname *) noex ;
extern int uuname_close(uuname *) noex ;

EXTERNC_end


#endif /* UUNAME_INCLUDE */


