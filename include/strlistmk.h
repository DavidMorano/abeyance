/* strlistmk HEADER */
/* lang=C20 */

/* STRLISTMK management */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRLISTMK_INCLUDE
#define	STRLISTMK_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* systems IDs */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<modload.h>

#include	"strlistmks.h"


#define	STRLISTMK		struct strlistmk_head
#define	STRLISTMK_CA		struct strlistmk_calls
#define	STRLISTMK_MAGIC		0x99447256
#define	STRLISTMK_MODBNAME	"strlistmks"
#define	STRLISTMK_OBJNAME	"strlistmks"


EXTERNC_begin
struct strlistmk_calls {
	int	(*open)(void *,cchar *,cchar *,int,mode_t,int) noex ;
	int	(*chgrp)(void *,gid_t) noex ;
	int	(*add)(void *,cchar *,int) noex ;
	int	(*abort)(void *) noex ;
	int	(*close)(void *) noex ;
} ;
EXTERNC_end

struct strlistmk_head {
	modload		*mlp ;		/* module-load-pointer */
	void		*obj ;		/* object pointer */
	STRLISTMK_CA	call ;
	uint		magic ;
	int		objsize ;	/* object size */
} ;

typedef	STRLISTMK	strlistmk ;
typedef	STRLISTMK_CA	strlistmk_ca ;

EXTERNC_begin

extern int strlistmk_open(strlistmk *,cc *,cc *,int,mode_t,int) noex ;
extern int strlistmk_chgrp(strlistmk *,gid_t) noex ;
extern int strlistmk_add(strlistmk *,cchar *,int) noex ;
extern int strlistmk_abort(strlistmk *) noex ;
extern int strlistmk_close(strlistmk *) noex ;

EXTERNC_end


#endif /* STRLISTMK_INCLUDE */


