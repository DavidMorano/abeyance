/* ucenumsv HEADER */
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

#ifndef	UCENUMSV_INCLUDE
#define	UCENUMSV_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>

#include	<ucenumxx.h>		/* <- money shot */
#include	<ucentsv.h>		/* <- money shot */


#define	UCENUMSV		struct ucenumsv_head
#define	UCENUMSV_MAGIC		0x88776281


typedef UCENUMXX		ucenumsv ;
typedef ucentsv			ucenumsv_ent ;

EXTERNC_begin

extern int ucenumsv_open(ucenumsv *,cchar *) noex ;
extern int ucenumsv_close(ucenumsv *) noex ;
extern int ucenumsv_readent(ucenumsv *,ucenumsv_ent *,char *,int) noex ;
extern int ucenumsv_reset(ucenumsv *) noex ;

EXTERNC_end


#endif /* UCENUMSV_INCLUDE */


