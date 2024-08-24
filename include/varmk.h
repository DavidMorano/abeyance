/* varmk HEADER */
/* lang=C20 */

/* VARMK management */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	VARMK_INCLUDE
#define	VARMK_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/param.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<modload.h>

#include	"varmks.h"


#define	VARMK		struct varmk_head
#define	VARMK_CALLS	struct varmk_callsubs
#define	VARMK_MAGIC	0x99447246


struct varmk_callsubs {
	int	(*open)(void *,cchar *,int,mode_t,int) ;
	int	(*chgrp)(void *,gid_t) ;
	int	(*addvar)(void *,cchar *,cchar *,int) ;
	int	(*abort)(void *) ;
	int	(*close)(void *) ;
} ;

struct varmk_head {
	MODLOAD		loader ;
	VARMK_CALLS	call ;
	void		*sop ;		/* shared-object (SO) pointer */
	void		*obj ;		/* object pointer */
	uint		magic ;
	int		objsize ;	/* object size */
} ;

typedef VARMK		varmk ;
typedef VARMK_CALLS	varmk_calls ;

EXTERNC_begin

extern int	varmk_open(VARMK *,cchar *,int,mode_t,int) noex ;
extern int	varmk_chgrp(VARMK *,gid_t) noex ;
extern int	varmk_addvar(VARMK *,cchar *,cchar *,int) noex ;
extern int	varmk_abort(VARMK *) noex ;
extern int	varmk_close(VARMK *) noex ;

EXTERNC_end


#endif /* VARMK_INCLUDE */


