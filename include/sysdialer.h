/* sysdialer HEADER */
/* lang=C20 */

/* system-dialer storage object */
/* version %I% last-modified %G% */


/* revision history:

	= 2003-02-01, David A­D­ Morano
	This subroutine was adopted for use from the DWD program.

*/

/* Copyright © 2003 David A­D­ Morano.  All rights reserved. */

#ifndef	SYSDIALER_INCLUDE
#define	SYSDIALER_INCLUDE


#include	<envstandards.h>
#include	<sys/types.h>
#include	<usystem.h>		/* for |ino_t| */
#include	<vecobj.h>
#include	<vecstr.h>


#define	SYSDIALER_MAGIC	31815927
#define	SYSDIALER	struct sysdialer_head
#define	SYSDIALER_FL	struct sysdialer_flags
#define	SYSDIALER_ENT	struct sysdialer_entry
#define	SYSDIALER_CALLS	struct sysdialer_calls
#define	SYSDIALER_INFO	struct sysdialer_information
#define	SYSDIALER_ARGS	struct sysdialer_arguments
#define	SYSDIALER_PRC	struct sysdialer_prcache
#define	SYSDIALER_MOD	struct sysdialer_module
#define	SYSDIALER_LF	"sysdialer"

#ifdef	COMMENT
#define	INTERFACE	struct interface
#endif

/* sysdialer flags */
#define	SYSDIALER_MFULL		0x0001
#define	SYSDIALER_MHALFOUT	0x0002
#define	SYSDIALER_MHALFIN	0x0004
#define	SYSDIALER_MCOR		0x0008
#define	SYSDIALER_MCO		0x0010
#define	SYSDIALER_MCL		0x0020
#define	SYSDIALER_MARGS		0x0040

#define	SYSDIALER_MRDONLY	SYSDIALER_MHALFIN
#define	SYSDIALER_MWRONLY	SYSDIALER_MHALFOUT


struct sysdialer_information {
	cchar		*name ;
	cchar		*version ;
	cchar		*itype ;
	int		osize ;
	int		flags ;
} ;

struct sysdialer_flags {
	uint		vsprs:1 ;
	uint		vsdirs:1 ;
} ;

struct sysdialer_prcache {
	cchar		*domainname ;
	cchar		**prs ;
} ;

struct sysdialer_head {
	cchar		*pr ;
	cchar		**dirs ;
	SYSDIALER_PRC	pc ;
	SYSDIALER_FL	f ;
	vecobj		entries ;	/* sysdialer-module names */
	vecstr		prlist ;
	vecstr		dirlist ;
	time_t		ti_lastcheck ;
	uint		magic ;
} ;

struct sysdialer_module {
	void		*dhp ;		/* SO-dlopen handle */
	dev_t		dev ;
	ino_t		ino ;
	int		count ;
} ;

struct sysdialer_entry {
	cchar		*name ;
	cchar		*itype ;
	SYSDIALER_MOD	*mp ;
	void		*callp ;
	int		osize ;		/* object size */
	int		flags ;
	int		count ;
} ;

struct sysdialer_arguments {
	cchar		*pr ;		/* program root */
	cchar		*prn ;		/* program root-name */
	cchar		*ip ;		/* interface */
	mainv		argv ;
	mainv		envv ;
	int		timeout ;
	int		options ;
} ;

#ifdef	COMMENT
struct interface {
	char		*name ;
	int		osize ;
} ;
#endif /* COMMENT */

typedef	SYSDIALER	sysdialer ;
typedef	SYSDIALER_FL	sysdialer_fl ;
typedef	SYSDIALER_ENT	sysdialer_ent ;
typedef	SYSDIALER_MOD	sysdialer_mod ;
typedef	SYSDIALER_INFO	sysdialer_info ;
typedef	SYSDIALER_ARGS	sysdialer_args ;

EXTERNC_begin

extern int sysdialer_start(sysdialer *,cchar *,cchar **,cchar **) noex ;
extern int sysdialer_loadin(sysdialer *,cchar *,sysdialer_ent **) noex ;
extern int sysdialer_loadout(sysdialer *,cchar *) noex ;
extern int sysdialer_check(sysdialer *,time_t) noex ;
extern int sysdialer_finish(sysdialer *) noex ;

EXTERNC_end


#endif /* SYSDIALER_INCLUDE */


