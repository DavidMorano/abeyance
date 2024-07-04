/* gethostid SUPPORT */
/* lang=C++20 */

/* get the host-ID value (a 32-bit binary number) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

	Retrieve the host ID value (a 32-bit unsigned binary integer
	value).

*******************************************************************************/

#include	<envstandards.h>	/* first to configure */
#include	<sys/types.h>		/* required by |sysctl(3)| */
#include	<sys/sysctl.h>		/* required by |sysctl(3)| */
#include	<cerrno>
#include	<cstddef>		/* <- |nullptr_t| ?? */
#include	<cstdint>		/* <- |int32_t| */
#include	<cstdio>
#include	<utypedefs.h>
#include	<clanguage.h>


/* local defines */


/* imported namespaces */

using std::nullptr_t ;			/* type */


/* exported variables */


/* exported subroutines */

long gethostid() noex {
	const nullptr_t	np{} ;
	size_t		idlen = sizeof(int32_t) ;
	int32_t		id{} ;
	if (sysctlbyname("kern.hostid",&id,&idlen,np,0uz) < 0) {
	printf("errno=%d id=%08x\n",errno,id) ;
	    id = 0 ;
	}
	printf("errno=%d id=%08x\n",errno,id) ;
	return long(id) ;
}
/* end subroutine (gethostid) */


