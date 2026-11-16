/* strfilemk HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* STRFILEMK management */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STRFILEMK_INCLUDE
#define	STRFILEMK_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* POSIX® system types */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */

#include	"strfilemks.h"


#define	STRFILEMK	struct strfilemk_head
#define	STRFILEMK_FL	struct strfilemk_flags
#define	STRFILEMK_MAGIC	0x99447256


struct strfilemk_flags {
        uint            modload:1 ;
} ; /* end struct */

struct strfilemk_head {
	modload		*mlp ;
	void		*callp ;
	void		*obj ;		/* object pointer */
	STRFILEMK_FL	fl ;
	uint		magval ;
	int		objsz ;		/* object size */
	int		cursz ;		/* cursor size */
} ; /* end struct (strfilemk_head) */

typedef	STRFILEMK	strfilemk ;
typedef	STRFILEMK_FL	strfilemk_fl ;

EXTERNC_begin

extern int strfilemk_open	(strfilemk *,cchar *,int,mode_t,int) noex ;
extern int strfilemk_chgrp	(strfilemk *,gid_t) noex ;
extern int strfilemk_addfile	(strfilemk *,cchar *,int) noex ;
extern int strfilemk_count	(strfilemk *) noex ;
extern int strfilemk_abort	(strfilemk *) noex ;
extern int strfilemk_close	(strfilemk *) noex ;

EXTERNC_end


#endif /* STRFILEMK_INCLUDE */


