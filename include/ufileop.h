/* ufileop HEADER (UNIX® file operations) */
/* lang=C20 */

/* translation layer interface for UNIX® equivalents */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services
	(RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:

	Description:
	All of the UNIX® system calls that use (operate on) a
	file-descroptor.

*******************************************************************************/

#ifndef	UFILEOP_INCLUDE
#define	UFILEOP_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>		/* system types */
#include	<sys/stat.h>
#include	<sys/mount.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<stdint.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usupport.h>


#ifdef	__cplusplus

namespace ufileop {
    struct ufileopflags {
	uint		fintr:1 ;	/* request interrupts to return */
    } ; /* end struct (ufileopflags) */
    struct ufileopbase {
	cchar		*fn ;
	ufileopflags	f{} ;
	ufileopbase() noex { } ;
	int operator () (cchar *) noex ;
	virtual int callstd(cchar *) noex = 0 ;
    } ; /* end struct (ufileopbase) */
}

#endif /* __cplusplus */

EXTERNC_begin

extern int u_access(cchar *,int) noex ;
extern int u_chdir(cchar *) noex ;
extern int u_chmod(cchar *,mode_t) noex ;
extern int u_minmod(cchar *,mode_t) noex ;
extern int u_chown(cchar *,uid_t,gid_t) noex ;
extern int u_lchown(cchar *,uid_t,gid_t) noex ;
extern int u_link(cchar *,cchar *) noex ;
extern int u_lstat(cchar *,USTAT *) noex ;
extern int u_mknod(cchar *,mode_t,dev_t) noex ;
extern int u_mkdir(cchar *,mode_t) noex ;
extern int u_pathconf(cchar *,int,long *) noex ;
extern int u_readlink(cchar *,char *,int) noex ;
extern int u_rename(cchar *,cchar *) noex ;
extern int u_resolvepath(cchar *,char *,int) noex ;
extern int u_rmdir(cchar *) noex ;
extern int u_stat(cchar *,USTAT *) noex ;
extern int u_statfs(cchar *,STATFS *) noex ;
extern int u_statvfs(cchar *,STATVFS *) noex ;
extern int u_symlink(cchar *,cchar *) noex ;
extern int u_truncate(cchar *,off_t) noex ;
extern int u_unlink(cchar *) noex ;
extern int u_utime(cchar *,CUTIMBUF *) noex ;
extern int u_utimes(cchar *,CTIMEVAL *) noex ;
extern int u_xattrget(cc *,cc *,void *,size_t,uint32_t,int) noex ;
extern int u_xattrset(cc *,cc *,cvoid *,size_t,uint32_t,int) noex ;

EXTERNC_end


#endif /* UFILEOP_INCLUDE */


