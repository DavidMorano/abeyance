/* getax HEADER */
/* lang=C20 */

/* UNIX® System databases (ucentpw, ucentsp, ucentgr, and ucentpj) */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-06-16, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	GETAX_INCLUDE
#define	GETAX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


EXTERNC_begin

extern int getpw_begin() noex ;
extern int getpw_end() noex ;
extern int getpw_ent(ucentpw *,char *,int) noex ;
extern int getpw_name(ucentpw *,char *,int,cchar *) noex ;
extern int getpw_uid(ucentpw *,char *,int,uid_t) noex ;

extern int getua_begin() noex ;
extern int getua_end() noex ;
extern int getua_ent(ucentua *,char *,int) noex ;
extern int getua_entnam(ucentua *,char *,int,cchar *) noex ;
extern int getua_entuid(ucentua *,char *,int,uid_t) noex ;

extern int getsp_begin() noex ;
extern int getsp_end() noex ;
extern int getsp_ent(ucentsp *sp,char *,int) noex ;
extern int getsp_name(ucentsp *sp,char *,int,cchar *) noex ;

extern int getgr_begin() noex ;
extern int getgr_end() noex ;
extern int getgr_ent(ucentgr *,char *,int) noex ;
extern int getgr_name(ucentgr *,char *,int,cchar *name) noex ;
extern int getgr_gid(ucentgr *,char *,int,gid_t) noex ;

extern int getpj_begin() noex ;
extern int getpj_end() noex ;
extern int getpj_ent(ucentpj *,char *,int) noex ;
extern int getpj_name(ucentpj *,char *,int,cchar *) noex ;
extern int getpj_pid(ucentpj *,char *,int,projid_t) noex ;
extern int getpj_def(ucentpj *,char *,int,cchar *) noex ;

EXTERNC_end


#endif /* GETAX_INCLUDE */


