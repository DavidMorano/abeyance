/* libcmd HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/*
 * Copyright (c) 1997, by Sun Microsystems, Inc.
 * All rights reserved.
 */

/*
 * Declarations for the functions in libcmd.
 */

#ifndef	_LIBCMD_H
#define	_LIBCMD_H

#pragma ident	"@(#)libcmd.h 1.1	97/06/26 SMI"


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<sum.h>
#include	<localmisc.h>


EXTERNC_begin

extern int getterm(char *, char *, char *, char *) noex ;

extern int mkmtab(char *, int) noex ;
extern int ckmtab(char *, int, int) noex ;
extern void prtmtab(void) noex ;

extern void sumpro(struct suminfo *sip) noex ;
extern void sumupd(struct suminfo *, char *, int) noex ;
extern void sumepi(struct suminfo *) noex ;
extern void sumout(FILE *, struct suminfo *) noex ;

extern int defcntl(int cmd, int newflags) noex ;

EXTERNC_end


#endif /* _LIBCMD_H */


