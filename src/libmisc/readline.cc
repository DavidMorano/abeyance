/* readline SUPPORT */
/* lang=C++11 */

/* read a line from a file */
/* version %I% last-modified %G% */


/* revision history:

	= 2013-07-11, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2013 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	readline

	Synopsis:
	int readline(ifstream &is,char *lbuf,int llen) noex

	Arguments:
	is		reference to stream (file)
	lbuf		buffer to receive
	llen		length of supplied buffer

	Returns:
	-		lenght of bytes read

*******************************************************************************/

#include	<envstandards.h>
#include	<climits>
#include	<cinttypes>
#include	<new>
#include	<initializer_list>
#include	<utility>
#include	<functional>
#include	<algorithm>
#include	<vector>
#include	<string>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<usystem.h>
#include	<localmisc.h>


/* local defines */


/* name-spaces */

using namespace std ;


/* external subroutines */


/* global variables */


/* local structures (and methods) */


/* forward references */


/* local variables */


/* exported variables */


/* exported subroutines */

int readline(ifstream &is,char *lbuf,int llen) noex {
	int		rs = SR_OK ;
	if (is.getline(lbuf,llen)) {
	    rs = is.gcount() ;
	}
	return rs ;
}
/* end subroutine (readline) */


