/* ucsthr SUPPORT (Solaris® Threads)*/
/* charset=ISO8859-1 */
/* lang=C++20 */

/* interface component for UNIX® library-3c */
/* Solaris® threads */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Names:
	uc_sthrcreate
	uc_sthrexit
	uc_sthrjoin
	uc_sthrsuspend
	uc_sthrcontinue
	uc_sthrminstack
	uc_sthrkill
	uc_sthrmain
	uc_sthrself
	uc_sthryield
	uc_sthrsigsetmask
	uc_sthrstksegment
	uc_sthrkeycreate
	uc_sthrsetspecific
	uc_sthrgetspecific
	uc_sthrgetconcurrency
	uc_sthrsetconcurrency

	Description:
	This code module provided a cleaned up interface to the
	native Solaris® thread facility.  Generally, this interface
	is ignored in favor of the POSIX® interface.

	Synopsis:
	int uc_sthrcreate(sbase,ssize,func,arg,tfl)
	caddr_t		sbase ;
	size_t		ssize ;
	thr_f		func ;
	cvoid		*arg ;
	long		tfl ;

	Arguments:
	sbase		stack base address
	ssize		statk size
	func		function to call as a thread
	arg		argument to thread function
	tfl		flags to manage thread creation

	Returns:
	>=0		thread ID
	<0		error (system-return)

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<thread.h>
#include	<cerrno>
#include	<csignal>
#include	<cstring>
#include	<usystem.h>
#include	<localmisc.h>

#include	"ucsthr.h"


/* local defines */


/* imported namespaces */


/* local typedefs */

extern "C" {
    typedef int (*thr_f)(void *) noex ;
}


/* local variables */


/* external subroutines */


/* exported subroutines */

int uc_sthrcreate(caddr_t sb,size_t sse,thr_f fn,cvoid *arg,long tfl) noex {
	thread_t	tid ;
	int		rs ;
	void		*targ = (void *) arg ;
	void		*(*tstart)(void *) = (void *(*)(void *)) fn ;
	repeat {
	    rs = thr_create(sb,sse,tstart,targ,tfl,&tid) ;
	    if (rs != 0) {
	        if (rs > 0) {
		    rs = (- rs) ;
	        } else
		    rs = SR_LIBACC ;
	    } else {
	        rs = (int) (tid & INT_MAX) ; /* we assume thread-ids can fit */
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrcreate) */

int uc_sthrexit(int ex) noex {
	void		*stat = (void *) ex ;
	thr_exit(stat) ;
	return SR_OK ;
}
/* end subroutine (uc_sthrexit) */

int uc_sthrjoin(thread_t tid,int *exp) noex {
	thread_t	depart ;
	int		rs ;
	void		*stat ;
	repeat {
	    rs = thr_join(tid,&depart,&stat) ;
	    if (rs > 0) {
	        rs = (- rs) ;
	    } else {
	        if (exp != NULL) {
		    long	v = (long) stat ;
		    *exp = (int) (v & INT_MAX) ;
	        }
	        rs = (int) (depart & INT_MAX) ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrjoin) */

int uc_sthrsuspend(thread_t tid) noex {
	int		rs ;
	repeat {
	    rs = thr_suspend(tid) ;
	    if (rs > 0) {
	        rs = (- rs) ;
	    } else if (rs < 0) {
	        rs = SR_LIBACC ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrsuspend) */

int uc_sthrcontinue(thread_t tid) noex {
	int		rs ;
	repeat {
	    rs = thr_continue(tid) ;
	    if (rs > 0) {
	        rs = (- rs) ;
	    } else if (rs < 0) {
	        rs = SR_LIBACC ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrcontinue) */

int uc_sthrminstack() noex {
	size_t		size ;
	int		rs ;
	repeat {
	     rs = SR_OK ;
	     errno = 0 ;
	     size = thr_min_stack() ;
	     if (errno > 0) {
		rs = (- errno) ;
	     } else {
	         rs = (int) (size & INT_MAX) ;
	     }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrminstack) */

int uc_sthrkill(thread_t tid,int sig) noex {
	int		rs ;
	repeat {
	    rs  = thr_kill(tid,sig) ;
	    if (rs > 0) {
	        rs = (- rs) ;
	    } else if (rs < 0) {
	        rs = SR_LIBACC ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrkill) */

int uc_sthrmain() noex {
	int		rs ;
	repeat {
	    errno = 0 ;
	    rs = thr_main() ;
	    if (rs < 0) {
	        if (errno != 0) {
		    rs = (- errno) ;
	        } else {
	            rs = SR_LIBACC ;
		}
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrmain) */

int uc_sthrself() noex {
	thread_t	tid ;
	int		rs ;
	repeat {
	    rs = SR_OK ;
	    errno = 0 ;
	    tid = thr_self() ;
	    if (errno != 0) {
	        rs = (- errno) ;
	    } else {
	        rs = (int) (tid & INT_MAX) ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrself) */

int uc_sthryield() noex {
	int		rs ;
	repeat {
	    rs = SR_OK ;
	    errno = 0 ;
	    thr_yield() ;
	    if (errno != 0) rs = (- errno) ;
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthryield) */

int uc_sthrsigsetmask(int how,const sigset_t *nsp,sigset_t *osp) noex {
	int		rs ;
	repeat {
	    errno = 0 ;
	    rs = thr_sigsetmask(how,nsp,osp) ;
	    if (rs != 0) {
	        if (rs > 0) {
	            rs = (- rs) ;
	        } else if (errno != 0) {
	            rs = (- errno) ;
		}
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrsigsetmask) */

int uc_sthrstksegment(stack_t *stk) noex {
	int		rs ;
	repeat {
	    rs = thr_stksegment(stk) ;
	    if (rs > 0) {
	        rs = (- rs) ;
	    } else if (rs < 0) {
	        rs = SR_LIBACC ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrstksegment) */

int uc_sthrkeycreate(thread_key_t *keyp,void (*destructor)(void *)) noex {
	int		rs ;
	repeat {
	    rs = thr_keycreate(keyp,destructor) ;
	    if (rs > 0) {
	        rs = (- rs) ;
	    } else if (rs < 0) {
	        rs = SR_LIBACC ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrkeycreate) */

int uc_sthrsetspecific(thread_key_t key,void *value) noex {
	int		rs ;
	repeat {
	    rs = thr_setspecific(key,value) ;
	    if (rs > 0) {
	        rs = (- rs) ;
	    } else if (rs < 0) {
	        rs = SR_LIBACC ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrsetspecific) */

int uc_sthrgetspecific(thread_key_t key,void **value) noex {
	int		rs ;
	repeat {
	    rs = thr_getspecific(key,value) ;
	    if (rs > 0) {
	        rs = (- rs) ;
	    } else if (rs < 0) {
	        rs = SR_LIBACC ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrgetspecific) */

int uc_sthrgetconcurrency() noex {
	int		rs ;
	repeat {
	    errno = 0 ;
	    rs = thr_getconcurrency() ;
	    if (errno != 0) rs = (- errno) ;
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrgetconcurrency) */

int uc_sthrsetconcurrency(int new) noex {
	int		rs ;
	repeat {
	    rs = thr_setconcurrency(new) ;
	    if (rs > 0) {
	        rs = (- rs) ;
	    } else if (rs < 0) {
	        rs = SR_LIBACC ;
	    }
	} until (rs != SR_INTR) ;
	return rs ;
}
/* end subroutine (uc_sthrsetconcurrency) */


