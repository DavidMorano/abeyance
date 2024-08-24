/* ucenumsp HEADER */
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

#ifndef	UCENUMSP_INCLUDE
#define	UCENUMSP_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>

#include	<ucenumxx.h>		/* <- money shot */
#include	<ucentsp.h>		/* <- money shot */


#define	UCENUMSP		struct ucenumsp_head
#define	UCENUMSP_MAGIC		0x88776281


typedef UCENUMXX		ucenumsp ;
typedef ucentsp			ucenumsp_ent ;

EXTERNC_begin

extern int ucenumsp_open(ucenumsp *,cchar *) noex ;
extern int ucenumsp_close(ucenumsp *) noex ;
extern int ucenumsp_readent(ucenumsp *,ucenumsp_ent *,char *,int) noex ;
extern int ucenumsp_reset(ucenumsp *) noex ;

EXTERNC_end


#endif /* UCENUMSP_INCLUDE */


