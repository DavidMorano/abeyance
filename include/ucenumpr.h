/* ucenumpr HEADER */
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

#ifndef	UCENUMPR_INCLUDE
#define	UCENUMPR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>

#include	<ucenumxx.h>		/* <- money shot */
#include	<ucentpr.h>		/* <- money shot */


#define	UCENUMPR		struct ucentpr_head
#define	UCENUMPR_MAGIC		0x88776281


typedef UCENUMXX		ucenumpr ;
typedef ucentpr			ucenumpr_ent ;

EXTERNC_begin

extern int ucenumpr_open(ucenumpr *,cchar *) noex ;
extern int ucenumpr_close(ucenumpr *) noex ;
extern int ucenumpr_readent(ucenumpr *,ucenumpr_ent *,char *,int) noex ;
extern int ucenumpr_reset(ucenumpr *) noex ;

EXTERNC_end


#endif /* UCENUMPR_INCLUDE */


