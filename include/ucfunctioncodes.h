/* ucfunctioncodes HEADER */
/* lang=C20 */

/* additional UNIX® limits support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Function codes for extended Input-Output operations.

*******************************************************************************/

#ifndef	UCFUNCTIONCODES_INCLUDE
#define	UCFUNCTIONCODES_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


/* control function codes */

#define	FC_MASK		0x0000000F	/* control function mask */

#define	fc_mask		FC_MACH

/* control functions */

#define	FC_NOOP		0
#define	FC_SETMODE	1		/* set terminal mode */
#define	FC_GETMODE	2		/* retrieve current mode */
#define	FC_REESTABLISH	3		/* terminal re-establish */
#define	FC_SETRTERMS	4		/* set read terminators */
#define	FC_GETSID	5		/* get control-terminal session ID */
#define	FC_GETPGRP	6		/* get control-terminal PGRP-ID */
#define	FC_SETPGRP	7		/* set control-term PGID */
#define	FC_GETPOP	8		/* get terminal POP information */
#define	FC_SETPOP	9		/* set terminal POP information */

#define	fc_noop		FC_NOOP
#define	fc_setmode	FC_SETMODE
#define	fc_getmode	FC_GETMODE
#define	fc_reestablish	FC_REESTABLISH
#define	fc_setrterms	FC_SETRTERMS	/* set read terminators */
#define	fc_getsid	FC_GETSID
#define	fc_getpgrp	FC_GETPGRP
#define	fc_setpgrp	FC_SETPGRP
#define	fc_getpop	FC_GETPOP
#define	fc_setpop	FC_SETPOP

/* function modifiers */

#define	FM_CMDMASK	0x0F
#define	FM_OPTMASK	0xFFFFFFF0
#define	FM_MASK		FM_OPTMASK

#define	fm_mask		FM_MASK

/* function modifiers (|open| and |setmode|) */

#define	FM_LARGEFILE	(1<<(0+4))
#define	FM_QUEUE	(1<<(1+4))
#define	FM_NOREPORT	(1<<(2+4))
#define	FM_INT		(1<<(2+4))	/* set interrupt attention */
#define	FM_KILL		(1<<(3+4))	/* set control-Y attention */
#define	FM_READATT	(1<<(5+4))	/* read-attention */
#define	FM_WRITEATT	(1<<(6+4))	/* write-attention */
#define	FM_GETSTATE	(1<<(7+4))
#define	FM_CLEARSTATE	(1<<(8+4))
#define	FM_NOSIG	(1<<(9+4))	/* do not generate signals */
#define	FM_NOSIGECHO	(1<<(10+4))	/* no echo of signals */
#define	FM_NOFLOW	(1<<(11+4))	/* no output flow-control */
#define	FM_NET		(1<<(14+4))	/* specify network operation */

#define	fm_queue	FM_QUEUE	
#define	fm_noreport	FM_NOREPORT	
#define	fm_largefile	FM_LARGEFILE
#define	fm_int		FM_INT
#define	fm_kill		FM_KILL
#define	fm_readatt	FM_READATT
#define	fm_writeatt	FM_WRITEATT
#define	fm_getstate	FM_GETSTATE
#define	fm_clearstate	FM_CLEARSTATE
#define	fm_nosig	FM_NOSIG
#define	fm_nosigecho	FM_NOSIGECHO
#define	fm_noflow	FM_NOFLOW	/* no output flow control */
#define	fm_net		FM_NET

/* function modifiers (|read|) */

#define	FM_NONE		0x0000		/* no options specified */
#define	FM_ECHO		0x0000		/* echo data */
#define	FM_FILTER	0x0000		/* do canonical processing */
#define	FM_NOECHO	(1<<(0+4))	/* no echo on input */
#define	FM_NOTECHO	(1<<(1+4))	/* no terminator echo */
#define	FM_NOFILTER	(1<<(2+4))	/* no filter on input */
#define	FM_RAWIN	(1<<(3+4))	/* raw input (no control) */
#define	FM_NONBLOCK	(1<<(4+4))	/* don't start if no data */
#define	FM_TIMED	(1<<(5+4))	/* timed read */
#define	FM_EXACT	(1<<(6+4))	/* exact transfer length */
#define	FM_AGAIN	(1<<(7+4))	/* return AGAIN if no data */
#define	FM_SLOWPOLL	(1<<(8+4))	/* perform slower polling */
#define	FM_TIMEINT	(1<<(9+4))	/* set time-out interval */
#define	FM_SETMSG	(1<<(10+4))	/* set messages on terminal (what?) */
#define	FM_NOFILTECHO	(1<<(11+4))	/* do not echo filter operations */

#define	fm_none		FM_NONE
#define	fm_echo		FM_ECHO
#define	fm_filter	FM_FILTER
#define	fm_noecho	FM_NOECHO
#define	fm_notecho	FM_NOTECHO
#define	fm_nofilter	FM_NOFILTER
#define	fm_rawin	FM_RAWIN
#define	fm_nonblock	FM_NONBLOCK
#define	fm_timed	FM_TIMED
#define	fm_exact	FM_EXACT
#define	fm_again	FM_AGAIN
#define	fm_slowpoll	FM_SLOWPOLL
#define	fm_timeint	FM_TIMEINT	/* set time-out interval */
#define	fm_setmsg	FM_SETMSG	/* what is this? */
#define	fm_nofiltecho	FM_NOFILTECHO	/* do not echo filter operations */

/* function modifiers (|write|) */

#define	FM_CCO		(1<<(0+4))	/* cancel output cancel */
#define	FM_RAWOUT	(1<<(1+4))	/* raw output */

#define	fm_cco		FM_CCO
#define	fm_rawout	FM_RAWOUT

/* function modifiers (|status|) */

/* function modifiers (|cancel|) */

#define	FM_CANALL	(1<<(0+4))	/* cancel all requests w/ FC */
#define	FM_ALL		FM_CANALL	/* cancel all requests w/ FC */

#define	fm_canall	FM_CANALL
#define	fm_all		FM_ALL


#endif /* UCFUNCTIONCODES_INCLUDE */


