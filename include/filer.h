/* filer HEADER */
/* lang=C20 */

/* support some buffered file operations */
/* version %I% last-modified %G% */


/* revision history:

	= 2002-04-01, David A­D­ Morano
	This subroutine was originally written for Rightcore Network
	Services (RNS).

*/

/* Copyright © 2002 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

        This little object supports some buffered file operations for
        low-overhead buffered I-O requirements.

*******************************************************************************/

#ifndef	FILER_INCLUDE
#define	FILER_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>		/* system types */
#include	<unistd.h>		/* system types */
#include	<stdarg.h>		/* |va_list(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


#define	FILER		struct filer_head
#define	FILER_FL	struct filer_flags
#define	FILER_MAGIC	0x21387462
#define	FILER_ONET	O_NETWORK	/* specify network FD */
#define	FILER_RCNET	3		/* read-count for network */


struct filer_flags {
	uint		net:1 ;		/* network FD */
	uint		write:1 ;	/* we are writing (otherwise reading) */
} ;

struct filer_head {
	char		*dbuf ;		/* data-bufer pointer (constant) */
	char		*bp ;		/* goes up with use */
	off_t		off ;		/* virtual file pointer */
	FILER_FL	f ;
	uint		magic ;
	int		fd ;		/* file-descriptor */
	int		of ;		/* open-flags */
	int		dt ;		/* file-type ("DT_XXX" values)*/
	int		dlen ;		/* data-buffer length (constant) */
	int		len ;		/* length of valid-data in buffer */
} ;

typedef FILER		filer ;
typedef FILER_FL	filer_fl ;

EXTERNC_begin

extern int	filer_start(filer *,int,off_t,int,int) noex ;
extern int	filer_read(filer *,void *,int,int) noex ;
extern int	filer_readp(filer *,void *,int,off_t,int) noex ;
extern int	filer_readln(filer *,char *,int,int) noex ;
extern int	filer_readlns(filer *,char *,int,int,int *) noex ;
extern int	filer_write(filer *,cvoid *,int) noex ;
extern int	filer_writeto(filer *,cvoid *,int,int) noex ;
extern int	filer_println(filer *,cchar *,int) noex ;
extern int	filer_vprintf(filer *,cchar *,va_list) noex ;
extern int	filer_printf(filer *,cchar *,...) noex ;
extern int	filer_reserve(filer *,int) noex ;
extern int	filer_update(filer *,off_t,cchar *,int) noex ;
extern int	filer_invalidate(filer *) noex ;
extern int	filer_flush(filer *) noex ;
extern int	filer_adv(filer *,int) noex ;
extern int	filer_seek(filer *,off_t,int) noex ;
extern int	filer_tell(filer *,off_t *) noex ;
extern int	filer_poll(filer *,int) noex ;
extern int	filer_finish(filer *) noex ;

extern int	filer_writeblanks(filer *,int) noex ;
extern int	filer_writefill(filer *,cchar *,int) noex ;
extern int	filer_writealign(filer *,int) noex ;
extern int	filer_writezero(filer *,int) noex ;
extern int	filer_writefd(filer *,char *,int,int,int) noex ;
extern int	filer_writehdr(filer *,cchar *,int) noex ;
extern int	filer_writehdrkey(filer *,cchar *) noex ;
extern int	filer_printlncont(filer *,int,cchar *,int) noex ;

EXTERNC_end

#if	__cplusplus

template<typename ... Args>
static inline int filer_magic(filer *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == FILER_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}

#endif /* __cplusplus */


#endif /* FILER_INCLUDE */


