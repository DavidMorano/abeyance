/* postfile SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* indexed POST file */
/* version %I% last-modified %G% */

#define	CF_SAFE		1		/* safe mode */
#define	CF_LOCKING	0		/* use file locking */
#define	CF_HOLDING	1		/* use file-map holding */
#define	CF_MEMSYNC	1		/* use memory synchronization? */

/* revision history:

	= 2002-05-01, David A­D­ Morano
	This object module was created from some previous code, of
	which I longer know what it was.

*/

/* Copyright © 2002 David A­D­ Morano.  All rights reserved. */

/******************************************************************************

  	Object:
	postfile

	Description:
	This object module provides an interface to a data base of
	information about the GECOS name in the system PASSWD
	database.  The system PASSWD database (whether a file or
	whatever) was enumerated (separately) and an index file was
	made with several indices to lookup usernames based on a
	real name.  For starters only indices consisting of using:
	the first character of the last name, the first 3 characters
	of the last name, and the first character of the first name
	have been used.  But future index files might provide more
	combinations, like using the first 3 characters of the last
	name combined with the first character of the first name!
	The various data and indices were written into a file.  We
	are accessing that file within this object.

*****************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/mman.h>		/* Memory Management */
#include	<unistd.h>
#include	<fcntl.h>
#include	<climits>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<usystem.h>
#include	<mallocstuff.h>
#include	<storeitem.h>
#include	<dstr.h>
#include	<realname.h>
#include	<endian.h>
#include	<hash.h>
#include	<hashindex.h>
#include	<strwcpy.h>
#include	<intceil.h>
#include	<randlc.h>
#include	<isfiledesc.h>
#include	<localmisc.h>		/* |TIMEBUFLEN| */

#include	"postfile.h"


/* local defines */

#define	PF		postfile
#define	PF_INFO		postfile_info
#define	PF_CUR		postfile_cur
#define	PF_ENT		postfile_ent

#define	MODP2(v,n)	((v) & ((n) - 1))

#define	TO_FILECOME	5
#define	TO_OPEN		(60 * 60)
#define	TO_ACCESS	(1 * 60)
#define	TO_LOCK		10		/* seconds */

#define	TI_MINUPDATE	4		/* minimum time between updates */

#define	NSHIFT		6


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

template<typename ... Args>
static int postfile_ctor(dw *op,Args ... args) noex {
    	POSTFIE		*hop = op ;
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = memclear(hop) ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (postfile_ctor) */

static int postfile_dtor(dw *op) noex {
	int		rs = SR_FAULT ;
	if (op) {
	    rs = SR_OK ;
	} /* end if (non-null) */
	return rs ;
}
/* end subroutine (postfile_dtor) */

template<typename ... Args>
static inline int postfile_magic(dw *op,Args ... args) noex {
	int		rs = SR_FAULT ;
	if (op && (args && ...)) {
	    rs = (op->magic == POSTFILE_MAGIC) ? SR_OK : SR_NOTOPEN ;
	}
	return rs ;
}
/* end subroutine (postfile_magic) */

static int	postfile_fileheader(PF *) noex ;
static int	postfile_holdget(PF *,time_t) noex ;
static int	postfile_holdrelease(PF *,time_t) noex ;

#if	CF_LOCKING
static int	postfile_lockget(PF *,int) noex ;
static int	postfile_lockrelease(PF *) noex ;
#endif

static int	postfile_fileopen(PF *,time_t) noex ;
static int	postfile_fileclose(PF *) noex ;
static int	postfile_keymatchlast(PF *,int,int,char *,int) noex ;
static int	postfile_keymatchall(PF *,int,int,realname *) noex ;

static uint	ceiling(uint,uint) noex ;


/* local variables */

enum headers {
	header_writetime,
	header_writecount,
	header_rectab,
	header_rectablen,
	header_strtab,
	header_strtabsize,
	header_indexl1,
	header_indexl3,
	header_indexf,
	header_indexlen,
	header_overlast
} ;

constexpr cpcchar	localfs[] = {
	"ufs",
	"tmpfs",
	"lofs",
	nullptr
} ;


/* exported variables */


/* exported subroutines */

int postfile_open(PF *,cchar *fname) noex {
	int	rs ;
	USTAT	sb ;
	uint	*table ;
	time_t	daytime ;

	int	i, cl ;
	int	prot, flags ;
	int	magiclen ;
	int	size ;

	cchar	*cp ;


	if (op == nullptr)
	    return SR_FAULT ;

	if (fname == nullptr)
	    return SR_FAULT ;


	op->fd = -1 ;
	op->oflags = O_RDONLY ;
	op->operm = 0666 ;

	rs = u_open(fname,op->oflags,op->operm) ;

	if (rs < 0)
	    goto bad0 ;

	op->fd = rs ;
	rs = u_fstat(op->fd,&sb) ;

	if (rs < 0)
	    goto bad1 ;

/* local or remote */

	rs = isfsremote(op->fd) ;
	op->f.remote = (i > 0) ;
	if (rs < 0)
	    goto bad1 ;

/* store filename away */

	op->fname = mallocstr(fname) ;
	if (op->fname == nullptr) {
	    rs = SR_NOMEM ;
	    goto bad1 ;
	}

	size = 16 + 4 + (header_overlast * szof(int)) ;

/* wait for the file to come in if it is not yet available */

	for (i = 0 ; (i < TO_FILECOME) && (rs >= 0) && (sb.st_size < size) ;
	    i += 1) {

	    sleep(1) ;

	    rs = u_fstat(op->fd,&sb) ;

	} /* end while */

	if (rs < 0)
	    goto bad2 ;

	rs = SR_TIMEDOUT ;
	if (i >= TO_FILECOME)
	    goto bad2 ;

	if (sb.st_size < size)
	    goto bad2 ;

	op->mtime = sb.st_mtime ;
	op->filesize = sb.st_size ;
	op->pagesize = getpagesize() ;

/* OK, continue on */

	if (op->filesize >= size) {

/* map it */

	    prot = PROT_READ ;
	    flags = MAP_SHARED ;
	    rs = u_mmap(nullptr,(size_t) op->filesize,prot,flags,
	        op->fd,0L,&op->mapbuf) ;

	    if (rs < 0)
	        goto bad2 ;

/* OK, check it out */

	    rs = postfile_fileheader(op) ;

	    if (rs < 0)
	        goto bad3 ;

/* ok, we're good (?) */

	    u_time(&daytime) ;
	    op->opentime = daytime ;
	    op->accesstime = daytime ;
	    op->f.fileinit = true ;
	} /* end if (file had some data) */

/* we should be good */

	op->magic = POSTFILE_MAGIC ;

ret1:
	u_close(op->fd) ;
	op->fd = -1 ;

ret0:
	return rs ;

/* we're out of here */
bad3:
	u_mmapend(op->mapbuf,(size_t) op->filesize) ;

bad2:
	free(op->fname) ;

bad1:
	u_close(op->fd) ;
	op->fd = -1 ;

bad0:
	return rs ;
}
/* end subroutine (postfile_open) */

int postfile_close(PF *op) noex {
	int		rs ;
	int		rs1 ;
	if ((rs = postfile_magic(op)) >= 0) {
	    if (op->mapbuf) {
		void	*md = op->mapbuf ;
		csize	ms = op->filesize ;
	        rs1 = u_mmapend(md,ms) ;
		if (rs >= 0) rs = rs1 ;
	    }
	    if (op->fd >= 0) {
	        rs1 = u_close(op->fd) ;
	        if (rs >= 0) rs = rs1 ;
	    }
	    op->magic = 0 ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (postfile_close) */

int postfile_count(PF *op) noex {
    	int		rs ;
	if ((rs = postfile_magic(op)) >= 0) {
	    rs = (op->rtlen - 1) ;
	}
	return rs ;
}
/* end subroutine (postfile_count) */

/* calculate the index table length (number of entries) at this point */
int postfile_countindex(PF *op) noex {
    	int		rs ;
	if ((rs = postfile_magic(op)) >= 0) {
	    rs = op->rilen ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (postfile_countindex) */

int postfile_curbegin(PF *op,PF_CUR *curp) noex )
    	int		rs ;
	if ((rs = postfile_magic(op,curp)) >= 0) {
	    op->f.cursor = true ;
	    op->f.cursorlockbroken = false ;
	    op->f.cursoracc = false ;
	    for (int i = 0 ; i < POSTFILE_NINDICES ; i += 1) {
	        cp->i[i] = -1 ;
	    }
	    cp->magic = POSTFILE_MAGIC ;
	} /* end if (magic) */
	return rs ;
}
/* end subroutine (postfile_curbegin) */

int postfile_curend(PF *op,PF_CUR *curp) noex {
    	int		rs ;
	if ((rs = postfile_magic(op)) >= 0) {
	    custime	dt = getustime ;
	    if (op->f.cursoracc) {
	        op->accesstime = dt ;
	    }
	    op->f.cursor = false ;
#if	CF_LOCKING
	    if (op->f.lockedread || op->f.lockedwrite) {
	        postfile_lockrelease(op) ;
	    }
#endif
#if	CF_HOLDING
	    if (op->f.held) {
	        rs = postfile_holdrelease(op,dt) ;
	    }
#endif
	    for (int i = 0 ; i < POSTFILE_NINDICES ; i += 1) {
	        cp->i[i] = -1 ;
	    }
	    cp->magic = 0 ;
	} /* end if (magic) */
	return rs ;
} /* end subroutine (postfile_curend) */

int postfile_curenum(PF *op,PF_CUR *curp,cc *namep,cc *userp) noex {
    	int		rs ;
	if ((rs = postfile_magic(op,curp)) >= 0) {

	time_t	daytime ;

	int	ri, si ;
	int	ui ;

	char	*sp ;
	char	*cp ;



	if (! op->f.cursor)
	    return SR_INVALID ;

	ri = (cup->i[0] < 1) ? 1 : (cup->i[0] + 1) ;

/* capture a hold on the file */

#if	CF_HOLDING
	if (! op->f.held) {

	    u_time(&daytime) ;

	    rs = postfile_holdget(op,daytime) ;

	    if (rs > 0)
	        rs = postfile_fileheader(op) ;

	    if (rs < 0)
	        return rs ;

	}
#endif /* CF_HOLDING */


/* ok, we're good to go */

	if (ri >= op->rtlen)
	    return SR_NOTFOUND ;

	if (np != nullptr) {
	    dstr	ss[5] ;
		/* first */
	    si = op->rectab[ri].first ;
	    ss[0].s = (char *) (op->stab + si) ;
	    ss[0].slen = -1 ;
		/* middle-1 */
	    si = op->rectab[ri].m1 ;
	    ss[1].s = (char *) (op->stab + si) ;
	    ss[1].slen = -1 ;
		/* middle-2 */
	    si = op->rectab[ri].m2 ;
	    ss[2].s = (char *) (op->stab + si) ;
	    ss[2].slen = -1 ;
		/* middle=3 */
	    ss[3].s = nullptr ;
	    ss[3].slen = 0 ;
		/* last */
	    si = op->rectab[ri].last ;
	    ss[4].s = (char *) (op->stab + si) ;
	    ss[4].slen = -1 ;
		/* done */
	    rs = np->start(ss) ;
	} /* end if */

	if (rs >= 0) {

	    ui = op->rectab[ri].username ;
	    if (up != nullptr) {
	        cp = strwcpy(up,(op->stab + ui),POSTFILE_USERNAMELEN) ;
	        rs = cp - up ;
	    } else {
	        rs = strlen(op->stab + ui) ;
	   }
	    cup->i[0] = ri ;
	} /* end if */

	return rs ;
} /* end subroutine (postfile_curenum) */

/* fetch an entry by key lookup */
int postfile_fetch(op,np,cup,opts,up)
POSTFILE	*op ;
realname	*np ;
POSTFILE_CUR	*cup ;
int		opts ;
char		*up ;
{
	POSTFILE_CUR	cur ;

	time_t		daytime = 0 ;

	uint		rhash ;

	const int	ns = NSHIFT ;

	int	rs = SR_OK, i, wi, si, ui, hi, ri ;
	int	hl, ul, c, n ;
	int	klen[POSTFILE_NINDICES] ;
	int	f_cur = false ;

	char	*sp ;
	char	*cp ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != POSTFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif

	if (cup == nullptr) {

	    cup = &cur ;
	    for (i = 0 ; i < POSTFILE_NINDICES ; i += 1)
	        cup->i[i] = -1 ;

	} else {

	    f_cur = true ;
	    if (! op->f.cursor)
	        return SR_INVALID ;

	}

	if (np == nullptr)
	    return SR_FAULT ;

#ifdef	COMMENT
	if (up != nullptr)
	    *up = '\0' ;
#endif

/* do we have a hold on the file ? */

#if	CF_HOLDING
	if (! op->f.held) {

	    u_time(&daytime) ;

	    rs = postfile_holdget(op,daytime) ;

	    if (rs > 0) {
	        rs = postfile_fileheader(op) ;
	    }

	    if (rs < 0)
	        return rs ;

	}
#endif /* CF_HOLDING */

/* continue with regular fetch activities */

	op->f.cursoracc = true ;	/* doesn't hurt if no cursor ! */
	n = op->rilen ;

/* which index do we want to use ? */

	wi = (np->len.last < 3) ? 0 : 1 ;

/* OK, we go from here */

	if (cup->i[wi] < 0) {

	    sp = np->last ;
	    hl = MIN(np->len.last,((wi == 0) ? 1 : 3)) ;

	    rhash = hash_elf(sp,hl) ;

	    hi = hashindex(rhash,op->rilen) ;
/* start searching! */
	    if (op->ropts & POSTFILE_OSEC) {
	        c = 0 ;
	        while ((ri = (op->recind[wi])[hi][0]) != 0) {

	            if (postfile_keymatchlast(op,opts,ri,sp,hl))
	                break ;

	            op->collisions += 1 ;
	            if (op->ropts & POSTFILE_ORANDLC) {
	                rhash = randlc(rhash + c) ;
		    } else {
	                rhash = ((rhash << (32 - ns)) | (rhash >> ns)) + c ;
		    }
	            hi = hashindex(rhash,n) ;
	            c += 1 ;
	        } /* end while */
	        if (ri == 0) {
	            rs = SR_NOTFOUND ;
		}
	    } /* end if (secondard hasing) */

	} else {
	    hi = cup->i[wi] ;
	    if (hi != 0) {

	        ri = (op->recind[wi])[hi][0] ;
	        if (ri != 0) {

	            hi = (op->recind[wi])[hi][1] ;
	            if (hi != 0)
	                ri = (op->recind[wi])[hi][0] ;

	            else
	                rs = SR_NOTFOUND ;

	        }

	    } else
	        rs = SR_NOTFOUND ;

	} /* end if (preparation) */
	if (rs >= 0) {

	    while ((ri = (op->recind[wi])[hi][0]) != 0) {

	        if (postfile_keymatchall(op,opts,ri,np))
	            break ;

	        hi = (op->recind[wi])[hi][1] ;
	        if (hi == 0)
	            break ;

	        op->collisions += 1 ;

	    } /* end while */

	    if ((ri == 0) || (hi == 0)) {
	        rs = SR_NOTFOUND ;
	    }
	} /* end if (following the existing chain) */

	if (rs >= 0) {

	    ui = op->rectab[ri].username ;
	    if (up != nullptr) {
	        cp = strwcpy(up,(op->stab + ui),POSTFILE_USERNAMELEN) ;
	        ul = (cp - up) ;
	    } else {
	        ul = strlen(op->stab + ui) ;
	    }
/* update cursor */
	    if (f_cur) {
	        cup->i[wi] = hi ;
	    }
	} /* end if (got one) */

#if	CF_HOLDING
	if (! op->f.cursor) {

	    if (daytime == 0)
	        u_time(&daytime) ;

	    op->accesstime = daytime ;
	    rs = postfile_holdrelease(op,daytime) ;

	}
#endif /* CF_HOLDING */

	return (rs >= 0) ? ul : rs ;
}
/* end subroutine (postfile_fetch) */


#ifdef	COMMENT

/* get the entries (serially) */
int postfile_get(op,ri,rpp)
POSTFILE	*op ;
int		ri ;
POSTFILE_ENT	**rpp ;
{

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != POSTFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif

	if (rpp == nullptr)
	    return SR_FAULT ;

	if ((ri < 0) || (ri >= op->rtlen))
	    return SR_NOTFOUND ;

	*rpp = nullptr ;
	if (ri > 0) {
	    *rpp = op->rectab + ri ;
	}
	return ri ;
}
/* end subroutine (postfile_get) */

#endif /* COMMENT */


/* get information about all static branches */
int postfile_info(op,rp)
POSTFILE	*op ;
POSTFILE_INFO	*rp ;
{
	int	rs = SR_OK ;


	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != POSTFILE_MAGIC)
	    return SR_NOTOPEN ;

	if (rp == nullptr)
	    return SR_FAULT ;

	if (rp != nullptr) {

	    rp->collisions = op->collisions ;

	}

	return rs ;
}
/* end subroutine (postfile_info) */


/* do some checking */
int postfile_check(op,daytime)
POSTFILE	*op ;
time_t		daytime ;
{
	int	rs = SR_OK ;

	if (op == nullptr)
	    return SR_FAULT ;

	if (op->magic != POSTFILE_MAGIC)
	    return SR_NOTOPEN ;

	if (op->fd < 0)
	    return SR_OK ;

	if ((daytime - op->accesstime) > TO_ACCESS)
	    goto closeit ;

	if ((daytime - op->opentime) > TO_OPEN)
	    goto closeit ;

	return rs ;

/* handle a close out */
closeit:
	rs = postfile_fileclose(op) ;

	return rs ;
}
/* end subroutine (postfile_check) */


/* private subroutines */

static int postfile_fileheader(op)
POSTFILE	*op ;
{
	uint		*table ;
	int		rs = SR_OK ;
	int		i ;
	int		f ;
	char		*cp ;

	cp = (char *) op->mapbuf ;
	f = (strncmp(cp,POSTFILE_FILEMAGIC,POSTFILE_FILEMAGICLEN) == 0) ;
	f = f && (*(cp + POSTFILE_FILEMAGICLEN) == '\n') ;

	if (! f) {
	    rs = SR_BADFMT ;
	    goto bad3 ;
	}

	cp += 16 ;
	if (cp[0] > POSTFILE_FILEVERSION) {
	    rs = SR_NOTSUP ;
	    goto bad3 ;
	}

	if (cp[1] != ENDIAN) {
	    rs = SR_NOTSUP ;
	    goto bad3 ;
	}

/* the recorder options */

	op->ropts = cp[2] ;

/* if looks good, read the header stuff */

	table = (uint *) (op->mapbuf + 16 + 4) ;
	op->rectab = (POSTFILE_ENT *) (op->mapbuf + table[header_rectab]) ;
	op->rtlen = table[header_rectablen] ;

	op->stab = (cchar *) (op->mapbuf + table[header_strtab]) ;
	op->stlen = table[header_strtabsize] ;

	op->recind[0] = (uint (*)[2]) (op->mapbuf + table[header_indexl1]) ;
	op->recind[1] = (uint (*)[2]) (op->mapbuf + table[header_indexl3]) ;
	op->recind[3] = (uint (*)[2]) (op->mapbuf + table[header_indexf]) ;

	op->rilen = table[header_indexlen] ;

ret0:
	return rs ;

/* bad stuff comes here */
bad3:
	return rs ;
}
/* end subroutine (ipsswd_fileheader) */


/* acquire access to the file (mapped memory) */
static int postfile_holdget(op,daytime)
POSTFILE	*op ;
time_t		daytime ;
{
	USTAT		sb ;
	int	rs = SR_OK ;
	int	mpages, fpages ;
	int	prot, flags ;
	int	f_changed = false ;
	int	f_opened = false ;

	if ((daytime - op->accesstime) < TO_ACCESS)
	    return SR_OK ;

/* has the file changed at all (try checking size and mtime) ? */

	rs = u_stat(op->fname,&sb) ;

	if (rs == SR_NOENT)
	    return SR_OK ;

	if (rs < 0)
	    goto bad2 ;

	if (op->mapbuf != nullptr) {

/* has the file size changed ? */

	    if (sb.st_size != op->filesize) {

	        f_changed = true ;
	        mpages = ceiling(op->mapsize,op->pagesize) ;

	        fpages = ceiling(sb.st_size,op->pagesize) ;

	        if (fpages > mpages) {

	            f_changed = true ;
	            u_mmapend(op->mapbuf,(size_t) op->mapsize) ;

	            op->mapbuf = nullptr ;	/* signal a re-map */

	        }

	    } /* end if (file size changed) */

#if	CF_MEMSYNC
	    if ((op->mapbuf != nullptr) &&
	        op->f.remote && (sb.st_mtime != op->mtime)) {

	        f_changed = true ;
	        flags = MS_SYNC | MS_INVALIDATE ;
	        rs = uc_msync(op->mapbuf,op->mapsize,flags) ;

	    }
#endif /* CF_MEMSYNC */

	} /* end if (checking existing map) */

/* do a map or a re-map */

	if ((rs >= 0) && (op->mapbuf == nullptr)) {

	    f_changed = true ;
	    rs = postfile_fileopen(op,daytime) ;

	    if (rs >= 0) {

	        op->mapsize = ceiling(sb.st_size,op->pagesize) ;

	        if (op->mapsize == 0)
	            op->mapsize = op->pagesize ;

	        prot = PROT_READ ;
	        flags = MAP_SHARED ;
	        rs = u_mmap(((caddr_t) 0),(size_t) op->mapsize,prot,flags,
	            op->fd,0L,&op->mapbuf) ;

	        postfile_fileclose(op) ;

	    } /* end if (opened the file) */

	    if (rs < 0)
	        goto bad2 ;

	} /* end if (mapping file) */

	if (f_changed) {

	    op->filesize = sb.st_size ;
	    op->mtime = sb.st_mtime ;

	}

	if (rs >= 0)
	    op->f.held = true ;

	return (rs >= 0) ? f_changed : rs ;

/* bad stuff */
bad2:

bad1:
	op->f.held = false ;

bad0:
	return rs ;
}
/* end subroutine (postfile_holdget) */


/* release our hold on the filemap */
static int postfile_holdrelease(op,daytime)
POSTFILE	*op ;
time_t		daytime ;
{
	int	rs = SR_OK ;


	if (! op->f.held)
	    return SR_OK ;


	op->f.held = false ;

	return rs ;
}
/* end subroutine (postfile_holdrelease) */


#if	CF_LOCKING

/* acquire access to the file (mapped memory) */
static int postfile_lockget(op,daytime,f_read)
POSTFILE	*op ;
time_t		daytime ;
int		f_read ;
{
	USTAT	sb ;

	int	rs = SR_OK ;
	int	mpages, fpages ;
	int	prot, flags ;
	int	f_changed = false ;


	if (op->fd < 0)
	    rs = postfile_fileopen(op,daytime) ;

	if (rs < 0)
	    goto bad0 ;

	if (f_read) {
	    op->f.lockedread = true ;
	    rs = lockfile(op->fd,F_RLOCK,0L,op->filesize,TO_LOCK) ;
	} else {
	    op->f.lockedwrite = true ;
	    rs = lockfile(op->fd,F_WLOCK,0L,op->filesize,TO_LOCK) ;
	}

	if (rs < 0)
	    goto bad1 ;

/* has the size of the file changed ? */

	rs = u_fstat(op->fd,&sb) ;

	if (rs < 0)
	    goto bad2 ;

	op->filesize = sb.st_size ;
	if (op->mapbuf != nullptr) {

	    mpages = ceiling(op->mapsize,op->pagesize) ;

	    fpages = ceiling(op->filesize,op->pagesize) ;

	    if (fpages > mpages) {

	        f_changed = true ;
	        u_mmapend(op->mapbuf,(size_t) op->mapsize) ;

	        op->mapbuf = nullptr ;

	    }

#if	CF_MEMSYNC
	    if ((op->mapbuf != nullptr) &&
	        op->f.remote && (op->mtime != sb.st_mtime)) {

	        f_changed = true ;
	        op->mtime = sb.st_mtime ;
	        flags = MS_SYNC | MS_INVALIDATE ;
	        rs = uc_msync(op->mapbuf,op->mapsize,flags) ;

	    }
#endif /* CF_MEMSYNC */

	} /* end if (checking existing map) */

	if ((rs >= 0) && (op->mapbuf == nullptr)) {

	    f_changed = true ;
	    op->mapsize = ceiling(op->filesize,op->pagesize) ;

	    if (op->mapsize == 0)
	        op->mapsize = op->pagesize ;

	    prot = PROT_READ | PROT_WRITE ;
	    flags = MAP_SHARED ;
	    rs = u_mmap(((caddr_t) 0),(size_t) op->mapsize,prot,flags,
	        op->fd,0L,&op->mapbuf) ;

	    if (rs < 0)
	        goto bad2 ;

	    op->mtime = sb.st_mtime ;

	} /* end if (mapping file) */

	return (rs >= 0) ? f_changed : rs ;

/* bad stuff */
bad2:
	lockfile(op->fd,F_ULOCK,0L,op->filesize,TO_LOCK) ;

bad1:
	op->f.lockedread = false ;
	op->f.lockedwrite = false ;

bad0:
	return rs ;
}
/* end subroutine (postfile_lockget) */


static int postfile_lockrelease(op)
POSTFILE	*op ;
{
	int	rs = SR_OK ;


	if (! (op->f.lockedread || op->f.lockedwrite))
	    return SR_OK ;

	if (op->fd >= 0)
	    rs = lockfile(op->fd,F_ULOCK,0L,op->filesize,TO_LOCK) ;

	op->f.lockedread = false ;
	op->f.lockedwrite = false ;

	return rs ;
}
/* end subroutine (postfile_lockrelease) */

#endif /* CF_LOCKING */


static int postfile_fileopen(op,daytime)
POSTFILE	*op ;
time_t		daytime ;
{
	int	rs ;
	if (op->fd >= 0)
	    return op->fd ;

	rs = u_open(op->fname,op->oflags,op->operm) ;

	if (rs < 0)
	    goto bad0 ;

	op->fd = rs ;

	op->opentime = daytime ;
	return (rs >= 0) ? op->fd : rs ;

/* bad things */
bad0:
	return rs ;
}
/* end subroutine (postfile_fileopen) */


static int postfile_fileclose(op)
POSTFILE	*op ;
{
	int	rs = SR_OK ;


	if (op->fd >= 0) {

	    u_close(op->fd) ;

	    op->fd = -1 ;

	}

	return rs ;
}
/* end subroutine (postfile_fileclose) */


static int postfile_keymatchlast(op,opts,ri,sp,hl)
POSTFILE	*op ;
int		opts ;
int		ri ;
char		*sp ;
int		hl ;
{
	int		si = op->rectab[ri].last ;
	int	f ;
	if (opts & POSTFILE_FLASTFULL) {
	    f = (strncmp((op->stab + si),sp,3) == 0) ;
	} else {
	    f = (strncmp((op->stab + si),sp,hl) == 0) ;
	}
	return f ;
}
/* end subroutine (postfile_keymatchlast) */

static int postfile_keymatchall(op,opts,ri,np)
POSTFILE	*op ;
int		opts ;
int		ri ;
realname	*np ;
{
	int	si ;

	cchar	*s = op->stab ;
	cchar	*sp ;
/* last */
	if (opts & POSTFILE_FLASTFULL) {

	    si = op->rectab[ri].last ;
	    if (strcmp((s + si),np->last) != 0)
	        return false ;

	} else {

	    si = op->rectab[ri].last ;
	    if (strncmp((s + si),np->last,np->len.last) != 0)
	        return false ;

	}

/* first */

	si = op->rectab[ri].first ;
	sp = np->first ;
	if ((sp != nullptr) && (sp[0] != '\0')) {

	    si = op->rectab[ri].first ;
	    if (strncmp((s + si),sp,np->len.first) != 0)
	        return false ;

	}

/* middle-1 */

	si = op->rectab[ri].m1 ;
	sp = np->m1 ;
	if ((sp != nullptr) && (sp[0] != '\0')) {

	    si = op->rectab[ri].m1 ;
	    if (strncmp((s + si),sp,np->len.m1) != 0)
	        return false ;

	}

/* middle-2 */

	si = op->rectab[ri].m2 ;
	sp = np->m2 ;
	if ((sp != nullptr) && (sp[0] != '\0')) {

	    si = op->rectab[ri].m2 ;
	    if (strncmp((s + si),sp,np->len.m2) != 0)
	        return false ;

	}
	return true ;
}
/* end subroutine (postfile_keymatchall) */

static uint ceiling(uint v,uint a) noex {
	return (v + (a - 1)) & (~ (a - 1)) ;
}
/* end subroutine (ceiling) */


