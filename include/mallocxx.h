/* mallocxx HEADER */
/* lang=C20 */

/* interface component for UNIX® library-3c */
/* version %I% last-modified %G% */


/* revision history:

	= 2014-06-17, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 2014 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This module provides some subroutines to serve as short-cuts to
	allocating system buffers (that is: buffers that are used by
	the UNIX® system with their particular buffer-sizes).


*******************************************************************************/

#ifndef	MALLOCXX_INCLUDE
#define	MALLOCXX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int malloc_ma(char **) noex ;		/* MA max-args */
extern int malloc_mn(char **) noex ;		/* MN max-name */
extern int malloc_mp(char **) noex ;		/* MP max-path */
extern int malloc_ml(char **) noex ;		/* ML max-line */
extern int malloc_nn(char **) noex ;		/* NN node-name */
extern int malloc_hn(char **) noex ;		/* HN host-name */
extern int malloc_un(char **) noex ;		/* UN user-name */
extern int malloc_gn(char **) noex ;		/* GN group-name */
extern int malloc_pn(char **) noex ;		/* PN project-name */
extern int malloc_pw(char **) noex ;		/* PW object */
extern int malloc_sp(char **) noex ;		/* SP object */
extern int malloc_ua(char **) noex ;		/* UA object */
extern int malloc_gr(char **) noex ;		/* GR object */
extern int malloc_pj(char **) noex ;		/* PJ object */
extern int malloc_pr(char **) noex ;		/* PR object */
extern int malloc_nw(char **) noex ;		/* NW object */
extern int malloc_ho(char **) noex ;		/* HO object */
extern int malloc_sv(char **) noex ;		/* SV object */
extern int malloc_fs(char **) noex ;		/* FS type */
extern int malloc_zn(char **) noex ;		/* TZ name */

extern int malloc_ps(char **) noex ;		/* pagesize */
extern int malloc_mailaddr(char **) noex ;	/* mail address */

EXTERNC_end


#endif /* MALLOCXX_INCLUDE */


