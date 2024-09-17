/* keysymer HEADER */
/* lang=C++20 */

/* keysym name-value database */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	KEYSYMER_INCLUDE
#define	KEYSYMER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<mapstrint.h>


#define	KEYSYMER_MAGIC		0x24282138
#define	KEYSYMER		struct keysymer_head
#define	KEYSYMER_FL		struct keysymer_flags
#define	KEYSYMER_KE		struct keysymer_entry
#define	KEYSYMER_CUR		struct keysymer_cursor
#define	KEYSYMER_NAMELEN	60


struct keysymer_flags {
	uint		dummy:1 ;	/* dummy */
} ;

struct keysymer_entry {
	int		keynum ;
	char		keyname[KEYSYMER_NAMELEN+1] ;
} ;

struct keysymer_cursor {
	MAPSTRINT_CUR	c ;
} ;

struct keysymer_head {
	mapstrint	map ;
	KEYSYMER_FL	f ;
	uint		magic ;
} ;

typedef	KEYSYMER	keysymer ;
typedef	KEYSYMER_FL	keysymer_fl ;
typedef	KEYSYMER_KE	keysymer_ke ;
typedef	KEYSYMER_CUR	keysymer_cur ;

EXTERNC_begin

extern int keysymer_open(keysymer *,cchar *) noex ;
extern int keysymer_count(keysymer *) noex ;
extern int keysymer_lookup(keysymer *,cchar *,int) noex ;
extern int keysymer_curbegin(keysymer *,keysymer_cur *) noex ;
extern int keysymer_curend(keysymer *,keysymer_cur *) noex ;
extern int keysymer_enum(keysymer *,keysymer_cur *,keysymer_ke *) noex ;
extern int keysymer_close(keysymer *) noex ;

EXTERNC_end


#endif /* KEYSYMER_INCLUDE */


