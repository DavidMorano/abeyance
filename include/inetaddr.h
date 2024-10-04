/* inetaddr HEADER */
/* lang=C20 */

/* object to manipulate INET adresses */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	INETADDR_INCLUDE
#define	INETADDR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<netinet/in.h>
#include	<netdb.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	INETADDR	union inetaddr_head


struct inetaddr_head {
	union {
	    struct in_addr	a ;
	    char		straddr[sizeof(struct in_addr)] ;
	} ;
} ;


#ifdef	__cplusplus
enum inetaddrmems {
	inetaddrmem_finish,
	inetaddrmem_overlast
} ;
struct inetaddr ;
struct inetaddr_co {
	inetaddr	*op = nullptr ;
	int		w = -1 ;
	void operator () (inetaddr *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (inetaddr_co) */
struct inetaddr : inetaddr_head {
	inetaddr_co	finish ;
	inetaddr() noex {
	    finish(this,inetaddrmem_finish) ;
	} ;
	inetaddr(const inetaddr &) = delete ;
	inetaddr &operator = (const inetaddr &) = delete ;
	int start(cvoid *) noex ;
	int startstr(cchar *,int = -1) noex ;
	int startdot(cchar *,int = -1) noex ;
	int gethexaddr(char *,int) noex ;
	int getdotaddr(char *,int) noex ;
} ; /* end struct (inetaddr) */
#else /* __cplusplus */
typedef INETADDR	inetaddr ;
#endif /* __cplusplus */

EXTERNC_begin

extern int inetaddr_start(inetaddr *,cvoid *) noex ;
extern int inetaddr_startstr(inetaddr *,cchar *,int) noex ;
extern int inetaddr_startdot(inetaddr *,cchar *,int) noex ;
extern int inetaddr_gethexaddr(inetaddr *,char *,int) noex ;
extern int inetaddr_getdotaddr(inetaddr *,char *,int) noex ;
extern int inetaddr_finish(inetaddr *) noex ;

EXTERNC_end


#endif /* INETADDR_INCLUDE */


