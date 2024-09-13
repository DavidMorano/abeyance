/* ccfile HEADER */
/* lang=C++20 */

/* C++ file I-O operations */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-10, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CCFILE_INCLUDE
#define	CCFILE_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* MUST be first to configure */
#include	<unistd.h>		/* for |off_t| */
#include	<fstream>
#include	<string>
#include	<string_view>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


enum ccfilemems {
	ccfilemem_rewind,
	ccfilemem_close,
	ccfilemem_overlast
} ;

struct ccfile ;

struct ccfile_co {
        ccfile		*op = nullptr ;
        int             w = -1 ;
        void operator () (ccfile *p,int m) noex {
            op = p ;
            w = m ;
        } ;
        int operator () (int a = -1) noex ;
        operator int () noex {
	    return operator () () ;
        } ;
} ; /* end struct (ccfile_co) */

struct ccfile : std::fstream {
	typedef std::string_view	strview ;
	friend		ccfile_co ;
	ccfile_co	rewind ;
	ccfile_co	close ;
	bool		freading = false ;
	ccfile() noex {
	    rewind(this,ccfilemem_rewind) ;
	    close(this,ccfilemem_close) ;
	} ;
	ccfile(const ccfile &) = delete ;
	ccfile &operator = (const ccfile &) = delete ;
	int open(cchar *,cchar * = nullptr,mode_t = 0) noex ;
	int open(const strview,cchar * = nullptr,mode_t = 0) noex ;
	int readln(char *,int,int = 0) noex ;
	int readln(std::string &,int = 0) noex ;
	int seek(off_t = 0z,int = -1) noex ;
	void dtor() noex ;
	~ccfile() {
	    dtor() ;
	} ;
private:
	int irewind() noex ;
	int iclose() noex ;
} ; /* end class (ccfile) */


#endif /* __cplusplus */
#endif /* CCFILE_INCLUDE */


