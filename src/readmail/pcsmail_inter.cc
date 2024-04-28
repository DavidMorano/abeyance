/* pcsmail_inter SUPPORT */
/* lang=C++20 */

/* collect the mail-message to send, interactively */
/* version %I% last-modified %G% */


/************************************************************************

	= 94-01-06, David A­D­ Morano
	This subroutine was adopted from the 'main' subroutine of
	the old PCS-SENDMAIL program.

************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/wait.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include	<unistd.h>
#include	<cerrno>
#include	<csignal>
#include	<ctime>
#include	<cstring>
#include	<usystem.h>
#include	<baops.h>
#include	<logfile.h>
#include	<bfile.h>
#include	<char.h>
#include	<ascii.h>
#include	<userinfo.h>
#include	<pcsconf.h>

#include	"localmisc.h"
#include	"config.h"
#include	"defs.h"
#include	"prompt.h"
#include	"header.h"



/* local subroutine defines */

#define		MAXARGINDEX	100
#define		MAXARGGROUPS	(MAXARGINDEX/8 + 1)


/* external subroutines */

extern char	*putheap() ;
extern char	*timestr_log() ;


/* external data */

extern struct global	g ;

	extern struct pcsconf	p ;

	extern struct userinfo	u ;


/* global data */


/* forward references */


/* local static data */





int inter()
{
	bfile	errfile, *efp = &errfile ;
	bfile	infile, *ifp = &infile ;
	bfile	outfile, *ofp = &outfile ;
	bfile	msgfile, *mfp = &msgfile ;
	bfile	tmpfile, *tfp = &tmpfile ;
	bfile	*fpa[3] ;

	struct	stat	sb ;

	struct tm	*timep ;

	struct group	*gp ;

	off_t		offset ;

	int		len, rs, status ;
	int		wstatus ;
	int		i, l ;
	int	f_optminus, f_optplus, f_optequal ;
	int	f_done = FALSE ;
	int	f_extra = FALSE ;
	int	f_version = FALSE ;
	int	f_usage = FALSE ;
	int		f_send ;
	int		pid_child ;

	char	argpresent[MAXARGGROUPS] ;
	char		*option, *tmp ;
	char		buf[BUFSIZE + 1], *bp ;
	char		linebuf[LINELEN + 1] ;
	char		*namep, *cp, *cp2 ;
	char		*realname ;


/* go */

	if (isfile) {

	    if (access(filename,R_OK) < 0) {

	        logfile_printf(&g.eh,"main: could not access FILENAME \"%s\"\n",
	            filename) ;

	    }

	    getheader(filename,u.mailname) ;

	    tonames = getnames(recipient) ;

	    bccnames = getnames(bcopyto) ;

	    ccnames = getnames(copyto) ;

/* if we have a return path, then we do not include the rest of the file */

#ifdef	COMMENT
	    if (isret) {

	        isfile = 0 ;	/* added to force reply message */
	        logfile_printf(&g.eh,"main: turned off 'isfile'\n") ;

	    }
#endif

	} /* end if (we have a file) */

/* the message itself */

/* if we already have recipients then the following will not ask ? */

	if (ex_mode == EM_PCSMAIL) {

	    prompt(ALL) ;

	}

/* write the headers that we have so far to the message file */

	writeheader(mfp,TRUE) ;

	bclose(mfp) ;

/* now we fork so that we can process the inputting of the message */

	fp = NULL ;
	pid_child = 0 ;
	if (ex_mode != EM_PC) {

/*
 This process collects the message from the terminal and	 
 stuffs it into tempfile while the main branch continues on 
 and reads in the humongously large translation table, which 
 takes anywhere from 4 to 8 seconds to read in! Then it waits
 for this process to terminate, and takes appropriate action 
 based on the termination status of this process. If this    
 process terminates normally (exit status 0) then processing 
 the message continues as usual. If terminal status is non-zero 
 then the main branch exits. If wait returns error then the  
 main branch saves the message in $HOME/dead.letter and exits 
*/

	    bflush(g.efp) ;

	    bflush(g.ofp) ;

	pid_child = -1 ;
	    if ((! g.f.interactive) || iswait || 
		((pid_child = uc_fork()) <= 0)) {

/* if we forked, the child is executing the following code */

	        if ((rs = bopen(mfp,tempfile,"wca",0600)) < 0) {

	            bprintf(g.efp,"%s: could not open TMP file (rs %d)\n",
	                g.progname,rs) ;

	            logfile_printf(&g.lh,"could not open TMP file (rs %d)\n",
	                g.progname,rs) ;

	            goto badret ;
	        }

	        bseek(mfp,0L,SEEK_END) ;

	        if (ex_mode == EM_PCSMAIL) {

/* body of the message */

	            if (*message != '\0') {
/* we were given the message on the command invocation line */
	                bprintf(mfp,"\n%s\n",message) ;
	            } else if (isfile) {

/* we were not given the message body on the command invocation line */

	                if ((rs = bopen(tfp,filename,"r",0600)) < 0) {

	                    bprintf(g.efp,
	                        "%s: ERROR cannot open \"%s\"\n",
				filename) ;

	                    logfile_printf(&g.eh,
	                        "cannot read file \"%s\" rs=%d\n",
	                        filename,rs) ;

	                    goto badret ;
	                }

/* copy the file to the mail file */

	                rs = 0 ;

/* skip any headers that may be in the file */

#ifdef	COMMENT
	                len = 0 ;
	                while ((l = breadln(tfp,linebuf,LINELEN)) > 0) {

				len += l ;
	                    if (linebuf[0] == '\n') break ;

			}
#else
	                if ((l = skipheaders(tfp,linebuf,LINELEN)) > 0)
				bwrite(mfp,linebuf,l) ;
#endif

/* copy the body of the message that was given us in the input file */

	                while ((rs = bcopyblock(tfp,mfp,BUFLEN)) > 0)
	                    len += rs ;

	                bclose(tfp) ;

	                if (rs < 0) {
	                    logfile_printf(&g.lh,
	                        "possible full filesystem (rs %d)\n",
	                        rs) ;
	                    bprintf(g.efp,
	                        "%s: possible full filesystem (rs %d)\n",
	                        g.progname,rs) ;
	                }
	            } /* end if (have a file given) */

	        } /* end if (regular mode) */

	        bflush(mfp) ;

	        if (isedit) {

	            bclose(mfp) ;

	            if (iseforward) {
	                fappend(eforwfile,tempfile) ;
	                unlink(eforwfile) ;
	                iseforward = 0 ;
	            } /* end if (we have a forward file) */

	            editit(tempfile) ;

	        } else if ((! isfile) && (*message == '\0')) {

	            if (g.f.interactive) bprintf(g.ofp,
	                "enter message - terminate by period or EOF :\n") ;

	            while (((len = breadln(g.ifp,linebuf,LINELEN)) > 0) && 
	                (strncmp(linebuf,".\n",2) != 0)) {

	                linebuf[len] = '\0' ;
	                if (g.f.interactive && (strcmp(linebuf,"?\n") == 0)) {

	                    help(4) ;

	                    continue ;
	                }

	                bwrite(mfp,linebuf,len) ;

	            } /* end while */

	            bclose(mfp) ;

	        } else {

	            bclose(mfp) ;

	        } /* end if (gathering or editing the file) */

	        fp = NULL ;

/* exit only if fork did happen, otherwise just continue */

	        if (g.f.interactive && (! iswait) && (pid_child != -1))
	            exit(0) ;

	    } /* end if (of forked off code) */

/* while the other process is collecting input from the terminal */
/* the main process ignores any interrupts and continues with its*/
/* housekeeping chores, i.e. read translation table from the disk*/

	} /* end if (not running as PCS PostCard) */

/* get last->myname conversion table */

	gettable(u.nodename) ;

	if ((tablelen == 0) && (namelist[0] != '\0'))
	    bprintf(g.efp,
	        "%s: warning - no entries in the translation table\n",
	        g.progname) ;


/* This is where the join happens 				*/
/* the join needs to be done only if the forking actually	*/
/* happened. pid_child has a positive non-zero value only if the	*/
/* forking actually happened					*/

	if (pid_child > 0) {

	    while ((wstatus = u_waitpid(pid_child,&status,0)) >= 0) {
	        if (wstatus == pid_child) break ;
	    }

	    if (wstatus == -1) {

	        goto badret ;
	    }

	    if (status != 0) goto goodret ;

	} /* end if */

	if (pid_child > 0) {

/* scan message for changes */

	    if (isedit != 0) {
	        *subject = *recipient = '\0';			/* (11/30) */
	        *copyto  = *bcopyto = '\0' ;
	        isedit = 0 ;	/* MR# gw85-00801 2/7/85 (JM)*/
	    }

	    getheader(tempfile,syscom) ;	/* (11/30) */

	    if (isedit != 0) {

	        getfield(tempfile,HS_CC,copyto) ;

	        getfield(tempfile,HS_BCC,bcopyto) ;

	    }

	    tonames = getnames(recipient) ;

	    ccnames = getnames(copyto) ;

	    bccnames = getnames(bcopyto) ;

	    isedit = 0 ;

	} /* end if (gettinu.name ?) */

/* convert user name (in 'username') to real name and put in variable 'from' */

#ifdef	COMMENT
	myname = getname(u.username,buf) ;

	if (myname == 0) u.name = putheap(buf) ;
#endif


/* create the 'fromaddr' header field */

	strcpy(fromaddr,p.mailnode) ;

	strcat(fromaddr,"!") ;

	strcat(fromaddr,u.username) ;


#ifndef	COMMENT

	namep = NULL ;
	if (f_name) {

	    if (u.mailname != NULL)
	        namep = u.mailname ;

	    else if (u.gecosname != NULL)
	        namep = u.gecosname ;

	    else if (u.name != NULL)
	        namep = u.name ;

	    else if (f_fullname && (u.fullname != NULL))
	        namep = u.fullname ;

	}

	if (namep != NULL) {

	    if (strchr(namep,' ') != NULL) {

	        if (f_internet) sprintf(from, "%s@%s (%s)", 
	            u.username,MAILNODE,namep) ;

	        else sprintf(from, "%s!%s (%s)", 
	            p.mailnode,u.username,namep) ;

	    } else {

	        if (f_internet) sprintf(from, "%s <%s@%s>", 
	            namep, u.username, MAILNODE) ;

	        else sprintf(from, "%s <%s!%s>", 
	            namep, p.mailnode,u.username) ;

	    }

	} else {

	    if (f_internet) sprintf(from, "%s@%s", 
	        u.username, MAILNODE) ;

	    else sprintf(from, "%s!%s", 
	        p.mailnode,u.username) ;

	}
#else
	if (*from == '\0') {

	    if (myname < 0) sprintf(from,"%s!%s",
	        u.nodename,u.username) ;

/* setup local or internet from field */

	    if ((tonames != 0) && 
	        (strpbrk(recipient,"@_") != NULL) || f_internet)

/* this is going internet */

	        if (myname >= 0) {

	            strcpy(syscom,from) ;

	            sprintf(from,"%s@%s.%s (%s)",
	                u.username,p.mailnode,p.orgdomain,syscom) ;

	        }
	        else {

	            sprintf(from,"%s@%s.%s",
	                u.username,p.mailnode,p.orgdomain) ;

	        }
	}
#endif

	if (ex_mode != EM_PCSMAIL) {

	    if (ex_mode == EM_PC) redo_message() ;

	    getheader(tempfile,from) ;

	    ccnames = bccnames = 0 ;

	} else {

	    if (iseforward) {
	        fappend(eforwfile,tempfile) ;
	        unlink(eforwfile) ;
	    }

/* check TO:, CC:, BCC: list */

	    getfield(tempfile,HS_CC,copyto) ;

	    getfield(tempfile,HS_BCC,bcopyto) ;

	    if (*copyto != '\0') ccnames = getnames(copyto) ;

	    if (*bcopyto != '\0') bccnames = getnames(bcopyto) ;

	    checkreclist(0) ;

	    redo_message() ;

/* ask for sending command */
opts:
	    if (ambiguous) redo_message() ;

	    if (! g.f.interactive) {
	        strcpy(command,"send") ;
	        isedit = 0 ;
	    } else {
	        if (*recipient == '\0') {
	            bprintf(g.ofp,"\nno recipient(s) specified\n") ;
	            tonames = 0 ;
	            prompt(TO) ;
	            strcpy(realto, recipient) ;
	            checkreclist(0) ;
	            redo_message() ;
	        }

	        if (error != 0) {

	            bprintf(g.ofp,"%s%s","\nthe recipient lists contains",
	                " unknown names\n") ;

	            bprintf(g.ofp,"%s%s","do you really want to send",
	                " the message ? [no] ") ;

	            if (fgetline(stdin,s,BUFSIZE) <= 0) {

	                goto badret ;
	            }

	            if (*s != 'y') {
	                bprintf(g.ofp,"%s%s","OK, please edit",
	                    " the message or quit\n") ;
	            }
	        }

	        if (isedit != 0) {
		    strcpy(command,"edit") ;
	        } else {
		    prompt(SENDCOM) ;
		}

	    } /* end if */

	    cp = command ;
	    while (CHAR_ISWHITE(*cp)) cp += 1 ;

	    option = strtok(cp,",: \t") ;

/* top of parsing the command */
opts1:
	    if ((option == NULL) || (! g.f.interactive))
	        isdef = 1 ;

	    else {

/* send with current list of names */

	        f_send = FALSE ;
	        switch ((int) *option) {

	        case 's':
	            standard = 1 ;
	            copy = 0 ;
	            verify = 0 ;
	            f_send = TRUE ;
	            break ;

/* review the message */
	        case 'r':
	            reviewit(option) ;
	            break ;

/* check recipient list */
	        case 'c':
	            checkit() ;
	            break ;

/* edit the message */
	        case 'e':
	            editit(tempfile) ;
	            checkreclist(0) ;
	            redo_message() ;
	            ambiguous = 0 ;
	            break ;

/* terminate the mail */
	        case 'q':
	            if (fork() == 0) {

	                close(0) ;

	                close(1) ;

	                close(2) ;

	                if (fork() == 0) {

	                    sleep(100) ;

	                    unlink(tempfile) ;

	                }

	            }

	            goto goodret ;

/* help user */
	        case '?':
	            help(0) ;

	            break ;

/* unknown. try again. */
	        default:
	            bprintf(g.ofp,"unknown command -- please try again") ;

	        } /* end switch */

	        if (! f_send) goto opts ;

	    } /* end if */

/* check for send options */
opts2:

/* check for default options */
/* MR# gx84-33465 JM 2/7/85 *//*begin*/

	    if (isdef != 1) {

	        standard = 1 ;
	        copy = verify = 0 ;
	    }

/* MR# gx84-33465 JM 2/7/85 *//*end*/

	    if ((! g.f.interactive) || isdef) option = NULL ;

	    else if ((option = strtok(NULL,", \t")) == NULL) {

	        prompt(SENDOPT) ;

	        option = strtok(sendopt,"+, \t") ;

	    }

	    while (option != NULL) {

/* set flags for options */
	        switch (*option) {

/* acknowledge delivery of message */
	        case 'd':
	            break ;

/* add sender to list of recipients */
	        case 'f':
	            copy = TRUE ;
	            break ;

/* notify recipient of incomming mail */
	        case 'n':
	            break ;

/* verify that the message is sent */
	        case 'v':
	            verify = TRUE ;
	            break ;

/* standard mail */
	        case 's':
	            standard = TRUE ;
	            verify = FALSE ;
	            break ;

/* if check, edit, review, go back */
	        case 'c':
	        case 'e':
	        case 'r':
	            goto opts1; /* break; */

/* allow quit here too */
	        case 'q':
	            goto goodret ;

/* fall through to next case */
	        case '?':
	            help(1) ;

	            strcpy(sendopt,"send") ;

	            goto opts2; /* break; */

/* unknown ; try again */
	        default:
	            bprintf(g.efp,"%s%s","unknown send option",
	                " -- please try again.\n") ;

	            strcpy(sendopt,"send") ;

	            goto opts2 ;	/* break; */
	        }

	        option = strtok(0,":+, 	") ;

	    } /* end while */

	    if (! g.f.interactive) {

	        getheader(tempfile,from) ;

	        if (*recipient != '\0') tonames = getnames(recipient) ;

	        if (*copyto != '\0') ccnames = getnames(copyto) ;

	        if (*bcopyto != '\0') bccnames = getnames(bcopyto) ;

	    }

	} /* end if (execution mode PCSMAIL or not) */

/* ignore signals */

/* 
	Fork off code to issue unix 'mail' commands and 
	  then do own notification (since Unix doesn't always),
	  once separately for each recipient (to avoid UNIX mail 'to' line).
	  Do the actual forking only if the user has not specified the '+wait'
	  option.  If 'ex_mode' is EM_PC, forking doesn't happen because
	  'iswait' is set to 1 in these modes.
*/

#ifdef COMMENT
	fclose(errlog) ;
#endif

/* fork off to UNIX top-level */

	if ((tonames > 0) && 
	    (iswait || ((pid_child = fork()) == 0) || (pid_child == -1))) {

	    deliverem() ;

/* if we forked, the child exits here */

	    goto goodret ;

	} /* end of forked off code */

/* no one to send to Sighhh...! */

	if (tonames == 0) {

	    if (access(tempfile,R_OK) < 0) {
	        debugprintf("main: no tempfile here\n") ;
	        sprintf(syscom,"cp /dev/null %s",tempfile) ;
	        system(syscom) ;
	    }

	    sprintf(syscom, "cat %s >> %s/%s\n", tempfile,
	        u.homedname, DEADFILE) ;

	    system(syscom) ;

	    unlink(tempfile) ;

	    if (isforward > 0) unlink(forwfile) ;

	    if (g.f.interactive) {

	        bprintf(g.ofp,"\nno recipients were specified\n") ;

	        bprintf(g.ofp,"mail saved in file '%s'\n",DEADFILE) ;

	    }

	    goto badret ;
	}

	if (g.f.interactive) {

	    bprintf(g.ofp,"sending mail ") ;

	    bputc(g.ofp,C_LPAREN) ;

	    if (standard) bprintf(g.ofp,"standard") ;

	    if (verify) bprintf(g.ofp," verify") ;

	    if (copy) bprintf(g.ofp," filecopy") ;

	    if (f_notify) bprintf(g.ofp," notify") ;

	    bprintf(g.ofp,"%c\n",C_RPAREN) ;

	}

done:
goodret:
#ifdef	COMMENT
	if (tempfile[0] != '\0') unlink(tempfile) ;
#endif

	bclose(g.ofp) ;

	bclose(g.efp) ;

	return OK ;

badret:
#ifdef	COMMENT
	if (tempfile[0] != '\0') unlink(tempfile) ;
#endif

	bclose(g.ofp) ;

	bclose(g.efp) ;

	return BAD ;

badargvalue:
	bprintf(efp,"%s: bad argument value was specified\n",
	    g.progname) ;

	goto badret ;

badargnum:
	bprintf(efp,"%s: not enough arguments specified\n",
	    g.progname) ;

	goto badret ;

badinopen:
	bprintf(g.efp,"%s: could not open the input (rs %d)\n",
	    g.progname,rs) ;

	goto badret ;

badoutopen:
	bprintf(g.efp,"%s: could not open the output (rs %d)\n",
	    g.progname,rs) ;

	goto badret ;

version:
	bprintf(g.efp,"%s: version %s/%s\n",
	    g.progname,
	    VERSION,(g.f.sysv_ct ? "SYSV" : "BSD")) ;

	goto goodret ;
}
/* end subroutine (inter) */



