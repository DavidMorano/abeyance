/* chartrans HEADER */
/* lang=C20 */

/* character translation */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CHARTRANS_INCLUDE
#define	CHARTRANS_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<stddef.h>
#include	<uiconv.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


#define	CHARTRANS	struct chartrans_head
#define	CHARTRANS_SET	struct chartrans_set
#define	CHARTRANS_FL	struct chartrans_flags
#define	CHARTRANS_MAGIC	0x67298361
#define	CHARTRANS_NCS	"UCS-4"			/* native character-set */


struct chartrans_flags {
	uint		dummy:1 ;
} ;

struct chartrans_set {
	cchar		*name ;
	UICONV		id ;			/* converter */
	time_t		ti_access ;		/* access time */
	uint		acount ;		/* access time-stamp */
	uint		uc ;			/* usage-count */
	int		pc ;			/* pass-set */
} ;

struct chartrans_head {
	CHARTRANS_SET	*sets ;
	cchar		*pr ;
	void		*utf8decoder ;
	CHARTRANS_FL	f ;
	uint		magic ;
	int		nmax ;
	int		nsets ;
	int		acount ;
} ;

typedef CHARTRANS	chartrans ;
typedef	CHARTRANS_FL	chartrans_fl ;
typedef	CHARTRANS_SET	chartrans_set ;

EXTERNC_begin

extern int chartrans_open(chartrans *,cchar *,int) noex ;
extern int chartrans_close(chartrans *) noex ;
extern int chartrans_transbegin(chartrans *,time_t,cchar *,int) noex ;
extern int chartrans_transend(chartrans *,int) noex ;
extern int chartrans_transread(chartrans *,int,wchar_t *,int,cchar *,int) noex ;

EXTERNC_end


#endif /* CHARTRANS_INCLUDE */


