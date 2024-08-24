/* opendial HEADER */
/* lang=C++20 */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	This subroutine was written for Rightcore Network Services (RNS).

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	OPENDIAL_INCLUDE
#define	OPENDIAL_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<localmisc.h>


/* options */
#define	OPENDIAL_OLONG		(1<<0)		/* FINGER "long" option */


enum opendialers {
	opendialer_unspec,
	opendialer_udp,
	opendialer_tcp,
	opendialer_tcpmux,
	opendialer_tcpnls,
	opendialer_uss,
	opendialer_ussmux,
	opendialer_ussnls,
	opendialer_ticotsord,
	opendialer_ticotsordnls,
	opendialer_pass,
	opendialer_open,
	opendialer_prog,
	opendialer_finger,
	opendialer_overlast
} ;

EXTERNC_begin

extern int opendial(int,int,cc *,cc *,cc *,mainv,mainv,int,int) noex ;

EXTERNC_end


#endif /* OPENDIAL_INCLUDE */


