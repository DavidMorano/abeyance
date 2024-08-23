/* posixdirent HEADER */
/* lang=C++20 */

/* help interface to POSIX |dirent(3c)| facility */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-23, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	See the 'cc' file for more information (and commentary) on
	this object.

*******************************************************************************/

#ifndef	POSIXDIRENT_INCLUDE
#define	POSIXDIRENT_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<dirent.h>


struct posixdirent ;

typedef int (posixdirent::*posixdirent_m)() noex ;

class posixdirent {
	posixdirent_m	m ;
	DIR		*dirp = nullptr ;
	dirent		*debuf = nullptr ;
	dirent		*dep ;
	cchar		*fname ;
	char		*nbuf ;
	off_t		*sop ;
	off_t		so ;
	int		nlen ;
	int		dfd = -1 ;
	int		delen = 0 ;
	int diropen() noex ;
	int dirclose() noex ;
	int dirread() noex ;
	int dirtell() noex ;
	int dirseek() noex ;
	int dirrewind() noex ;
	int setup(cchar *) noex ;
	int callout() noex ;
public:
	posixdirent() = default ;
	posixdirent(const posixdirent &) = delete ;
	posixdirent &operator = (const posixdirent &) = delete ;
	int open(cchar *) noex ;
	int close() noex ;
	int read(dirent *,char *,int) noex ;
	int tell(off_t *) noex ;
	int seek(off_t) noex ;
	int rewind() noex ;
	~posixdirent() noex {
	    (void) close() ;
	}
} ; /* end struct (posixdirent) */


#endif	/* __cplusplus */
#endif /* POSIXDIRENT_INCLUDE */


