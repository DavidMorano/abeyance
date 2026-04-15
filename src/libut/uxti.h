/* uxti HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* additional UNIX® limits support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Group:
	uxti

	Description:
	Additional (or supplemental) support for UNIX® limits.

*******************************************************************************/

#ifndef	UXTI_INCLUDE
#define	UXTI_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>

#if	defined(SYSHAS_XTI) && (SYSHAS_XTI > 0)
#include	<xti.h>
#endif


#ifndef	TBADF
#define	TBADF		0
#endif
#ifndef	TSYSERR
#define	TSYSERR		0
#endif


EXTERNC_begin

extern int	ut_alloc(int,int,int,void **) noex ;
extern int	ut_open(cchar *,int,struct t_info *) noex ;
extern int	ut_bind(int,struct t_bind *,struct t_bind *) noex ;
extern int	ut_listen(int,struct t_call *) noex ;
extern int	ut_connect(int,struct t_call *,struct t_call *) noex ;
extern int	ut_accept(int,int,const struct t_call *) noex ;
extern int	ut_look(int) noex ;
extern int	ut_sync(int) noex ;
extern int	ut_close(int) noex ;
extern int	ut_free(void *,int) noex ;

EXTERNC_end


#endif /* UXTI_INCLUDE */


