/* stubrpc SUPPORT */
/* lang=C20 */

/* stub RPC functions */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	STUBRPC_INCLUDE
#define	STUBRPC_INCLUDE


#define	STUBRPC_KEYNETSTARG	struct key_netstarg

#ifndef	MAXNETNAMELEN
#define	MAXNETNAMELEN		255	/* maximum length network user name */
#endif

#ifndef	STUBRPC_HEXKEYBYTES
#define	STUBRPC_HEXKEYBYTES	48
#endif


struct key_netstarg {
	char		st_priv_key[STUBRPC_HEXKEYBYTES+1] ;
	char		st_pub_key[STUBRPC_HEXKEYBYTES+1] ;
	char		*st_netname ;
} ;

typedef STUBRPC_KEYNETSTARG	key_netstarg ;

EXTERNC_begin

extern int	key_secretkey_is_set(void) noex ;
extern int	key_setnet(key_netstarg *) noex ;
extern int	getnetname(char *) noex ;
extern int	getsecretkey(cchar *,char *,cchar *) noex ;

EXTERNC_end


#endif /* STUBRPC_INCLUDE */


