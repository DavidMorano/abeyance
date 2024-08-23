/* thrbase HEADER */
/* lang=C20 */

/* access manager interface to PCS user-mode polling */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-10-07, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	THRBASE_INCLUDE
#define	THRBASE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<usystem.h>
#include	<thrcomm.h>


#define	THRBASE		struct thrbase_head
#define	THRBASE_SI	struct thrbase_startinfo
#define	THRBASE_INFO	struct thrbase_info
#define	THRBASE_MAGIC	0x88773423


enum thrbasecmds {
	thrbasecmd_noop,
	thrbasecmd_exit,
	thrbasecmd_overlast
} ;

struct thrbase_info {
	int		dummy ;
} ;

struct thrbase_startinfo {
	THRBASE		*op ;
	int		(*worker)(THRBASE *,void *) ;
} ;

struct thrbase_head {
	void		*ap ;
	THRBASE_SI	*sip ;
	THRCOMM		*tcp ;
	pthread_t	tid ;
	volatile int	trs ;
	volatile int	f_exiting ;
	int		f_exited ;
} ;

typedef THRBASE		thrbase ;
typedef	THRBASE_SI	thrbase_si;
typedef THRBASE_INFO	thrbase_info ;

EXTERNC_begin

typedef int (*thrbase_sub)(thrbase *,void *) noex ;

extern int	thrbase_start(thrbase *,thrbase_sub,void *) noex ;
extern int	thrbase_cmdsend(thrbase *,int,int) noex ;
extern int	thrbase_cmdexit(thrbase *) noex ;
extern int	thrbase_cmdrecv(thrbase *,int) noex ;
extern int	thrbase_exiting(thrbase *) noex ;
extern int	thrbase_waitexit(thrbase *) noex ;
extern int	thrbase_infoget(thrbase *,thrbase_info *) noex ;
extern int	thrbase_finish(thrbase *) noex ;

EXTERNC_end


#endif /* THRBASE_INCLUDE */


