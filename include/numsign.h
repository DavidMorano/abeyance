/* numsign HEADER */
/* lang=C20 */

/* number sign access */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NUMSIGN_INCLUDE
#define	NUMSIGN_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<stdintx.h>


#ifdef	__cplusplus

template<typename T>
constexpr bool numsign(T v) noex {
	cint	n = (8*sizeof(T)) ;
	return bool((v >> (n-1)) & 1) ;
}

#endif /* __cplusplus */

EXTERNC_begin

extern bool numsigni(int) noex ;
extern bool numsignl(long) noex ;
extern bool numsignll(longlong) noex ;
extern bool numsignui(uint) noex ;
extern bool numsignul(ulong) noex ;
extern bool numsignull(ulonglong) noex ;

EXTERNC_end


#endif /* NUMSIGN_INCLUDE */


