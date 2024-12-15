/* termcmd HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 */

/* clear out the TERMCMD object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	TERMCMD_INCLUDE
#define	TERMCMD_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	TERMCMD		struct termcmd_head
#define	TERMCMD_FL	struct termcmd_flags
#define	TERMCMD_NP	16	/* number of paramters (as per ANSI) */
#define	TERMCMD_PEOL	SHORT_MIN	/* parameter End-Of-Line (EOL) */
#define	TERMCMD_MAXPVAL	9999	/* as per ANSI */
#define	TERMCMD_ISIZE	40	/* size intermedicate-characters */
#define	TERMCMD_DSIZE	140	/* size DCS */


enum termcmdtypes {
	termcmdtype_reg,		/* regular character */
	termcmdtype_esc,		/* "escape" sequence */
	termcmdtype_csi,		/* control-sequence-introducer */
	termcmdtype_dcs,		/* device-control-string */
	termcmdtype_pf,			/* special function key (P,Q,R,S) */
	termcmdtype_overlast
} ;

struct termcmd_flags {
	uint		fpriv:1 ;	/* private CSI */
	uint		iover:1 ;	/* intermediate-string overflow */
	uint		dover:1 ;	/* device-control-string overflow */
} ;

struct termcmd_head {
	short		type ;		/* terminal-command type */
	short		name ;		/* "final" */
	TERMCMD_FL	f ;
	short		p[TERMCMD_NP] ;	/* parameters */
	char		istr[TERMCMD_ISIZE+1] ;
	char		dstr[TERMCMD_DSIZE+1] ;
} ;

typedef	TERMCMD		termcmd ;
typedef	TERMCMD_FL	termcmd_fl ;

EXTERNC_begin

extern int termcmd_clear(termcmd *) noex ;

EXTERNC_end


#endif /* TERMCMD_INCLUDE */


