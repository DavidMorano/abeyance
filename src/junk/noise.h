/* noise HEADER */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* noise generator */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	NOISE_INCLUDE
#define	NOISE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	NOISE		struct noise_head
#define	NOISE_FL	struct noise_flags


struct noise_flags {
	int	daemon:1 ;
} ;

struct noise_head {
	void	**va ;
	int	i ;		/* highest index */
	int	e ;		/* extent of array */
	int	c ;		/* count of items in list */
	int	policy ;
	int	f_sorted ;	/* flag indicating sort state */
} ;

typedef	NOISE		noise ;
typedef	NOISE_FL	noise_fl ;

EXTERNC_begin

extern int noise_open(noise *) noex ;
extern int noise_close(noise *) noex ;
extern int noise_read(noise *,char *,int) noex ;
extern int noise_write(noise *,cchar *,int) noex ;

EXTERNC_end


#endif /* NOISE_INCLUDE */


