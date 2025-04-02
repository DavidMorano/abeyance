/* libut HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* virtual-system definitions */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

*/

#ifndef	LIBUT_INCLUDE
#define	LIBUT_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<fcntl.h>
#include	<xti.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


EXTERNC_begin

extern int ut_open(cchar *,int,struct t_info *) noex ;
extern int ut_accept(int,addr,lenp) noex ;
extern int ut_bind(int,req,ret) noex ;
extern int ut_close(int) noex ;
extern int ut_connect(int,sndcall,rcvcall) noex ;
extern int ut_listen(int,int) noex ;
extern int ut_look(int) noex ;
extern int ut_sync(int) noex ;

extern int ut_alloc(int,stype,fields,rpp) noex ;
extern int ut_free(void *,int) noex ;

EXTERNC_end


#endif /* LIBUT_INCLUDE */


