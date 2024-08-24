/* nlsmsg HEADER */
/* lang=C20 */

/* information to create and read an NLS-connect message */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

	This header file contains some pre-processor defines used to
	create an NLS connection message and to parse the result.

	Definitions:
	NLPS		Network-Listener-Process-Server
	NLS		Network-Listener-Service

*******************************************************************************/

#ifndef	NLSMSG_INCLUDE
#define	NLSMSG_INCLUDE


/* this is the NLS dial-out connection-request string-prefix */
#define	NLSDIALSTR	"NLPS:002:002:"

/* these are some kind of NLS codes */
#define	NLSSTART	0
#define	NLSFORMAT	2
#define	NLSUNKNOWN	3
#define	NLSDISABLED	4

/* these are environment variables passed down to a NLPS sub-servier */
#define	NLSADDR		"NLSADDR"
#define	NLSOPT		"NLSOPT"
#define	NLSUDATA	"NLSUDATA"
#define	NLSPROVIDER	"NLSPROVIDER"


#endif /* NLSMSG_INCLUDE */


