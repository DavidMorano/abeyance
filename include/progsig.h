/* progsig HEADER */
/* lang=C20 */

/* program signal handling */
/* version %I% last-modified %G% */


/* revision history:

	= 2001-11-01, David A­D­ Morano
	Originally written.

*/

/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

#ifndef	PROGSIG_INCLUDE
#define	PROGSIG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<ctime>			/* |time_t| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	PROGSIG_NENTS	30
#define	PROGSIG_NOTE	struct progsig_note

#define	PROGSIG_RMKSH	(1<<0)
#define	PROGSIG_RMMAIN	(1<<1)

#define	PROGSIG_NBUFLEN	100
#define	PROGSIG_USERLEN	100


struct progsig_note {
	time_t		stime ;
	int		type ;
	int		dlen ;
	char		dbuf[PROGSIG_NBUFLEN+1] ;
	char		user[PROGSIG_USERLEN+1] ;
} ;

EXTERNC_begin

extern int	progsig_init(void) noex ;
extern int	progsig_fini(void) noex ;

extern int	progsig_mainbegin(mainv) noex ;
extern int	progsig_mainend(void) noex ;

extern int	progsig_runmode(void) noex ;
extern int	progsig_serial(void) noex ;

extern int	progsig_adm(int) noex ;

extern int	progsig_sigquit(void) noex ;
extern int	progsig_sigterm(void) noex ;
extern int	progsig_sigintr(void) noex ;
extern int	progsig_issig(int) noex ;

extern int	progsig_noteread(PROGSIG_NOTE *,int) noex ;
extern int	progsig_notedel(int) noex ;

EXTERNC_end


#endif /* PROGSIG_INCLUDE */


