/* shellunder HEADER */
/* lang=C20 */

/* parse a c-string into the shell-under information components */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SHELLUNDER_INCLUDE
#define	SHELLUNDER_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* system-types */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	SHELLUNDER_DAT	struct shellunder_data


struct shellunder_data {
	cchar		*progename ;	/* child program exec-name */
	pid_t		pid ;		/* parent (shell) PID */
} ;

typedef	SHELLUNDER_DAT	shellunder_dat ;

EXTERNC_begin

extern int	shellunder_wr(shellunder_dat *,cchar *) noex ;

EXTERNC_end


#endif /* SHELLUNDER_INCLUDE */


