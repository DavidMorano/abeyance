/* malloclog SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* malloc debugging */
/* version %I% last-modified %G% */

#define	CF_SKIPACCESS	1		/* skip file access on each write */

/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:
	malloclog

	Descrption:
	This set of subroutines forms a debugging package that can
	be used in conjuction with some sort of MALLOC package (like
	|malloc(3c)|).

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdarg>
#include	<cstring>
#include	<usystem.h>
#include	<hdb.h>
#include	<bfile.h>
#include	<fmtstr.h>
#include	<localmisc.h>


/* local defines */

#define	MALLOCLOG_FILE		"malloc.log"
#define	MALLOCLOG_BUFLEN	300
#define	MALLOCLOG_TSIZE		5000


/* external subroutines */


/* external variables */


/* local structures */

struct arec {
	ulong	addr ;
	uint	serial ;
	int	size ;
	int	count ;
} ;


/* forward references */

static int malloclog_access(cchar *,int) noex ;


/* local non-automatic variables */

static hdb	track ;

static int	rs_file = -1 ;
static int	f_init = FALSE ;
static int	f_file = FALSE ;

static uint	mark = 0 ;
static uint	serial = 0 ;


/* exported variables */


/* exported subroutines */

void malloclog_alloc(void *a,int size,cchar *s) noex {
	hdb_dat		key ;
	hdb_dat		value ;
	arec		*arp ;
	int	rs ;
	char	*addr = (char *) a ;

	if (a == 0)
	    return ;

#if	CF_TRACK

/* check startup */

	if (! f_init) {

	    hdb_start(&track,MALLOCLOG_TSIZE,0,NULL,NULL) ;

	    f_init = TRUE ;

	}

	if (size < 0)
	    size = strlen(addr) + 1 ;

	serial += 1 ;

/* store it for local tracking */

	key.buf = &a ;
	key.len = sizeof(ulong) ;

	rs = hdb_fetch(&track,key,NULL,&value) ;

	if (rs >= 0) {

	    arp = (struct arec *) value.buf ;
	    arp->count += 1 ;

	    if (arp->addr != a) {

	        if (malloclog_access(MALLOCLOG_FILE,W_OK) >= 0)
	            nprintf(MALLOCLOG_FILE,
			"%08x A %08lx %s %d bad addr=%08lx (%d)\n",
	                serial,a,s,size,arp->addr,arp->count) ;

	    }

	} else {

	    rs = uc_malloc(sizeof(struct arec),&arp) ;

	    arp->serial = serial ;
	    arp->addr = a ;
	    arp->size = size ;
	    arp->count = 1 ;

	    key.buf = &arp->addr ;
	    key.len = sizeof(ulong) ;

	    value.buf = arp ;
	    value.len = sizeof(struct arec) ;

	    rs = hdb_store(&track,key,value) ;

	}

#endif /* CF_TRACK */

/* print it for fun */

	if (malloclog_access(MALLOCLOG_FILE,W_OK) >= 0)
	    nprintf(MALLOCLOG_FILE,"%08x A %08lx %s %d\n",
	        serial,a,s,size) ;

}
/* end subroutine (malloclog_alloc) */

void malloclog_free(void *a,cchar *s) noex {
	hdb_dat	key, value ;
	arec		*arp ;
	ulong		addr = 0 ;
	uint		sn = 0 ;
	uint		count = 0 ;
	int	rs = 0 ;
	int	f_bad = FALSE ;

#if	CF_TRACK

/* check startup */

	if (! f_init) {
	    f_init = TRUE ;
	    hdb_start(&track,MALLOCLOG_TSIZE,0,NULL,NULL) ;
	}

	key.buf = &a ;
	key.len = szof(ulong) ;

	rs = hdb_fetch(&track,key,NULL,&value) ;

	if (rs >= 0) {

	    arp = (struct arec *) value.buf ;

	    arp->count -= 1 ;
	    count = arp->count ;
	    sn = arp->serial ;
	    addr = arp->addr ;
	    if (a != arp->addr) {
	        f_bad = TRUE ;
	    }

	    if (count == 0) {

	        rs = hdb_delkey(&track,key) ;

		if (rs >= 0) {
	        	free(arp) ;
		}

	    } else {
	        f_bad = TRUE ;
	    }

	}

#endif /* CF_TRACK */

/* print it for fun */

	if (rs >= 0) {

	if (f_bad) {

	    if (malloclog_access(MALLOCLOG_FILE,W_OK) >= 0)
	        nprintf(MALLOCLOG_FILE,"%08x F %08lx %s (%d) %08lx\n",
	            sn,a,count,s,addr) ;

	} else {

	    if (malloclog_access(MALLOCLOG_FILE,W_OK) >= 0)
	        nprintf(MALLOCLOG_FILE,"%08x F %08lx %s\n",
	            sn,a,s) ;

	}

	} else {

	    if (malloclog_access(MALLOCLOG_FILE,W_OK) >= 0)
	        nprintf(MALLOCLOG_FILE,
			"******** F %08lx %s (never allocated)\n",
	            a,s) ;

	}

}
/* end subroutine (malloclog_free) */

void malloclog_realloc(void *oa,void *a,int sz,char *s) noex {
	malloclog_free(oa,s) ;
	malloclog_alloc(a,sz,s) ;
}

int malloclog_mark() noex {
    	int		rs = SR_OK ;
	mark = serial ;
	return rs ;
}

int malloclog_dump() noex {
	hdb_dat		key ;
	hdb_dat		value ;
	hdb_cur		c ;
	arec		*arp ;
	int	rs ;


#if	CF_TRACK

	if (! f_init) {

	    f_init = TRUE ;
	    hdb_start(&track,10,0,NULL,NULL) ;

	}

	hdb_curbegin(&track,&c) ;

	while ((rs = hdb_curenum(&track,&c,&key,&value)) >= 0) {

	    if (value.buf == NULL) continue ;

	    arp = (struct arec *) value.buf ;

	    if (arp->serial >= mark) {

	        if (malloclog_access(MALLOCLOG_FILE,W_OK) >= 0)
	            nprintf(MALLOCLOG_FILE,"%08x D %08lx %d (%d)\n",
	                arp->serial,arp->addr,arp->size,arp->count) ;

	    }

	}

	hdb_curend(&track,&c) ;

#endif /* CF_TRACK */

}
/* end subroutine (malloclog_dump) */

int malloclog_printf(cchar *fmt,...) noex {
	va_list	ap ;
	int	len, rs ;
	char	buf[MALLOCLOG_BUFLEN + 1] ;

	if (u_access(MALLOCLOG_FILE,W_OK) < 0)
	    return SR_NOTOPEN ;

	va_begin(ap,fmt) ;
	len = format(buf,MALLOCLOG_BUFLEN,1,fmt,ap) ;
	va_end(ap) ;

	if (len > 0)
	rs = nprintf(MALLOCLOG_FILE,"******** P $w\n",buf,len) ;

	return rs ;
}
/* end subroutine (malloclog_printf) */


/* local subroutines */

static int malloclog_access(char *fname,int perm) noex {
	if (! f_file) {
		f_file = TRUE ;
	        rs_file = u_access(fname,perm) ;
	}
	return rs_file ;
}
/* end subroutine (malloclog_access) */


