/* netorder HEADER */
/* lang=C++20 */

/* network byte order manipulations */
/* version %I% last-modified %G% */


/* Copyright © 2001 David A­D­ Morano.  All rights reserved. */

#ifndef	NETORDER_INCLUDE
#define	NETORDER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<limits.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>
#include	<localmisc.h>


#define	NETORDER	char *

EXTERNC_begin

extern int netorder_rc(char *,char *) noex ;
extern int netorder_rs(char *,short *) noex ;
extern int netorder_ri(char *,int *) noex ;
extern int netorder_rl(char *,long *) noex ;
extern int netorder_rll(char *,longlong *) noex ;

extern int netorder_ruc(char *,uchar *) noex ;
extern int netorder_rus(char *,ushort *) noex ;
extern int netorder_rui(char *,uint *) noex ;
extern int netorder_rul(char *,ulong *) noex ;
extern int netorder_rull(char *,ulonglong *) noex ;

extern int netorder_wc(char *,int) noex ;
extern int netorder_ws(char *,int) noex ;
extern int netorder_wi(char *,int) noex ;
extern int netorder_wl(char *,long) noex ;
extern int netorder_wll(char *,longlong) noex ;

extern int netorder_wuc(char *,uint) noex ;
extern int netorder_wus(char *,uint) noex ;
extern int netorder_wui(char *,uint) noex ;
extern int netorder_wul(char *,ulong) noex ;
extern int netorder_wull(char *,ulonglong) noex ;

EXTERNC_end


#endif /* NETORDER_INCLUDE */


