/* ischarx HEADER */
/* lang=C20 */

/* test a character for a property */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	ISCHARX_INCLUDE
#define	ISCHARX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern bool iswhite(int) noex ;
extern bool isalnumlatin(int) noex ;
extern bool isalphalatin(int) noex ;
extern bool isdict(int) noex ;
extern bool isfnamespecial(int) noex ;
extern bool ishexlatin(int) noex ;
extern bool islowerlatin(int) noex ;
extern bool isupperlatin(int) noex ;
extern bool isnumsign(int) noex ;
extern bool isprintbad(int) noex ;
extern bool isprintlatin(int) noex ;
extern bool isprintterm(int) noex ;
extern bool iscmdstart(int) noex ;
extern bool ishdrkey(int) noex ;
extern bool	 ismmclass_7bit(int) noex ;
extern bool	 ismmclass_8bit(int) noex ;
extern bool	 ismmclass_binary(int) noex ;

static inline bool isspacetab(int ch) noex {
	return ((ch == ' ') || (ch == '\t')) ;
}

EXTERNC_end

#ifdef	__cplusplus

inline bool isdigitlatin(int ch) noex {
	return (ch >= '0') && (ch <= '9') ;
}
inline bool iseol(int ch) noex {
	return ((ch == '\n') || (ch == '\r')) ;
}
inline bool iszero(int ch) noex {
	return (ch == '0') ;
}
inline bool isplusminus(int ch) noex {
	return ((ch == '+') || (ch == '-')) ;
}

#else /* __cplusplus */

static inline bool isdigitlatin(int ch) noex {
	return (ch >= '0') && (ch <= '9') ;
}
static inline bool iseol(int ch) noex {
	return ((ch == '\n') || (ch == '\r')) ;
}
static inline bool iszero(int ch) noex {
	return (ch == '0') ;
}
static inline bool isplusminus(int ch) noex {
	return ((ch == '+') || (ch == '-')) ;
}

#endif /* __cplusplus */


#endif /* ISCHARX_INCLUDE */


