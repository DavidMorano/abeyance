/* ucopen HEADER */
/* lang=C20 */

/* additional UNIX® support */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in Apple-Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Additional (or supplemental) support for UNIX® limits.

*******************************************************************************/

#ifndef	UCOPEN_INCLUDE
#define	UCOPEN_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* |mode_t| ? */
#include	<sys/socket.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int uc_open(cchar *,int,mode_t) noex ;
extern int uc_opene(cchar *,int,mode_t,int) noex ;
extern int uc_openenv(cchar *,int,mode_t,mainv,int) noex ;
extern int uc_socket(int,int,int) noex ;
extern int uc_dupmin(int,int) noex ;
extern int uc_dupmince(int,int) noex ;
extern int uc_accepte(int,SOCKADDR *,int *,int) noex ;

extern int uc_create(cchar *,mode_t) noex ;
extern int uc_createfile(cchar *,mode_t) noex ;
extern int uc_open(cchar *,int,mode_t) noex ;
extern int uc_opene(cchar *,int,mode_t,int) noex ;
extern int uc_openex(cchar *,int,mode_t,int,int) noex ;
extern int uc_openenv(cchar *,int,mode_t,mainv,int) noex ;
extern int uc_opensocket(cchar *,int,int) noex ;
extern int uc_openproto(cchar *,int,int,int) noex ;
extern int uc_openpass(cchar *,int,int,int) noex ;
extern int uc_openuser(cchar *,cchar *,int,mode_t,int) noex ;
extern int uc_openprog(cchar *,int,mainv,mainv) noex ;
extern int uc_opendialer(cchar *,cchar *,int,mode_t,
			cchar **,cchar **,int) noex ;
extern int uc_openfsvc(cchar *,cchar *,cchar *,int,mode_t,
			cchar **,cchar **,int) noex ;
extern int uc_openusvc(cchar *,cchar *,cchar *,int,mode_t,
			cchar **,cchar **,int) noex ;
extern int uc_openfint(cchar *,cchar *,cchar *,
			cchar *, cchar *, int,mode_t,
			cchar **,cchar **,int) noex ;
extern int uc_opensys(cchar *,int,mode_t,mainv,int,int) noex ;
extern int uc_opendev(cchar *,int,mode_t,mainv,int,int) noex ;
extern int uc_opensysdb(int,int,mode_t) noex ;
extern int uc_openpt(int) noex ;

static inline int uc_dup(int fd) noex {
	return uc_dupmin(fd,0) ;
}

EXTERNC_end


#endif /* UCOPEN_INCLUDE */


