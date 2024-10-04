/* ufiledesc HEADER (UNIX® file operations) */
/* lang=C20 */

/* translation layer interface for UNIX® equivalents */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services (RNS).

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:

	Description:
	All of the UNIX® system calls that use (operate on) a
	file-descroptor.

*******************************************************************************/

#ifndef	UFILEDESC_INCLUDE
#define	UFILEDESC_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>		/* system types */
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usupport.h>


#ifdef	__cplusplus

namespace ufiledesc {
    struct ufiledescflags {
	uint		fclose:1 ;
	uint		fwrite:1 ;
	uint		fintr:1 ;	/* request interrupts to return */
    } ; /* end struct (ufiledescflags) */
    struct ufiledescbase {
	cvoid		*wbuf ;
	void		*rbuf ;
	int		wlen ;
	int		rlen ;
	ufiledescflags	f{} ;
	ufiledescbase() noex { } ;
	int operator () (int) noex ;
	virtual int callstd(int) noex = 0 ;
    } ; /* end struct (ufiledescbase) */
}

#endif /* __cplusplus */

EXTERNC_begin

extern int u_bind(int,cvoid *,int) noex ;
extern int u_listen(int,int) noex ;
extern int u_setsockopt(int,int,int,cvoid *,int) noex ;
extern int u_getsockopt(int,int,int,void *,int *) noex ;
extern int u_connect(int,cvoid *,int) noex ;
extern int u_getpeername(int,void *,int *) noex ;
extern int u_getsockname(int,void *,int *) noex ;
extern int u_send(int,cvoid *,int,int) noex ;
extern int u_sendmsg(int,CMSGHDR *,int) noex ;
extern int u_sendto(int,cvoid *,int,int,cvoid *,int) noex ;
extern int u_sendfiler(int,int,off_t,size_t) noex ;
extern int u_recv(int,void *,int,int) noex ;
extern int u_recvmsg(int,MSGHDR *,int) noex ;
extern int u_recvfrom(int,void *,int,int,void *,int *) noex ;
extern int u_shutdown(int,int) noex ;

extern int u_closeonexec(int,int) noex ;
extern int u_nonblock(int,int) noex ;
extern int u_readn(int,void *,int) noex ;
extern int u_writen(int,cvoid *,int) noex ;
extern int u_fchdir(int) noex ;
extern int u_fchmod(int,mode_t) noex ;
extern int u_fchown(int,uid_t,gid_t) noex ;
extern int u_close(int) noex ;
extern int u_fstat(int,USTAT *) noex ;
extern int u_fstatfs(int,STATFS *) noex ;
extern int u_fstatvfs(int,STATVFS *) noex ;
extern int u_fpathconf(int,int,long *) noex ;
extern int u_fstype(int,char *,int) noex ;
extern int u_fsync(int) noex ;
extern int u_fcntl(int,int,...) noex ;
extern int u_ftruncate(int,off_t) noex ;
extern int u_ioctl(int,int,...) noex ;
extern int u_lockf(int,int,off_t) noex ;
extern int u_pread(int,void *,int,off_t) noex ;
extern int u_pwrite(int,cvoid *,int,off_t) noex ;
extern int u_read(int,void *,int) noex ;
extern int u_readv(int,IOVEC *,int) noex ;
extern int u_seeko(int,off_t,int,off_t *) noex ;
extern int u_write(int,cvoid *,int) noex ;
extern int u_writev(int,CIOVEC *,int) noex ;
extern int u_getdents(int,dirent_t *,int) noex ;

/* special aliases */
extern int u_sockaddrrem(int,void *,int *) noex ;
extern int u_sockaddrloc(int,void *,int *) noex ;

static inline int u_seek(int fd,off_t wo,int w) noex {
	return u_seeko(fd,wo,w,nullptr) ;
}
static inline int u_seekoff(int fd,off_t wo,int w,off_t *offp) noex {
	return u_seeko(fd,wo,w,offp) ;
}
static inline int u_tell(int fd,off_t *rp) noex {
	return u_seeko(fd,0L,SEEK_CUR,rp) ;
}
static inline int u_seekable(int fd) noex {
	return u_seek(fd,0L,SEEK_CUR) ;
}
static inline int u_rewind(int fd) noex {
	return u_seek(fd,0L,SEEK_SET) ;
}

extern int u_poll(POLLFD *,int,int) noex ;	/* <- special case */

EXTERNC_end


#endif /* UFILEDESC_INCLUDE */


