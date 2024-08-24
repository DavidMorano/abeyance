/* proglog HEADER */
/* lang=C++20 */

/* program-logging */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-09-01, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Manage program logging operations.

*******************************************************************************/

#ifndef	PROGLOG_INCLUDE
#define	PROGLOG_INCLUDE
#ifdef	__cplusplus


#include	<envstandards.h>	/* must be before others */
#include	<stdarg.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<userinfo.h>

#include	<proginfo.hh>


#ifndef	LOGCNAME
#define	LOGCNAME	"log"
#endif


EXTERNC_begin

extern int proglog_begin(proginfo *,userinfo *) noex ;
extern int proglog_end(proginfo *) noex ;
extern int proglog_intro(proginfo *,userinfo *) noex ;
extern int proglog_checksize(proginfo *) noex ;
extern int proglog_check(proginfo *) noex ;
extern int proglog_print(proginfo *,cchar *,int) noex ;
extern int proglog_printf(proginfo *,cchar *,...) noex ;
extern int proglog_vprintf(proginfo *,cchar *,va_list) noex ;
extern int proglog_printfold(proginfo *,cchar *,cchar *,int) noex ;
extern int proglog_getid(proginfo *,char *,int) noex ;
extern int proglog_setid(proginfo *,cchar *,int) noex ;
extern int proglog_ssprint(proginfo *,cchar *,cchar *,int) noex ;
extern int proglog_ssprintf(proginfo *,cchar *,cchar *,...) noex ;
extern int proglog_ssvprintf(proginfo *,cchar *,cchar *,va_list) noex ;
extern int proglog_flush(proginfo *) noex ;
 
EXTERNC_end


#endif /* __cplusplus */
#endif /* PROGLOG_INCLUDE */


