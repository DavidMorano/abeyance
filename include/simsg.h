/* simsg HEADER */
/* lang=C20 */

/* messages for SIMSG requests-responses */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-07-21, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1999 David A­D­ Morano.  All rights reserved. */

#ifndef	SIMSG_INCLUDE
#define	SIMSG_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	SIMSG_SYSMISCGET	struct simsg_msggetsysmisc
#define	SIMSG_SYSMISC		struct simsg_msgsysmisc


/* request types */
enum simsgtypes {
	simsgtype_sysmiscget,
	simsgtype_sysmisc,
	simsgtype_overlast
} ;

/* response codes */
enum simsgrcs {
	simsgrc_ok,
	simsgrc_invalid,
	simsgrc_notavail,
	simsgrc_overlast
} ;

struct simsg_msggetsysmisc {
	uint	msglen ;
	uint	tag ;
	uchar	msgtype ;		/* message type */
} ;

struct simsg_msgsysmisc {
	uint	msglen ;
	uint	tag ;
	uint	mtime ;			/* data modification time */
	uint	la1m ;
	uint	la5m ;
	uint	la15m ;
	uint	btime ;
	uint	ncpu ;
	uint	nproc ;
	uchar	msgtype ;		/* message type */
	uchar	rc ;
} ;

EXTERNC_begin

extern int simsg_sysmiscget(SIMSG_SYSMISCGET *,int,char *,int) noex ;
extern int simsg_sysmisc(SIMSG_SYSMISC *,int,char *,int) noex ;

EXTERNC_end


#endif /* SIMSG_INCLUDE */


