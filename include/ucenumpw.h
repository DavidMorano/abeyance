/* ucenumpw HEADER */
/* lang=C20 */

/* enumerate system SYSDB-XX entries */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-24, David A­D­ Morano
	This object module was morphed from some previous one. I
	do not remember what the previous one was.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	We enumerate (reentrantly and thread safely) system SYSDB-XX
	entries from the system SYSDB-XX database.

*******************************************************************************/

#ifndef	UCENUMPW_INCLUDE
#define	UCENUMPW_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>

#include	<ucenumxx.h>		/* <- money shot */
#include	<ucentpw.h>		/* <- money shot */


#define	UCENUMPW		struct ucenumpw_head
#define	UCENUMPW_MAGIC		0x88776281


typedef UCENUMXX		ucenumpw ;
typedef ucentpw			ucenumpw_ent ;

EXTERNC_begin

extern int ucenumpw_open(ucenumpw *,cchar *) noex ;
extern int ucenumpw_close(ucenumpw *) noex ;
extern int ucenumpw_readent(ucenumpw *,ucenumpw_ent *,char *,int) noex ;
extern int ucenumpw_reset(ucenumpw *) noex ;

EXTERNC_end


#endif /* UCENUMPW_INCLUDE */


