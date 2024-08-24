/* inetaddrparse HEADER */
/* lang=C20 */

/* this little thing parses an INET address into parts */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	INETADDRPARSE_INCLUDE
#define	INETADDRPARSE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>


#define	INETADDRPARSE		struct inetaddrparse_head
#define	INETADDRPARSE_SO	struct inetaddrparse_strobj


struct inetaddrparse_strobj {
	cchar		*sp ;
	int		sl ;
} ;

struct inetaddrparse_head {
	INETADDRPARSE_SO	af, host, port ;
} ;

typedef INETADDRPARSE		inetaddrparse ;
typedef INETADDRPARSE_SO	inetaddrparse_so ;

EXTERNC_begin

extern int inetaddrparse_load(inetaddrparse *,cchar *,int) noex ;

EXTERNC_end


#endif /* INETADDRPARSE_INCLUDE */


