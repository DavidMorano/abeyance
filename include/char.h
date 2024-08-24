/* char HEADER */
/* lang=C20 */

/* fast character text and conversion facility */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-05, David A­D­ Morano
	This module was adapted from assembly lanauge.

	= 2011-08-19, David A­D­ Morano
	I changed this to use the C++ |bitset| object instead of
	an array of bytes for the single-bit truth-value observers.

*/

/* Copyright © 1998,2011 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

	This file (the header file) essentially supplies macros
	that provide the calling interface for this facility.  These
	macros provide super fast character test and conversion
	functions.  This level of speed is actually rarely needed
	since the normal corresponding UNIX®-supplied character
	subroutes are already very fast, but they are here for
	speacial needs that may arise.

	Only 8-bit characters are supported (ISO-Latin-1 character
	set).  For other character sets, use the system-supplied
	facilities.

	Extra-note: Note that non-breaking-white-space (NBSP)
	characters are *not* considered to be white-space!

******************************************************************************/

#ifndef	CHAR_INCLUDE
#define	CHAR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


/* support tables; not accessed directly by callers  */
extern const unsigned char	char_tolc[] ;
extern const unsigned char	char_touc[] ;
extern const unsigned char	char_tofc[] ;
extern const short		char_dictorder[] ;

/* test routines */
#define	CHAR_ISSPACETAB(c)	(((c) == ' ') || ((c) == '\t'))
#define	CHAR_ISWHITE(c)		char_iswhite(c)
#define	CHAR_ISLC(c)		char_islc(c)
#define	CHAR_ISUC(c)		char_isuc(c)
#define	CHAR_ISDIG(c)		char_isdig(c)

/* our super-fast conversions */
#define	CHAR_TOBC(c)		((c) & 0xff)
#define	CHAR_TOLC(c)		(char_tolc[(c) & 0xff])
#define	CHAR_TOUC(c)		(char_touc[(c) & 0xff])
#define	CHAR_TOFC(c)		(char_tofc[(c) & 0xff])
#define	CHAR_TOVAL(c)		char_toval(c) ;

/* dictionary-collating-ordinal */
#define	CHAR_DICTORDER(c)	(char_dictorder[(c) & 0xff])

EXTERNC_begin

extern bool char_iswhite(int) noex ;
extern bool char_islc(int) noex ;
extern bool char_isuc(int) noex ;

static inline bool char_isspacetab(int ch) noex {
	return CHAR_ISSPACETAB(ch) ;
}

extern int char_toval(int) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline bool char_isdig(int ch) noex {
	return ((ch >= '0') && (ch <= '9')) ;
}

#else /* __cplusplus */

static inline bool char_isdig(int ch) noex {
	return ((ch >= '0') && (ch <= '9')) ;
}

#endif /* __cplusplus */


#endif /* CHAR_INCLUDE */


