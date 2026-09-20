/* execute SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* execute a server daemon program */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1

/* revision history:

	= 1986-07-01, David A-D- Morano
	This program was originally written.

	= 1998-07-01, David A-D- Morano
	I added the ability to specify the "address_from"
	for the case when we add an envelope header to the message.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/**************************************************************************

  	Description:
	This subroutine just 'exec(2)'s a daemon server program.

***************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<pwd.h>
#include	<grp.h>
#include	<ctime>
#include	<csignal>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<bfile.h>
#include	<field.h>
#include	<vecstr.h>
#include	<localmisc.h>

#include	"srvpe.h"
#include	"srventry.h"
#include	"builtin.h"
#include	"config.h"
#include	"defs.h"


/* local defines */


/* external subroutines */

extern int	getfiledirs() ;
extern int	processargs(char *,VECSTR *) ;
extern int	process() ;


/* external variables */

extern struct global	g ;


/* forward references */


/* local data */


/* exported subroutines */


int execute(gp,s,elp,program,arg0,alp)
struct global	*gp ;
int		s ;
VECSTR		*elp ;
char		program[], arg0[] ;
VECSTR		*alp ;
{
	int	rs ;

	char	*oldarg0 ;


#if	CF_DEBUG
	if (gp->debuglevel > 2) {

		int	i ;

		char	*sp ;


		debugprintf("execute: program=%s\n",program) ;
		debugprintf("execute: arg0=%s\n",arg0) ;

		for (i = 0 ; vecstrget(alp,i,&sp) >= 0 ; i += 1)
			debugprintf("execute: arg%d> %s\n",i,sp) ;

	}
#endif /* CF_DEBUG */

	if ((g.workdir != NULL) && (g.workdir[0] != '\0'))
		u_chdir(g.workdir) ;

	if ((s != 0) && (s != 1))
		u_close(s) ;

	oldarg0 = alp->va[0] ;
	alp->va[0] = arg0 ;
	{
	    const char	**eav = (const char **) alp->va ;
	    const char	**eev = (const char **) elp->va ;
	    rs = u_execve(program,eav,eev) ;
	}

#if	CF_DEBUG
	if (gp->debuglevel > 2)
		debugprintf("execute: exec rs=%s\n",rs) ;
#endif /* CF_DEBUG */

	alp->va[1] = oldarg0 ;
	return rs ;
}
/* end subroutine (execute) */



