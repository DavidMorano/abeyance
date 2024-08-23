/* lookword HEADER */
/* lang=C++20 */

/* word look-up object */
/* version %I% last-modified %G% */


/* Copyright © 2002 David A­D­ Morano.  All rights reserved. */

#ifndef	LOOKWORD_INCLUDE
#define	LOOKWORD_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#define	LOOKWORD_MAGIC	0x97543218
#define	LOOKWORD	struct lookword_head
#define	LOOKWORD_CUR	struct lookword_cursor
#define	LOOKWORD_FL	struct lookword_flags
#define	LOOKWORD_WORD	struct lookword_worder
/* options */
#define	LOOKWORD_OFOLD	(1<<0)		/* fold characters for comparison */
#define	LOOKWORD_ODICT	(1<<1)		/* use "dictionary" comparison rules */
#define	LOOKWORD_OWORD	(1<<2)		/* whole-word comparison */


struct lookword_flags {
	uint		dict:1 ;
	uint		fold:1 ;
	uint		word:1 ;
} ;

struct lookword_head {
	void		*md ;
	size_t		ms ;
	LOOKWORD_FL	f ;
	uint		magic ;
	int		fd ;
} ;

struct lookword_worder {
	cchar		*wp ;
	int		wl ;
} ;

struct lookword_cursor {
	LOOKWORD_WORD	*ans ;
	int		n ;
	int		i ;		/* when enumerating */
} ;

typedef	LOOKWORD	lookword ;
typedef	LOOKWORD_FL	lookword_fl ;
typedef	LOOKWORD_CUR	lookword_cur ;
typedef	LOOKWORD_WORD	lookword_word ;

EXTERNC_begin

extern int lookword_open(lookword *,cchar *,int) noex ;
extern int lookword_close(lookword *) noex ;
extern int lookword_curbegin(lookword *,lookword_cur *) noex ;
extern int lookword_lookup(lookword *,lookword_cur *,cchar *) noex ;
extern int lookword_read(lookword *,lookword_cur *,char *,int) noex ;
extern int lookword_curend(lookword *,lookword_cur *) noex ;

EXTERNC_end


#endif /* LOOKWORD_INCLUDE */


