/* uux HEADER */
/* lang=C++20 */

/* SYSDIALER "uux" module */
/* version %I% last-modified %G% */


/* revision history:

	- 1996-02-01, David A­D­ Morano

	This subroutine was originally written.


*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	UUX_INCLUDE
#define	UUX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<logfile.h>
#include	<localmisc.h>

#include	"sysdialer.h"


#define	UUX_MAGIC	0x31455926
#define	UUX		struct uux_head
#define	UUX_FL		struct uux_flags


struct uux_flags {
	uint		log:1 ;
} ;

struct uux_head {
	LOGFILE		lh ;
	UUX_FL		f ;
	uint		magic ;
	int		fd ;
	int		tlen ;
} ;

typedef	UUX		uux ;
typedef	UUX_FL		uux_fl ;

EXTERNC_begin

extern int uux_open(UUX *,SYSDIALER_ARGS *,
		cchar *,cchar *,cchar **) noex ;
extern int uux_reade(UUX *,char *,int,int,int) noex ;
extern int uux_recve(UUX *,char *,int,int,int,int) noex ;
extern int uux_recvfrome(UUX *,char *,int,int,void *,int *,int,int) noex ;
extern int uux_recvmsge(UUX *,MSGHDR *,int,int,int) noex ;
extern int uux_write(UUX *,cchar *,int) noex ;
extern int uux_send(UUX *,cchar *,int,int) noex ;
extern int uux_sendto(UUX *,cchar *,int,int,void *,int) noex ;
extern int uux_sendmsg(UUX *,MSGHDR *,int) noex ;
extern int uux_shutdown(UUX *,int) noex ;
extern int uux_close(UUX *) noex ;

EXTERNC_end


#endif /* UUX_INCLUDE */


