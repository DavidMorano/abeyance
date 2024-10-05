/* bopenrcmd SUPPORT */
/* lang=C++20 */

/* BASIC INPUT OUTPUT package */
/* version %I% last-modified %G% */

#define	CF_DANGERHACK	1

/* revision history:

	= 1998-07-01, David A­D­ Morano
	This code was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	This subroutine spawns a shell and gives it a command to
	execute. Input and output is connected back to the caller.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<unistd.h>
#include	<fcntl.h>
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<localmisc.h>

#include	"bfile.h"


/* local defines */

#ifndef	LINEBUFLEN
#ifdef	LINE_MAX
#define	LINEBUFLEN	MAX(LINE_MAX,2048)
#else
#define	LINEBUFLEN	2048
#endif
#endif


/* external subroutines */


/* external variables */

extern char	*environ[] ;


/* forward reference */


/* exported variables */


/* exported subroutines */

int bopenrcmd(bfile **fpa,cchar *remotehost,cchar *cmd) noex {
	pid_t		child_pid = 0 ;
	int		rs ;
	int		fd = -1 ;
	int		i, j, k ;
	int		pipes[3][2] ;
	cchar		*cmd_rsh ;
	char		pfname[MAXPATHLEN + 1] ;

	if (fpa == NULL) return SR_FAULT ;

/* check for bad input */

	if ((remotehost == NULL) || (remotehost[0] == '\0'))
	    return SR_INVALID ;

	if ((cmd == NULL) || (cmd[0] == '\0'))
	    return SR_INVALID ;

	if ((strlen(cmd) + 6) > LINEBUFLEN)
	    return SR_INVALID ;

/* where is the RSH program */

	cmd_rsh = "/bin/rsh" ;
	if (u_access(cmd_rsh,X_OK) != 0) {
	    cmd_rsh = "/usr/ucb/rsh" ;
	    if (u_access(cmd_rsh,X_OK) != 0) {
	        return SR_BAD ;
	    }
	} /* end if */

/* open up the necessary pipes */

	for (i = 0 ; i < 3 ; i += 1) {
	    if (fpa[i] != NULL) {

/* file pointer already used? (yes this is a dangerous hack) */

#if	CF_DANGERHACK
	        if (fpa[i]->magic == BFILE_MAGIC) return SR_OPEN ;
#endif

	        if ((rs = u_pipe(pipes[i])) < 0)
	            goto badpipe ;

	    } /* end if */
	    if (rs < 0) break ;
	} /* end for */

/* we fork RSH */

	if (rs >= 0) {
	if ((child_pid = uc_fork()) == 0) {

	    for (i = 0 ; i < 3 ; i += 1) {

	        if (fpa[i] != NULL) {

	            u_close(i) ;

	            u_close(pipes[i][(i == 0) ? 1 : 0]) ;

	            fd = pipes[i][(i == 0) ? 0 : 1] ;
	            u_dup(fd) ;

	            u_close(fd) ;

	        } /* end if */

	    } /* end for */

/* do the exec */

	    if (rs >= 0) {
		    int		i = 0 ;
		    cchar	**ev = (cchar **) environ ;
		    cchar	*av[5] ;
		    av[i++] = "rsh" ;
		    av[i++] = remotehost ;
		    av[i++] = cmd ;
		    av[i] = NULL ;
	    	    uc_execve(cmd_rsh,av,ev) ;
	    }

	    uc_exit(BAD) ;
	} else if (child_pid < 0) {
	    rs = child_pid ;
	    goto badfork ;
	}
	} /* end if (ok) */

/* close some pipe ends */

	for (i = 0 ; i < 3 ; i += 1) {
	    if (fpa[i] != NULL) {
	        u_close(pipes[i][(i == 0) ? 0 : 1]) ;
	    }
	}

/* open the parent side "basic" files */

	for (i = 0 ; i < 3 ; i += 1) {

	    if (fpa[i] != NULL) {

	        if ((rs = bopen(fpa[i],(char *) pipes[i][(i == 0) ? 1 : 0],
	            (i == 0) ? "dw" : "dr",0666)) < 0)
	            goto badbopen ;

#if	BFILE_DUP
	        u_close(pipes[i][(i == 0) ? 1 : 0]) ;
#endif

	    } /* end if */

	} /* end for */

	return ((int) child_pid) ;

/* handle the numberous possible errors */
badbopen:

#if	BFILE_DUP
	u_close(pipes[i][(i == 0) ? 1 : 0]) ;
#endif

	for (j = 0 ; j < i ; j += 1)
	    if (fpa[j] != NULL)
	        bclose(fpa[j]) ;

	for (j = i ; j < 3 ; j += 1)
	    if (fpa[j] != NULL)
	        u_close(pipes[j][(j == 0) ? 1 : 0]) ;

	goto err3 ;

badfork:
err3:
	u_unlink(pfname) ;

badpipe:
	for (j = 0 ; j < i ; j += 1) {
	    for (k = 0 ; k < 2 ; k += 1) {
	        u_close(pipes[j][k]) ;
	    }
	}

	return rs ;
}
/* end subroutine (bopenrcmd) */


