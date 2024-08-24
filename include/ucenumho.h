/* ucenumho HEADER */
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

#ifndef	UCENUMHO_INCLUDE
#define	UCENUMHO_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>

#include	<ucenumxx.h>		/* <- money shot */
#include	<ucentho.h>		/* <- money shot */


#define	UCENUMHO		struct ucenumho_head
#define	UCENUMHO_MAGIC		0x88776281


typedef UCENUMXX		ucenumho ;
typedef ucentho			ucenumho_ent ;

EXTERNC_begin

extern int ucenumho_open(ucenumho *,cchar *) noex ;
extern int ucenumho_close(ucenumho *) noex ;
extern int ucenumho_readent(ucenumho *,ucenumho_ent *,char *,int) noex ;
extern int ucenumho_reset(ucenumho *) noex ;

EXTERNC_end


#endif /* UCENUMHO_INCLUDE */


