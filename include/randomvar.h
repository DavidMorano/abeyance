/* randomvar HEADER */
/* lang=C20 */

/* random-variable object */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	RANDOMVAR_INCLUDE
#define	RANDOMVAR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<stdintx.h>


#define	RANDOMVAR_MAGIC		0x97857322
#define	RANDOMVAR_DEGREE	127
#define	RANDOMVAR_DIGIT		ulong
#define	RANDOMVAR_STATELEN	(RANDOMVAR_DEGREE+1)
#define	RANDOMVAR_STIRINT	(5 * 60)

#define	RANDOMVAR		struct randomvar_head
#define	RANDOMVAR_FL		struct randomvar_flags


struct randomvar_flags {
	uint		pseudo:1 ;
	uint		flipper:1 ;
} ;

struct randomvar_head {
	ulong		*state ;
	time_t		laststir ;
	RANDOMVAR_FL	f ;
	uint		magic ;
	int		maintcount ;
	int		a, b, c ;
} ;

typedef RANDOMVAR	randomvar ;
typedef RANDOMVAR_FL	randomvar_fl ;

EXTERNC_begin

extern int randomvar_start(randomvar *,int,uint) noex ;
extern int randomvar_stateload(randomvar *,cchar *,int) noex ;
extern int randomvar_statesave(randomvar *,char *,int) noex ;
extern int randomvar_setpoly(randomvar *,int,int) noex ;
extern int randomvar_addnoise(randomvar *,cvoid *,int) noex ;
extern int randomvar_getlong(randomvar *,long *) noex ;
extern int randomvar_getulong(randomvar *,ulong *) noex ;
extern int randomvar_getint(randomvar *,int *) noex ;
extern int randomvar_getuint(randomvar *,uint *) noex ;
extern int randomvar_get(randomvar *,void *,int) noex ;
extern int randomvar_finish(randomvar *) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int randomvar_get(randomvar *op,int *p) noex {
	return randomvar_getint(op,p) ;
}
inline int randomvar_get(randomvar *op,long *p) noex {
	return randomvar_getlong(op,p) ;
}
inline int randomvar_get(randomvar *op,uint *p) noex {
	return randomvar_getuint(op,p) ;
}
inline int randomvar_get(randomvar *op,ulong *p) noex {
	return randomvar_getulong(op,p) ;
}

#endif /* __cplusplus */


#endif /* RANDOMVAR_INCLUDE */


