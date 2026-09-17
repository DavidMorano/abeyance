/* pcsruns HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* PCS real-username name-server */
/* version %I% last-modified %G% */


#ifndef	PCSRUNS_INCLUDE
#define	PCSRUNS_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<vechand.h>
#include	<strpack.h>


#define	PCSRUNS		struct pcsruns_head


struct pcsruns_head {
	vechand		env ;
	strpack		stores ;
} ;

typedef	PCSRUNS		pcsruns ;

EXTERNC_begin

extern int pcsruns_start(pcsruns *,cchar *) noex ;
extern int pcsruns_lookup(pcsruns *,cchar *,int,cchar **) noex ;
extern int pcsruns_envset(pcsruns *,cchar *,cchar *,int) noex ;
extern int pcsruns_sort(pcsruns *) noex ;
extern int pcsruns_getvec(pcsruns *,cchar ***) noex ;
extern int pcsruns_finish(pcsruns *) noex ;

EXTERNC_end


#endif /* PCSRUNS_INCLUDE */


