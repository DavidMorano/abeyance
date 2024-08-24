/* mkx HEADER */
/* lang=C20 */

/* provided are various general c-string creation subroutines */
/* version %I% last-modified %G% */


/* revision history:

  = 2000-05-14, David A-D- Morano
	This was written for Rightcore Network Services (RNS).
 
  = 2018-11-27, David A-D- Morano
	I created an inline version for the C language. We will
	likely do something for C++ at some other time.

  = 2023-10-23, David A-D- Morano
	At some point I added an inline (here) for the C++ language.

*/

/* Copyright © 1998,2018,23023 David A-D- Morano.  All rights reserved. */

#ifndef	MKX_INCLUDE
#define	MKX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>

#include	<mklogid.h>
#include	<mkgecosname.h>
#include	<mkcexsync.h>
#include	<mkuuid.h>
#include	<mkutmpid.h>
#include	<mkquoted.h>
#include	<mkprogenv.h>
#include	<mkpathxw.h>
#include	<mkpathx.h>
#include	<mkpathrooted.h>
#include	<mknpathxw.h>
#include	<mknpathx.h>
#include	<mkmagic.h>
#include	<mkfname.h>
#include	<mkfnamesuf.h>
#include	<mkfdfname.h>
#include	<mkdisplayable.h>
#include	<mknpath.h>
#include	<mkpath.h>
#include	<mkchar.h>
#include	<mkaddr.h>


EXTERNC_begin

extern int	mkrealname(char *,int,cchar *,int) noex ;
extern int	mknoise(uint *a,int n) noex ;
extern int	mkbasename(char *,cchar *,int) noex ;
extern int	mkshlibname(char *,cchar *,int) noex ;
extern int	mksofname(char *,cchar *,cchar *,cchar *) noex ;
extern int	mkintfname(char *,cchar *,cchar *,cchar *) noex ;
extern int	mktagfname(char *,cchar *,cchar *,int) noex ;
extern int	mkmid(char *,int,cchar *,cchar *,pid_t,int) noex ;
extern int	mkonefrom(char *,int,cchar *,int) noex ;
extern int	mkmailname(char *,int,cchar *,int) noex ;
extern int	mkvarpath(char *,cchar *,int) noex ;
extern int	mkexpandpath(char *,cchar *,int) noex ;
extern int	mkuserpath(char *,cchar *,cchar *,int) noex ;
extern int	mkufname(char *,cchar *,cchar *) noex ;
extern int	mkaltext(char *,cchar *,cchar *) noex ;
extern int	mkufname(char *,cchar *,cchar *) noex ;
extern int	mkaltext(char *,cchar *,cchar *) noex ;
extern int	mkmaildirtest(char *,cchar *,int) noex ;
extern int	mkstrunique(char *,int) noex ;
extern int	mkcleanline(char *,int,int) noex ;
extern int	mkfmtphone(char *,int,cchar *,int) noex ;
extern int	mkfingerquery(char *,int,int,cchar *,mainv) noex ;

/* obsolete */
extern int	mkcaselower(char *,int) noex ;
extern int	mkrevstr(char *,int) noex ;

EXTERNC_end


#endif /* MKX_INCLUDE */


