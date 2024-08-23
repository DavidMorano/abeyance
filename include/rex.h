/* rex HEADER */
/* lang=C20 */

/* subroutine to open a FD to a remotely executing command */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	REX_INCLUDE
#define	REX_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<netfile.h>


#define	REX_DEFEXECSERVICE		512

/* 
This flag is used in the same namespace as the |open(2)| open 
flags and therefor is pretty dangerous, but we live on the edge!
*/

#ifndef	O_KEEPALIVE
#define	O_KEEPALIVE	0x01000000
#endif /* O_KEEPALIVE */

enum rexopts {
	rexopt_keepalive = (1 << 0),
	rexopt_changedir = (1 << 1)
} ;

#define	REX_FL		struct rex_flags
#define	REX_AU		struct rex_auth


struct rex_flags {
	uint		keepalive:1 ;
	uint		changedir:1 ;
} ;

struct rex_auth {
	cchar		*res ;
	cchar		*username ;
	cchar		*password ;
	NETFILE_ENT	**machinev ;
} ;

typedef	REX_FL		rex_fl ;
typedef	REX_AU		rex_au ;

EXTERNC_begin

extern int rex(cc *,rex_au *,int,cc *,mainv,mainv,int *,
		netfile_ent **mpp) noex ;

EXTERNC_end


#endif /* REX_INCLUDE */


