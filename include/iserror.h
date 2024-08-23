/* iserror HEADER */
/* lang=C20 */

/* is an error code (per an integer) a part of a class of errors? */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ISERROR_INCLUDE
#define	ISERROR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>


EXTERNC_begin

extern bool isFailOpen(int) noex ;
extern bool isFailConn(int) noex ;
extern bool isBadSend(int) noex ;
extern bool isBadRecv(int) noex ;
extern bool isBadMsg(int) noex ;
extern bool isIOError(int) noex ;

EXTERNC_end


#endif /* ISERROR_INCLUDE */


