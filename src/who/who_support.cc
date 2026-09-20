/* utmp_support SUPPORT (who) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* support */
/* version %I% last-modified %G% */


/* revision history:

	= 2023-12-15, David A-D- Morano
	This is originally written.

*/

/* Copyright © 2023 David A-D- Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

	Names:
	snadd
	snaddw

	Description:
	Support subroutines.

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>		/* |struct passwd| */
#include	<sys/stat.h>		/* <- for |USTAT| */
#include	<sys/mman.h>
#include	<unistd.h>		/* <- for |ttyname_r(3c)| */
#include	<cstdlib>		/* <- for |EXIT_SUCCESS| */
#include	<cstdio>		/* <- for |printf(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>		/* |TIMEBUFLEN| */

#pragma		GCC dependency		"mod/umisc.ccm"

import umisc ;				/* |snaddw(3u)| */

/* local defines */


/* imported namespaces */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

    extern int mac_snaddw(char *dp,int dl,int i,cchar *sp,int sl) noex {
	return snaddw(dp,dl,i,sp,sl) ;
    }


