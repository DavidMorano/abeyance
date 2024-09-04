/* libmallocxx HEADER */
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

#ifndef	LIBMALLOCXX_INCLUDE
#define	LIBMALLOCXX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int libmalloc_ma(char **) noex ;	/* MA max-args */
extern int libmalloc_mn(char **) noex ;	/* MN max-name */
extern int libmalloc_mp(char **) noex ;	/* MP max-path */
extern int libmalloc_ml(char **) noex ;	/* ML max-line */
extern int libmalloc_nn(char **) noex ;	/* NN node-name */
extern int libmalloc_hn(char **) noex ;	/* HN host-name */
extern int libmalloc_un(char **) noex ;	/* UN user-name */
extern int libmalloc_gn(char **) noex ;	/* GN group-name */
extern int libmalloc_pn(char **) noex ;	/* PN project-name */
extern int libmalloc_pw(char **) noex ;	/* PW object */
extern int libmalloc_sp(char **) noex ;	/* SP object */
extern int libmalloc_ua(char **) noex ;	/* UA object */
extern int libmalloc_gr(char **) noex ;	/* GR object */
extern int libmalloc_pj(char **) noex ;	/* PJ object */
extern int libmalloc_pr(char **) noex ;	/* PR object */
extern int libmalloc_nw(char **) noex ;	/* NW object */
extern int libmalloc_ho(char **) noex ;	/* HO object */
extern int libmalloc_sv(char **) noex ;	/* SV object */
extern int libmalloc_fs(char **) noex ;	/* FS type */
extern int libmalloc_zn(char **) noex ;	/* TZ name */

extern int libmalloc_ps(char **) noex ;	/* PS pagesize */

EXTERNC_end


#endif /* LIBMALLOCXX_INCLUDE */


