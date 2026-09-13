/* dnsres_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* generic front-end */
/* version %I% last-modified %G% */

#define	CF_DEBUGS	0		/* compile-time debug print-outs */
#define	CF_DEBUG	0		/* run-time debug print-outs */

/* revision history:

	= 1989-03-01, David A­D­ Morano
	This was written for some program (deleted the particulars).

	= 1998-06-01, David A­D­ Morano
	This was enhanced from the original version.

	= 1999-03-01, David A­D­ Morano
	More enhancements.

	= 2006-04-05, David A­D­ Morano
	Enhanced to add dev-inode uniqueness checking.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Description:

	Synopsis:
	$ consoletime

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/wait.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<netdb.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<sighand.h>
#include	<baops.h>
#include	<keyopt.h>
#include	<bfile.h>
#include	<sbuf.h>
#include	<ids.h>
#include	<kinfo.h>		/* not thread safe! */
#include	<exitcodes.h>
#include	<localmisc.h>
#include	<libdebug.h>

#include	"config.h"
#include	"defs.h"


/* local defines */

#define	PI		proginfo

#define	MAXARGINDEX	100
#define	MAXARGGROUPS	(MAXARGINDEX/8 + 1)

#ifndef	LINEBUFLEN
#define	LINEBUFLEN	MAX((MAXPATHLEN + 3),2048)
#endif

#undef	O_FLAGS
#define	O_FLAGS		(O_WRONLY | O_NOCTTY)


/* external subroutines */

extern int	proginfo_setpiv(PI *,cchar *,const pivars *) ;
extern int	printhelp(void *,cchar *,cchar *,cchar *) ;


/* external variables */


/* local structures */


/* forward references */

local int	usage(PI *) ;

local int	procopts(PI *,keyopt *) ;
local int	procdaemon(PI *,cchar *) ;
local int	procserve(PI *,cchar *) ;
local int	proconce(PI *,cchar *) ;
local int	procout(PI *,cchar *) ;
local int	procprint(PI *,int,gid_t) ;

local int	procinfo_begin(PI *) ;
local int	procinfo_nusers(PI *) ;
local int	procinfo_nprocs(PI *) ;
local int	procinfo_check(PI *) ;
local int	procinfo_end(PI *) ;

local int	msglogdev(IDS *,cchar *) ;

static void	main_sighand(int,siginfo_t *,void *) ;


/* local variables */

static volatile int	if_int ;
static volatile int	if_exit ;

constexpr int	sigblocks[] = {
	SIGUSR1,
	SIGUSR2,
	SIGHUP,
	SIGCHLD,
	0
} ;

constexpr int	sigignores[] = {
	SIGPIPE,
	SIGPOLL,
	0
} ;

constexpr int	sigints[] = {
	SIGINT,
	SIGTERM,
	SIGQUIT,
	0
} ;

enum argopts {
	argopt_root,
	argopt_version,
	argopt_verbose,
	argopt_help,
	argopt_option,
	argopt_pm,
	argopt_sn,
	argopt_ef,
	argopt_af,
	argopt_if,
	argopt_of,
	argopt_to,
	argopt_mnt,
	argopt_overlast
} ;

constexpr cpcchar	argopts[] = {
	"ROOT",
	"VERSION",
	"VERBOSE",
	"HELP",
	"option",
	"pm",
	"sn",
	"ef",
	"af",
	"if",
	"of",
	"to",
	"mnt",
	nullptr
} ;

constexpr pivars	initvars = {
	VARPROGRAMROOT1,
	VARPROGRAMROOT2,
	VARPROGRAMROOT3,
	PROGRAMROOT,
	VARPRLOCAL
} ;

constexpr mapex		mapexs[] = {
	{ SR_NOENT, EX_NOUSER },
	{ SR_AGAIN, EX_TEMPFAIL },
	{ SR_DEADLK, EX_TEMPFAIL },
	{ SR_NOLCK, EX_TEMPFAIL },
	{ SR_TXTBSY, EX_TEMPFAIL },
	{ SR_ACCESS, EX_NOPERM },
	{ SR_REMOTE, EX_PROTOCOL },
	{ SR_NOSPC, EX_TEMPFAIL },
	{ SR_INTR, EX_INTR },
	{ SR_EXIT, EX_TERM },
	{ 0, 0 }
} ;

enum progmodes {
	progmode_consoletime,
	progmode_loginblurb,
	progmode_overlast
} ;

constexpr cpcchar	progmodes[] = {
	"consoletime",
	"loginblurb",
	nullptr
} ;

enum progopts {
	progopt_str,
	progopt_date,
	progopt_time,
	progopt_users,
	progopt_procs,
	progopt_mem,
	progopt_load,
	progopt_la,
	progopt_name,
	progopt_nodetitle,
	progopt_node,
	progopt_term,
	progopt_mesg,
	progopt_to,
	progopt_overlast
} ;

constexpr cpcchar	progopts[] = {
	"str",
	"date",
	"time",
	"users",
	"procs",
	"mem",
	"load",
	"la",
	"name",
	"nodetitle",
	"node",
	"term",
	"mesg",
	"to",
	nullptr
} ;

constexpr cpcchar	ansiterms[] = {
	"ansi",
	"sun",
	"screen",
	"vt100",
	"vt101",
	"vt102",
	"vt220",
	"vt230",
	"vt240",
	"vt320",
	"vt330",
	"vt340",
	"vt420",
	"vt430",
	"vt440",
	"vt520",
	"vt530",
	"vt540",
	nullptr
} ;

constexpr cpcchar	msglogdevs[] = {
	MSGLOGDEV,
	CONSOLEDEV,
	nullptr
} ;


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv,mainv envv) {
	PROGINFO	pi, *pip = &pi ;
	SIGHAND		sm ;
	IDS		id ;
	keyopt		akopts ;
	bfile		errfile ;
	ustat		sb ;

	int	argr, argl, aol, akl, avl, kwi ;
	int	ai, ai_max, ai_pos ;
	int	pan ;
	int	rs ;
	int	rs1 ;
	int	size ;
	int	n, i, j ;
	int	v ;
	int	ex = EX_INFO ;
	int	f_optminus, f_optplus, f_optequal ;
	int	f_version = false ;
	int	f_usage = false ;
	int	f_help = false ;

	cchar	*argp, *aop, *akp, *avp ;
	cchar	*argval = nullptr ;
	char	argpresent[MAXARGGROUPS] ;
	cchar	*pr = nullptr ;
	cchar	*sn = nullptr ;
	cchar	*pmspec = nullptr ;
	cchar	*efname = nullptr ;
	cchar	*afname = nullptr ;
	cchar	*ifname = nullptr ;
	cchar	*ofname = nullptr ;
	cchar	*termtype = nullptr ;
	cchar	*mntfname = nullptr ;
	cchar	*cp ;


	if_int = 0 ;
	if_exit = 0 ;

	rs = sighand_start(&sm, sigblocks,sigignores,sigints,main_sighand) ;
	if (rs < 0) goto ret0 ;

#if	CF_DEBUGS || CF_DEBUG
	if ((cp = getourenv(envv,VARDEBUGFNAME)) != nullptr) {
	    rs = debugopen(cp) ;
	    debugprintf("main: starting DFD=%d\n",rs) ;
	}
#endif /* CF_DEBUGS */

	rs = proginfo_start(pip,envv,argv[0],VERSION) ;
	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto badprogstart ;
	}

	if ((cp = getenv(VARBANNER)) == nullptr) cp = BANNER ;
	proginfo_setbanner(pip,cp) ;

	for (i = 0 ; i < 3 ; i += 1) {
	    if (u_fstat(i,&sb) < 0) {
		int oflags = (i == 0) ? O_RDONLY : O_WRONLY ;
		u_open(nullptrFNAME,oflags,0666) ;
	    }
	}

/* initialize */

	pip->verboselevel = 1 ;
	pip->to_open = -1 ;

	pip->f.term = true ;
	pip->f.mesg = false ;

	pip->f.o_string = false ;
	pip->f.o_time = true ;
	pip->f.o_nodetitle = false ;
	pip->f.o_node = true ;
	pip->f.o_users = true ;
	pip->f.o_procs = true ;
	pip->f.o_mem = true ;
	pip->f.o_load = true ;

/* start parsing the arguments */

	rs = keyopt_start(&akopts) ;
	pip->open.akopts = (rs >= 0) ;

	for (ai = 0 ; ai < MAXARGGROUPS ; ai += 1)
	    argpresent[ai] = 0 ;

	ai = 0 ;
	ai_max = 0 ;
	ai_pos = 0 ;
	argr = argc ;
	for (ai = 0 ; (ai < argc) && (argv[ai] != nullptr) ; ai += 1) {
	    if (rs < 0) break ;
	    argr -= 1 ;
	    if (ai == 0) continue ;

	    argp = argv[ai] ;
	    argl = strlen(argp) ;

	    f_optminus = (*argp == '-') ;
	    f_optplus = (*argp == '+') ;
	    if ((argl > 1) && (f_optminus || f_optplus)) {
		cint	ach = MKCHAR(argp[1]) ;

	        if (isdigitlatin(ach)) {

	            argval = (argp + 1) ;

	        } else if (ach == '-') {

	            ai_pos = ai ;
	            break ;

	        } else {

	            aop = argp + 1 ;
	            akp = aop ;
	            aol = argl - 1 ;
	            f_optequal = false ;
	            if ((avp = strchr(aop,'=')) != nullptr) {
	                f_optequal = true ;
	                akl = avp - aop ;
	                avp += 1 ;
	                avl = aop + argl - 1 - avp ;
	                aol = akl ;
	            } else {
	                avp = nullptr ;
	                avl = 0 ;
	                akl = aol ;
	            }

	            if ((kwi = matostr(argopts,2,akp,akl)) >= 0) {

	                switch (kwi) {

/* version */
	                case argopt_version:
	                    f_version = true ;
	                    if (f_optequal)
	                        rs = SR_INVALID ;
	                    break ;

/* verbose mode */
	                case argopt_verbose:
	                    pip->verboselevel = 2 ;
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl) {
	            		    rs = optvalue(avp,avl) ;
	                            pip->verboselevel = rs ;
				}
	                    }
	                    break ;

	                case argopt_help:
	                    f_help = true ;
	                    break ;

/* the user specified some progopts */
	                case argopt_option:
	                    if (argr <= 0) {
	                        rs = SR_INVALID ;
	                        break ;
	                    }
	                    argp = argv[++ai] ;
	                    argr -= 1 ;
	                    argl = strlen(argp) ;
	                    if (argl)
	                        rs = keyopt_loads(&akopts,argp,argl) ;
	                    break ;

/* program mode */
	                case argopt_pm:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            pmspec = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            pmspec = argp ;
	                    }
	                    break ;

/* program search-name */
	                case argopt_sn:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            sn = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            sn = argp ;
	                    }
	                    break ;

/* error file */
	                case argopt_ef:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            efname = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            efname = argp ;
	                    }
	                    break ;

/* argument file */
	                case argopt_af:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            afname = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            afname = argp ;
	                    }
	                    break ;

/* input file */
	                case argopt_if:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            ifname = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            ifname = argp ;
	                    }
	                    break ;

/* output file */
	                case argopt_of:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            ofname = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            ofname = argp ;
	                    }
	                    break ;

/* mount file */
	                case argopt_mnt:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl)
	                            mntfname = avp ;
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            mntfname = argp ;
	                    }
	                    break ;

/* timeout (open) */
	                case argopt_to:
	                    if (f_optequal) {
	                        f_optequal = false ;
	                        if (avl) {
	                            rs = cfdeci(avp,avl,&v) ;
				    pip->to_open = v ;
				}
	                    } else {
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl) {
	                            rs = cfdeci(argp,argl,&v) ;
				    pip->to_open = v ;
				}
	                    }
	                    break ;

/* handle all keyword defaults */
	                default:
	                    rs = SR_INVALID ;
	                    bprintf(pip->efp,
	                        "%s: invalid key=%t\n",
	                        pip->progname,akp,akl) ;

	                } /* end switch */

	            } else {

	                while (akl--) {
			    cint	kc = MKCHAR(*akp) ;
	                    switch (kc) {
/* debug */
	                    case 'D':
	                        pip->debuglevel = 1 ;
	                        if (f_optequal) {
	                            f_optequal = false ;
	                            if (avl) {
	                                    rs = optvalue(avp,avl) ;
	                                    pip->debuglevel = rs ;
				    }
	                        }
	                        break ;

/* program-root */
	                    case 'R':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            pr = argp ;
	                        break ;

/* terminal-type */
	                    case 'T':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            termtype = argp ;
	                        break ;

/* version */
	                    case 'V':
	                        f_version = true ;
	                        break ;

/* quiet mode */
	                    case 'Q':
	                        pip->f.quiet = true ;
	                        break ;

	                    case 'd':
				pip->f.daemon = true ;
	                        if (f_optequal) {
	                            f_optequal = false ;
	                            if (avl) {
	                                rs = cfdeci(avp,avl,&v) ;
					pip->intrun = v ;
				    }
				}
	                        break ;

/* observe MESG flag (group-writeable) on output device */
	                    case 'm':
	                        pip->finval.mesg = true ;
	                        pip->f.mesg = true ;
	                        if (f_optequal) {
	                            f_optequal = false ;
	                            if (avl) {
	                                rs = optbool(avp,avl) ;
	                                pip->f.mesg = (rs > 0) ;
	                            }
	                        }
	                        break ;

	                    case 'o':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl)
	                            rs = keyopt_loads(&akopts,argp,argl) ;
	                        break ;

	                    case 'q':
	                        pip->verboselevel = 0 ;
	                        break ;

	                    case 's':
	                        if (argr <= 0) {
	                            rs = SR_INVALID ;
	                            break ;
	                        }
	                        argp = argv[++ai] ;
	                        argr -= 1 ;
	                        argl = strlen(argp) ;
	                        if (argl) {
				    pip->finval.o_string = true ;
				    pip->f.o_string = true ;
	                            pip->string = argp ;
				}
	                        break ;

/* specify if output is a terminal or not */
	                    case 't':
				pip->finval.term = true ;
				pip->have.term = true ;
	                        pip->f.term = true ;
	                        if (f_optequal) {
	                            f_optequal = false ;
	                            if (avl) {
	                                rs = optbool(avp,avl) ;
	                                pip->f.term = (rs > 0) ;
	                            }
	                        }
	                        break ;

/* verbose mode */
	                    case 'v':
	                        pip->verboselevel = 2 ;
	                        if (f_optequal) {
	                            f_optequal = false ;
	                            if (avl) {
	                                rs = optbalue(avp,avl) ;
	                                pip->verboselevel = rs ;
				    }
	                        }
	                        break ;

	                    case '?':
	                        f_usage = true ;
	                        break ;

	                    default:
	                        rs = SR_INVALID ;
				break ;

	                    } /* end switch */
	                    akp += 1 ;

	                    if (rs < 0) break ;
	                } /* end while */

	            } /* end if (individual option key letters) */

	        } /* end if (digits as argument or not) */

	    } else {

	        if (ai >= MAXARGINDEX)
	            break ;

	        BASET(argpresent,ai) ;
	        ai_max = ai ;

	    } /* end if (key letter/word or positional) */

	    ai_pos = ai ;

	} /* end while (all command line argument processing) */

	if (efname == nullptr) efname = getenv(VARERRORFNAME) ;
	if (efname == nullptr) efname = BFILE_STDERR ;
	if ((rs1 = bopen(&errfile,efname,"wca",0666)) >= 0) {
	    pip->efp = &errfile ;
	    pip->open.errfile = true ;
	    bcontrol(&errfile,BC_SETBUFLINE,true) ;
	}

	if (rs < 0)
	    goto badarg ;

#if	CF_DEBUG
	if (DEBUGLEVEL(2))
	    debugprintf("main: debuglevel=%u\n",pip->debuglevel) ;
#endif

	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: debuglevel=%u\n",
	        pip->progname,pip->debuglevel) ;

	if (f_version)
	    bprintf(pip->efp,"%s: version %s\n",
	        pip->progname,VERSION) ;

/* get our program mode */

	if (pmspec == nullptr)
	    pmspec = pip->progname ;

	pip->progmode = matstr(progmodes,pmspec,-1) ;

#if	CF_DEBUG
	if (DEBUGLEVEL(4)) {
	    if (pip->progmode >= 0) {
	        debugprintf("main: progmode=%s(%u)\n",
	            progmodes[pip->progmode],pip->progmode) ;
	    } else
	        debugprintf("main: progmode=NONE\n") ;
	}
#endif /* CF_DEBUGS */

	if (pip->progmode < 0)
	    pip->progmode = progmode_consoletime ;

	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: pm=%s\n",
	        pip->progname,progmodes[pip->progmode]) ;

	if (sn == nullptr)
	    sn = progmodes[pip->progmode] ;

/* get the program root */

	rs = proginfo_setpiv(pip,pr,&initvars) ;

	if (rs >= 0)
	    rs = proginfo_setsearchname(pip,VARSEARCHNAME,sn) ;

	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto retearly ;
	}

#if	CF_DEBUG
	if (DEBUGLEVEL(4))
	    debugprintf("main: pr=%s\n",pip->pr) ;
#endif

	if (pip->debuglevel > 0) {
	    bprintf(pip->efp,"%s: pr=%s\n", pip->progname,pip->pr) ;
	    bprintf(pip->efp,"%s: sn=%s\n", pip->progname,pip->searchname) ;
	} /* end if */

	if (f_usage)
	    usage(pip) ;

/* help file */

	if (f_help)
	    printhelp(nullptr,pip->pr,pip->searchname,HELPFNAME) ;

	if (f_version || f_help || f_usage)
	    goto retearly ;


	ex = EX_OK ;

/* program customization */

	switch (pip->progmode) {
	case progmode_loginblurb:
	    pip->f.o_time = false ;
	    if (ofname == nullptr) ofname = "-" ;
	    break ;
	case progmode_consoletime:
	    if ((! pip->finval.o_time) && pip->f.daemon)
		pip->f.o_time = false ;
	    break ;
	} /* end switch */

/* progopts */

	rs = procopts(pip,&akopts) ;
	if (rs < 0) {
	    ex = EX_OSERR ;
	    goto badproc ;
	}

/* final defaults */

	if (termtype == nullptr)
	    termtype = getenv(VARTERM) ;

	if (termtype != nullptr) {
	    n = matpcasestr(ansiterms,2,termtype,-1) ;
	    pip->f.ansiterm = (n >= 0) ;
	} /* end if */

	if (pip->f.daemon && (! pip->finval.term)) {
	    pip->f.term = false ;
	}

	if (pip->string == nullptr) {
	    pip->f.o_string = true ;
	    pip->string = getenv(VARSTRING) ;
	}

	pip->daytime = time(nullptr) ;

	if ((ofname == nullptr) && (! pip->f.daemon)) {
	    cchar	*ccp ;
	    cchar	*backup = nullptr ;
	    if ((rs = ids_load(&id)) >= 0) {
	        for (i = 0 ; (msglogdevs[i] != nullptr) ; i += 1) {
		    ccp = msglogdevs[i] ;
	            rs1 = msglogdev(&id,ccp) ;
	            if (rs1 >= 0) {
		        if (backup == nullptr) backup = ccp ;
		        if (rs1 > 0) {
		            ofname = ccp ;
		            break ;
		        }
		    }
	        } /* end for */
		ids_release(&id) ;
	    } /* end if (IDS) */
	    if (ofname == nullptr)
		ofname = backup ;
	} /* end if */

	if ((ofname != nullptr) &&
	    ((ofname[0] == '\0') || (ofname[0] == '-'))) {
	    ofname = OUTPUTDEV ;
	    if (! pip->finval.mesg)
	        pip->f.mesg = false ;
	}

	if (mntfname == nullptr)
	    mntfname = getenv(VARMNTFNAME) ;

	if (pip->to_open < 0)
	    pip->to_open = TO_OPEN ;

	if (pip->f.daemon) {

	    if ((mntfname == nullptr) || (mntfname[0] == '\0')) {
		rs = SR_NOENT ;
		ex = EX_NOINPUT ;
	        bprintf(pip->efp,"%s: inaccessible mount-point\n",
	            pip->progname) ;
	    }

	    if (rs >= 0)
	        rs = procdaemon(pip,mntfname) ;

	} else {

	    if ((ofname == nullptr) || (ofname[0] == '\0')) {
		rs = SR_NOENT ;
		ex = EX_CANTCREAT ;
	        bprintf(pip->efp,"%s: inaccessible msg-log device\n",
	            pip->progname) ;
	    }

	    if (rs >= 0)
	        rs = proconce(pip,ofname) ;

	} /* end if */

badproc:
badconsole:
done:
	if ((rs < 0) && (ex == EX_OK)) {
	    switch (rs) {

	    case SR_INVALID:
	        ex = EX_USAGE ;
	        break ;

	    case SR_NOENT:
	        ex = EX_CANTCREAT ;
	        bprintf(pip->efp,"%s: inaccessible console device (%d)\n",
	            pip->progname,rs) ;
	        break ;

	    case SR_AGAIN:
	        ex = EX_TEMPFAIL ;
	        break ;

	    default:
	        ex = mapex(mapexs,rs) ;
	        break ;

	    } /* end switch */
	} /* end if */

/* early return thing */
retearly:
	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: exiting ex=%u (%d)\n",
	        pip->progname,ex,rs) ;

	if (pip->efp != nullptr) {
	    bclose(pip->efp) ;
	    pip->efp = nullptr ;
	}

	if (pip->open.akopts) {
	    keyopt_finish(&akopts) ;
	    pip->open.akopts = false ;
	}

	proginfo_finish(pip) ;

/* restore and get out */
badprogstart:

#if	(CF_DEBUGS || CF_DEBUG)
	debugclose() ;
#endif

	sighand_finish(&sm) ;

ret0:
	return ex ;

/* the bad things */
badarg:
	ex = EX_USAGE ;
	bprintf(pip->efp,"%s: invalid argument specified (%d)\n",
	    pip->progname,rs) ;
	usage(pip) ;
	goto retearly ;

}
/* end subroutine (main) */


/* local subroutines */


/* ARGSUSED */
static void main_sighand(int sn,siginfo_t *sip,void *vcp)
{
	switch (sn) {
	case SIGINT:
	    if_int = true ;
	    break ;
	default:
	    if_exit = true ;
	    break ;
	} /* end switch */
}
/* end subroutine (main_sighand) */


local int usage(pip)
PROGINFO	*pip ;
{
	int	rs ;
	int	wlen = 0 ;


	rs = bprintf(pip->efp,
	    "%s: USAGE> %s [-of <consdev>] [-t[=<b>]] [-m[=<b>]] \n",
	    pip->progname,pip->progname) ;

	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s:  [-o <option(s)>] [-s <string>] [-to <timeout>]\n",
	    pip->progname) ;

	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s:  [-Q] [-D] [-v[=<n>]] [-HELP] [-V]\n",
	    pip->progname) ;

	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s: where:\n",
	    pip->progname) ;

	wlen += rs ;
	rs = bprintf(pip->efp,
	    "%s:  <option> is 'node', 'users', 'procs', 'mem', 'load'\n",
	    pip->progname) ;

	wlen += rs ;
	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (usage) */

local int procopts(PI *pip,keyopt *kop) noex {
	keyopt_cur	cur ;
	int	rs = SR_OK ;
	int	v ;
	int	ki ;
	int	kl, vl ;
	int	c = 0 ;
	cchar	*kp, *vp ;
	cchar	*cp ;

/* grab options from the environment */

	if ((cp = getenv(VAROPTS)) != nullptr) {
	    rs = keyopt_loads(kop,cp,-1) ;
	}

	if (rs < 0)
	    goto ret0 ;

/* process program options */

	if ((rs = keyopt_curbegin(kop,&cur)) >= 0) {

	while ((kl = keyopt_curenumkeys(kop,&cur,&kp)) >= 0) {

	    ki = matostr(progopts,2,kp,kl) ;

	    if (ki >= 0) {
	        c += 1 ;
	        vl = keyopt_fetch(kop,kp,nullptr,&vp) ;
	    }

	    switch (ki) {

	    case progopt_str:
		if (! pip->finval.o_string) {
		    pip->f.o_string = true ;
		    if (vl > 0) {
		        strdcpy1w(pip->strbuf,STRBUFLEN,vp,vl) ;
		        pip->string = pip->strbuf ;
		    }
		}
		break ;

	    case progopt_date:
	    case progopt_time:
	        pip->f.o_time = true ;
	        if (vl > 0) {
		    rs = optbool(vp,vl) ;
	            pip->f.o_time = (rs > 0) ;
		}
		break ;

	    case progopt_nodetitle:
	        pip->f.o_nodetitle = true ;
	        if (vl > 0) {
		    rs = optbool(vp,vl) ;
	            pip->f.o_nodetitle = (rs > 0) ;
		}
		break ;

	    case progopt_name:
	    case progopt_node:
	        pip->f.o_node = true ;
	        if (vl > 0) {
		    rs = optbool(vp,vl) ;
	            pip->f.o_node = (rs > 0) ;
		}
	        break ;

	    case progopt_users:
	        pip->f.o_users = true ;
	        if (vl > 0) {
		    rs = optbool(vp,vl) ;
	            pip->f.o_users = (rs > 0) ;
		}
	        break ;

	    case progopt_procs:
	        pip->f.o_procs = true ;
	        if (vl > 0) {
		    rs = optbool(vp,vl) ;
	            pip->f.o_procs = (rs > 0) ;
		}
	        break ;

	    case progopt_mem:
	        pip->f.o_mem = true ;
	        if (vl > 0) {
		    rs = optbool(vp,vl) ;
	            pip->f.o_mem = (rs > 0) ;
		}
	        break ;

	    case progopt_load:
	    case progopt_la:
	        pip->f.o_load = true ;
	        if (vl > 0) {
		    rs = optbool(vp,vl) ;
	            pip->f.o_load = (rs > 0) ;
		}
	        break ;

	    case progopt_term:
		if (! pip->finval.term) {
	            pip->finval.term = true ;
	            pip->have.term = true ;
	            pip->f.term = true ;
	            if (vl > 0) {
			rs = optbool(vp,vl) ;
	                pip->f.term = (rs > 0) ;
		    }
		}
	        break ;

	    case progopt_mesg:
		if (! pip->finval.mesg) {
	            pip->finval.mesg = true ;
	            pip->f.mesg = true ;
	            if (vl > 0) {
			rs = optbool(vp,vl) ;
	                pip->f.mesg = (rs > 0) ;
		    }
		}
	        break ;

	    case progopt_to:
	        if (vl > 0) {
		    rs = cfdeci(vp,vl,&v) ;
	            pip->to_open = v ;
		}
	        break ;

	    } /* end switch */

	        if (rs < 0) break ;

	    } /* end while (enumerating) */

	    keyopt_curend(kop,&cur) ;
	} /* end if */

ret0:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (procopts) */


local int procdaemon(pip,mntfname)
PROGINFO	*pip ;
cchar	mntfname[] ;
{
	int	rs = SR_OK ;
	int	i ;


	if (mntfname == nullptr)
	    return SR_FAULT ;

	if (mntfname[0] == '\0')
	    return SR_INVALID ;

	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: mnt=%s\n",pip->progname,mntfname) ;

	if (pip->intpoll <= 0)
	    pip->intpoll = TO_POLL ;

	if (pip->efp != nullptr)
	    bflush(pip->efp) ;

	if (pip->debuglevel == 0)
	    rs = uc_fork() ;

	if (rs == 0) {

	    for (i = 0 ; i < 3 ; i += 1) u_close(i) ;

	    uc_sigignore(SIGHUP) ;

	    u_setsid() ;

	    rs = procserve(pip,mntfname) ;

	} /* end if (child) */

ret0:
	return rs ;
}
/* end subroutine (procdaemon) */


local int procserve(pip,mntfname)
PROGINFO	*pip ;
cchar	mntfname[] ;
{
	struct pollfd	fds[2] ;

	time_t	ti_run = pip->daytime ;
	time_t	ti_check = pip->daytime ;
	time_t	ti_wait = pip->daytime ;

	int	rs = SR_OK ;
	int	to = pip->intpoll ;
	int	to_check = TO_CHECK ;
	int	pto ;
	int	nfds ;
	int	n, i ;
	int	cfd, sfd, pfd ;
	int	pipes[2] ;
	int	nhandle = 0 ;


	if (mntfname[0] == '\0')
	    return SR_INVALID ;

	if (to < 1) to = 3 ;

	if (to > to_check) to = to_check ;

	rs = procinfo_begin(pip) ;
	if (rs < 0)
	    goto ret0 ;

	rs = u_pipe(pipes) ;
	sfd = pipes[0] ;		/* server-side */
	cfd = pipes[1] ;		/* client-side */
	if (rs < 0)
	    goto ret1 ;

	rs = u_ioctl(cfd,I_PUSH,"connld") ;
	if (rs < 0)
	    goto ret2 ;

/* attach the client end to the file created above */

	rs = uc_fattach(cfd,mntfname) ;

#if	CF_DEBUG
	if (DEBUGLEVEL(3)) {
	    debugprintf("main/procserve: mntfname=%s\n",mntfname) ;
	    debugprintf("main/procserve: uc_fattach() rs=%d\n",rs) ;
	}
#endif

	if (rs < 0) {
	    if ((! pip->f.quiet) && (pip->efp != nullptr))
	        bprintf(pip->efp,"%s: could not perform mount (%d)\n",
	            pip->progname,rs) ;
	    goto ret3 ;
	}

	u_close(cfd) ;
	cfd = -1 ;

	uc_closeonexec(sfd,true) ;

/* ready */

	nfds = 0 ;
	fds[nfds].fd = sfd ;
	fds[nfds].events = (POLLIN | POLLPRI) ;
	nfds += 1 ;
	fds[nfds].fd = -1 ;
	fds[nfds].events = 0 ;

	pto = (to * POLL_INTMULT) ;
	while ((rs >= 0) && (if_exit || if_int)) {

	    rs = u_poll(fds,nfds,pto) ;
	    n = rs ;
	    pip->daytime = time(nullptr) ;

	    if ((rs >= 0) && (n > 0)) {

		for (i = 0 ; (rs >= 0) && (i < nfds) ; i += 1) {
		    int	fd = fds[i].fd ;
	            int	re = fds[i].revents ;

		    if (fd == sfd) {

	                if ((re & POLLIN) || (re & POLLPRI)) {
	                    struct strrecvfd	passer ;
		            gid_t	gid ;

	                    rs = acceptpass(sfd,&passer,-1) ;
	                    pfd = rs ;

	                    if (rs >= 0) {
			        nhandle += 1 ;
	                        gid = passer.gid ;
	                        rs = procprint(pip,pfd,gid) ;
	                        u_close(pfd) ;
	                    } /* end if */

	                } else if (re & POLLHUP) {
	                    rs = SR_HANGUP ;
	                } else if (re & POLLERR) {
	                    rs = SR_POLLERR ;
	                } else if (re & POLLNVAL) {
	                    rs = SR_NOTOPEN ;
	                } /* end if (poll returned) */

		    } /* end if */

	        } /* end for */

	    } else if (rs == SR_INTR)
	        rs = SR_OK ;

#ifdef	COMMENT
	    if ((rs >= 0) && (if_exit || if_int))
		rs = SR_INTR ;
#endif

	    if (rs >= 0) {
	        if ((pip->daytime - ti_check) >= to_check) {
		     ti_check = pip->daytime ;
		     rs = procinfo_check(pip) ;
		}
	    }

#ifdef	COMMENT
	    if ((rs >= 0) && ((pip->daytime - ti_wait) >= (to*4))) {
		ti_wait = pip->daytime ;
	        rs1 = u_waitpid(-1,nullptr,WNOHANG) ;
	    }
#endif /* COMMENT */

	    if ((rs >= 0) && (pip->intrun > 0) &&
	        ((pip->daytime - ti_run) >= pip->intrun)) {

	        if (pip->efp != nullptr)
	            bprintf(pip->efp,"%s: exiting on run-int timeout\n",
	                pip->progname) ;

	        break ;
	    }

	    if ((pip->efp != nullptr) && if_int)		/* fun only! */
		bprintf(pip->efp,"%s: interrupt\n",	/* fun only! */
	                pip->progname) ;

	} /* end while */

ret4:
	uc_detach(mntfname) ;

ret3:
ret2:
	if (sfd >= 0) {
	    u_close(sfd) ;
	    sfd = -1 ;
	}

	if (cfd >= 0) {
	    u_close(cfd) ;
	    cfd = -1 ;
	}

ret1:
	procinfo_end(pip) ;

ret0:

#if	CF_DEBUG
	if (DEBUGLEVEL(3))
	    debugprintf("main/procserve: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (procserve) */


local int proconce(pip,ofname)
PROGINFO	*pip ;
cchar	ofname[] ;
{
	int	rs = SR_OK ;


	if (ofname == nullptr)
	    return SR_FAULT ;

	if (ofname[0] == '\0')
	    return SR_INVALID ;

	if (pip->debuglevel > 0)
	    bprintf(pip->efp,"%s: msglog=%s\n",pip->progname,ofname) ;

#ifdef	OPTIONAL
	{
	    ustat	sb ;
	    rs = u_stat(ofname,&sb) ;
	    if ((rs >= 0) && S_ISDIR(sb.st_mode))
		rs = SR_ISDIR ;
	}
#endif /* OPTIONAL */

/* do the deed */

	if (rs >= 0)
	    rs = procout(pip,ofname) ;

	return rs ;
}
/* end subroutine (proconce) */


/* open the console */
local int procout(pip,ofname)
PROGINFO	*pip ;
cchar	ofname[] ;
{
	gid_t	gid = getgid() ;

	int	rs ;
	int	fd ;
	int	oflags = O_FLAGS ;
	int	operms = 0666 ;
	int	wlen = 0 ;


	if (ofname == nullptr)
	    return SR_FAULT ;

	if (ofname[0] == '\0')
	    return SR_INVALID ;

	if ((rs = procinfo_begin(pip)) >= 0) {

	    rs = uc_opene(ofname,oflags,operms,pip->to_open) ;
	    fd = rs ;
	    if (rs >= 0) {

	        rs = procprint(pip,fd,gid) ;

	        u_close(fd) ;
	    } /* end if (uc_opene) */

	    procinfo_end(pip) ;
	} /* end if (procinfo) */

ret0:
	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (procout) */


/* print the time to the console */
local int procprint(pip,fd,gid)
PROGINFO	*pip ;
int		fd ;
gid_t		gid ;
{
	ustat	sb ;
	sbuf	b ;
	int	rs = SR_OK ;
	int	rs1 ;
	int	c = 0 ;
	int	wlen = 0 ;
	int	f_terminal = false ;
	int	f_ok = true ;
	int	f ;
	char	linebuf[LINEBUFLEN + 1] ;

	f = ((! pip->have.term) || pip->f.term) ;
	if (f && (! pip->f.daemon)) {
	    if ((rs = u_fstat(fd,&sb)) >= 0) {
	        f_terminal = (S_ISCHR(sb.st_mode)) ? true : false ;
	        if (f_terminal && pip->f.mesg) {
	            f_ok = (sb.st_mode & S_IWGRP) ? 1 : 0 ;
	        }
	    } /* end if (stat) */
	} /* end if (daemon-mode) */

	if (rs < 0)
	    goto ret1 ;
	if (! f_ok)
	    goto ret1 ;

	rs = sbuf_start(&b,linebuf,LINEBUFLEN) ;
	if (rs < 0)
	    goto ret1 ;

	if (f_terminal)
	    sbuf_char(&b,'\r') ;

/* time */

	if (pip->f.o_string && (pip->string != nullptr)) {

	    c += 1 ;
	    sbuf_strw(&b,pip->string,-1) ;

	} /* end if (option-string) */

	if (pip->f.o_time) {
	    char	timebuf[TIMEBUFLEN + 1] ;

	    timestr_logz(pip->daytime,timebuf) ;

	    if (c++ > 0) sbuf_char(&b,' ') ;
	    sbuf_strw(&b,timebuf,23) ;

	} /* end if (option-time) */

/* node-name */

	if ((rs >= 0) && pip->f.o_node) {

	    rs = proginfo_nodename(pip) ;

	    if (rs >= 0) {
	        if (c++ > 0) sbuf_char(&b,' ') ;
	        if (pip->f.o_nodetitle) 
	            sbuf_strw(&b,"node=",-1) ;
	        sbuf_strw(&b,pip->nodename,-1) ;
	    }

	} /* end if (option-nodename) */

/* users (number of logged-in users) */

	if ((rs >= 0) && pip->f.o_users) {

	    rs = procinfo_nusers(pip) ;

	    if (rs >= 0) {
	        if (c++ > 0) sbuf_char(&b,' ') ;
	        sbuf_strw(&b,"users=",-1) ;
	        sbuf_decui(&b,pip->nusers) ;
	    }

	} /* end if (option-users) */

/* number of processes */

	if ((rs >= 0) && pip->f.o_procs) {

	    if ((rs = procinfo_nprocs(pip)) >= 0) {
	        if (c++ > 0) sbuf_char(&b,' ') ;
	        sbuf_strw(&b,"procs=",-1) ;
	        sbuf_decui(&b,pip->nprocs) ;
	    }

	} /* end if (option-processes) */

/* memory usage */

#if	defined(_SC_PHYS_PAGES) && defined(_SC_AVPHYS_PAGES)

	if ((rs >= 0) && pip->f.o_mem) {

	    ulong	n100, mu ;

	    long	mt, ma ;

	    uint	percent ;


	    rs1 = uc_sysconf(_SC_PHYS_PAGES,&mt) ;

	    if (rs1 >= 0)
	        rs1 = uc_sysconf(_SC_AVPHYS_PAGES,&ma) ;

#if	CF_DEBUG
	    if (DEBUGLEVEL(3))
	        debugprintf("main/procprint: mt=%lu ma=%lu\n",mt,ma) ;
#endif

	    if ((rs1 >= 0) && (mt > 0)) {

	        mu = (mt - ma) ;
	        n100 = (mu * 100) ;
	        percent = (n100 / mt) ;

	        if (c++ > 0) sbuf_char(&b,' ') ;
	        sbuf_strw(&b,"mem=",-1) ;
	        sbuf_decui(&b,percent) ;
	        sbuf_char(&b,'%') ;

	    } /* end if */

	} /* end if (memory usage) */

#endif /* defined(_SC_PHYS_PAGES) && defined(_SC_AVPHYS_PAGES) */

/* load averages */

	if ((rs >= 0) && pip->f.o_load) {

	    double	dla[3] ;

	    cchar	*fmt ;


	    if ((rs1 = uc_getloadavg(dla,3)) >= 0) {

	        fmt = "la=(%4.1f %4.1f %4.1f)" ;
	        if (ndig(dla,3) > 2) {
	            fmt = "la=(%5.1f %5.1f %5.1f)" ;
	            ndigmax(dla,3,3) ;
	        }

	        if (c++ > 0) sbuf_char(&b,' ') ;
	        sbuf_printf(&b,fmt,dla[0],dla[1],dla[2]) ;

	    } /* end if (load-averages) */

	} /* end if (option-loadaverages) */

/* done */

	if (f_terminal && pip->f.ansiterm)
	    sbuf_strw(&b,"\033[K",-1) ;

	if (f_terminal)
	    sbuf_char(&b,'\r') ;

	sbuf_char(&b,'\n') ;

	rs1 = sbuf_finish(&b) ;
	wlen = rs1 ;
	if (rs >= 0) rs = rs1 ;
	if (rs >= 0)
	    rs = u_write(fd,linebuf,wlen) ;

ret1:
ret0:
	return (rs >= 0) ? wlen : rs ;
}
/* end subroutine (procprint) */


local int procinfo_begin(pip)
PROGINFO	*pip ;
{


	return SR_OK ;
}
/* end subroutine (procinfo_begin) */


local int procinfo_end(pip)
PROGINFO	*pip ;
{
	int	rs = SR_OK ;
	int	rs1 ;


	if (pip->open.si) {
	    pip->open.si = false ;
	    rs1 = kinfo_close(&pip->si) ;	/* not thread safe! */
	    if (rs >= 0) rs = rs1 ;
	}

	if (pip->open.ui) {
	    pip->open.ui = false ;
	    rs1 = tmpx_close(&pip->ui) ;
	    if (rs >= 0) rs = rs1 ;
	}

	return rs ;
}
/* end subroutine (procinfo_end) */


local int procinfo_nprocs(pip)
PROGINFO	*pip ;
{
	int	rs = SR_OK ;


	if (! pip->open.si) {
	    rs = kinfo_open(&pip->si,pip->daytime) ; /* not thread safe! */
	    pip->open.si = (rs >= 0) ;
	}

	if (rs >= 0) {
	    if ((pip->daytime - pip->ti_sysmisc) >= TO_SYSMISC) {
	        KINFO_DATA	kd ;
	 	pip->ti_sysmisc = pip->daytime ;
		rs = kinfo_sysmisc(&pip->si,pip->daytime,&kd) ;
	    	pip->nprocs = kd.nproc ;
	    }
	}

	return (rs >= 0) ? pip->nprocs : rs ;
}
/* end subroutine (procinfo_nprocs) */


local int procinfo_nusers(pip)
PROGINFO	*pip ;
{
	int	rs = SR_OK ;


	if (! pip->open.ui) {
	    rs = tmpx_open(&pip->ui,nullptr,O_RDONLY) ;
	    pip->open.ui = (rs >= 0) ;
	}

	if (rs >= 0) {
	    if ((pip->daytime - pip->ti_tmpx) >= TO_TMPX) {
	 	pip->ti_tmpx = pip->daytime ;
		rs = tmpx_nusers(&pip->ui) ;
	    	pip->nusers = rs ;
	    }
	}

	return (rs >= 0) ? pip->nusers : rs ;
}
/* end subroutine (procinfo_nusers) */


local int procinfo_check(pip)
PROGINFO	*pip ;
{
	int	rs = SR_OK ;


	if ((rs >= 0) && pip->open.ui)
	    rs = tmpx_check(&pip->ui,pip->daytime) ;

	if ((rs >= 0) && pip->open.si)
	    rs = kinfo_check(&pip->si,pip->daytime) ;

	return rs ;
}
/* end subroutine (procinfo_check) */

local int msglogdev(IDS *idp,cchar *fname) noex {
	ustat	sb ;
	int	rs ;
	int	f = false ;

	if (fname == nullptr)
	    return SR_FAULT ;

	if (fname[0] == '\0')
	    return SR_INVALID ;

	rs = u_stat(fname,&sb) ;
	if (rs >= 0) {
	    rs = permids(idp,&sb,W_OK) ;
	    if (rs >= 0) {
	        f = f || S_ISCHR(sb.st_mode) ;
	        f = f || S_ISFIFO(sb.st_mode) ;
	        f = f || S_ISSOCK(sb.st_mode) ;
	    }
	}
	return (rs >= 0) ? f : rs ;
}
/* end subroutine (msglogdev) */



