/* uunamerec HEADER */
/* lang=C20 */

/* string uunamerec object */
/* version %I% last-modified %G% */


#ifndef	UUNAMEREC_INCLUDE
#define	UUNAMEREC_INCLUDE


#include	<envstandards.h>
#include	<sys/types.h>
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	UUNAMEREC	struct uunamerec_head


struct uunamerec_head {
	int	*rectab ;	/* an entry is a single unsigned int */
	int	i ;		/* current length (including last NULL) */
	int	e ;		/* current buffer extent */
	int	c ;		/* count */
} ;

typedef	UUNAMEREC	uunamerec ;

EXTERNC_begin

extern int	uunamerec_start(uunamerec *,int) noex ;
extern int	uunamerec_finish(uunamerec *) noex ;
extern int	uunamerec_add(uunamerec *,int) noex ;
extern int	uunamerec_already(uunamerec *,int) noex ;
extern int	uunamerec_count(uunamerec *) noex ;
extern int	uunamerec_gettab(uunamerec *,int **) noex ;
extern int	uunamerec_indexlen(uunamerec *) noex ;
extern int	uunamerec_indexsize(uunamerec *) noex ;
extern int	uunamerec_mkindex(uunamerec *,int [][2],int) noex ;

EXTERNC_end


#endif /* UUNAMEREC_INCLUDE */


