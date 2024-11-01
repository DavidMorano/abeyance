/* objfile SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

/* map an ELF object file into memory for examination */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-07-26, David A­D­ Morano
	I am writing this from stratch after trying to make the
	best use of the related code in the MINT simulator and
	becoming disgusted with the failure of the attempt!  MINT
	is changing the code that it reads in and also does not
	read every type of object file either!  Worse, MINT inserts
	into the code some stuff for its own purposes that currently
	escapes understanding.

	= 2005-03-28, David A­D­ Morano
	This code has been hacked up to just provide examination
	of the object file.

*/

/* Copyright © 2000,2005 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Object:
	objfile

	Description:
	This module is used to map an object file into memory for
	purposes of examining it for symbol content.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/mman.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<ctime>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstring>
#include	<elf.h>
#include	<usystem.h>
#include	<vecobj.h>
#include	<hdb.h>
#include	<hash.h>		/*|hash_elf(3uc) */
#include	<intceil.h>
#include	<localmisc.h>

#include	"objfile.h"		/* ourselves */


/* local defines */

#define	OF		objfile

#define	NSYMBOLS	200


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

static int	objfile_hash(OF *,Elf32_Ehdr *) noex ;
static int	objfile_dynsym(OF *,Elf32_Ehdr *) noex ;

static int	objfile_symtabsinit(OF *,Elf32_Ehdr *) noex ;
static int	objfile_symtabsfree(OF *) noex ;

static int	objfile_symtabmap(OF *,int) noex ;
static int	objfile_symtabunmap(OF *,int) noex ;

static int	objfile_symbolsinit(OF *) noex ;
static int	objfile_symbolsfree(OF *) noex ;

static int	checkelf(Elf32_Ehdr *) noex ;
static int	finds(Elf32_Shdr *,int,cc *,cc *,int) noex ;
static int	findhs(Elf32_Shdr *,int,cc *,cc *,int) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int objfile_open(OF *op,cchar *fname) noex {
	Elf32_Ehdr	ehead ;
	off_t		uoff ;
	uint		size ;
	uint		mapalign ;
	cint		pagesize = getpagesize() ;
	int		rs, rs1 ;
	int		i ;
	int		len ;
	cchar		*cp ;
	char		*shstrs = nullptr ; 	/* section header strings */

	if (op == nullptr) return SR_FAULT ;

	memclear(op) ;

	op->f.symtab = FALSE ;
	op->f.symbols = FALSE ;
/* try to open the ELF file */
	rs = u_open(fname,O_RDONLY,0666) ;
	op->ofd = rs ;
	if (rs < 0)
	    goto bad0 ;

	op->lastaccess = time(nullptr) ;

/* the file MUST be seekable! */

	rs = u_seek(op->ofd,0L,SEEK_CUR) ;
	if (rs < 0)
	    goto bad1 ;

/* read the ELF header */

	rs = u_read(op->ofd,&ehead,sizeof(Elf32_Ehdr)) ;
	if (rs < 0)
	    goto bad1 ;

/* check if it is an ELF file */

	rs = checkelf(&ehead) ;
	if (rs < 0) {
	    goto bad1 ;
	}

/* read some stuff that we want out of the ELF header */

	op->progentry = ehead.e_ent ;	/* program entry address */
	mapalign = pagesize ;
	op->mapalign = mapalign ;

/* allocate space for the section header table */

	op->nsheads = ehead.e_shnum ;

	size = ehead.e_shnum * ehead.e_shentsize ;
	rs = uc_malloc(size,&op->sheads) ;
	if (rs < 0)
	    goto bad1 ;

	uoff = ehead.e_shoff ;
	u_seek(op->ofd,uoff,SEEK_SET) ;

	rs = u_read(op->ofd,op->sheads,size) ;
	len = rs ;
	if ((rs >= 0) && (len < size)) {
	    rs = SR_EOF ;
	    goto bad2 ;
	}

/* do we even have a section string table? */

	if (ehead.e_shstrndx != SHN_UNDEF) {
	    /* verify we have a section string table here! */
	    i = ehead.e_shstrndx ;
	    if (op->sheads[i].sh_type != SHT_STRTAB)
	        goto bad2 ;

	    size = op->sheads[i].sh_size ;
	    rs = uc_malloc(size,&shstrs) ;
	    if (rs < 0)
	        goto bad2 ;

/* read in the section string table */

	    uoff = op->sheads[i].sh_offset ;
	    u_seek(op->ofd,uoff,SEEK_SET) ;

	    rs = u_read(op->ofd,shstrs,size) ;
	    len = rs ;
	    if ((rs >= 0) && (len < size)) {
		rs = SR_EOF ;
	        goto bad3 ;
	    }

	} /* end if (section string table) */

/* initialize the symbol table container */

	size = sizeof(OBJFILE_SYMTAB) ;
	rs = vecobj_start(&op->symtabs,size,100,VECOBJ_OCOMPACT) ;
	if (rs < 0)
	    goto bad3 ;

	op->f.symtab = TRUE ;

/* do we have a dynamic hash section? */

	rs1 = objfile_hash(op,&ehead) ;
	if (rs1 < 0) {
	    rs1 = objfile_dynsym(op,&ehead) ;
	}

/* OK, now we want to map any symbol tables and their string tables! */

	if (rs1 < 0) {

	    rs = objfile_symtabsinit(op,&ehead) ;
	    if (rs < 0)
	        goto bad3a ;

	}

/* store the fname now that we are pretty sure we are OK */

	rs = uc_mallocstrw(fname,-1,&cp) ;
	op->fname = cp ;
	if (rs < 0) goto bad4 ;

/* we're almost done! , set this so we can use ourselves! */

	if (rs >= 0)
	    op->magic = OBJFILE_MAGIC ;

/* free up section strings */

	if (shstrs != nullptr) {
	    uc_free(shstrs) ;
	    shstrs = nullptr ;
	}

	u_close(op->ofd) ;
	op->ofd = -1 ;			/* mark as closed */

/* let's index the symbols if we have any (by name) */

	if ((rs >= 0) && op->f.symtab) {
	    hdb_dat		key, value ;
	    OBJFILE_SYMTAB	*stp ;
#ifdef	COMMENT
	    objfile_sym	*sep ;
#endif
	    Elf32_Sym	*eep ;
	    int		j ;

	    rs = hdb_start(&op->symbols,0,NSYMBOLS,nullptr,nullptr) ;
	    if (rs < 0)
	        goto bad9 ;

	    for (i = 0 ; vecobj_get(&op->symtabs,i,&stp) >= 0 ; i += 1) {
	        if (stp == nullptr) continue ;

	        for (j = 0 ; j < stp->nsyms ; j += 1) {

	            eep = stp->symtab + j ;
	            if (eep->st_name == 0) continue ;

	            key.buf = (stp->strings + eep->st_name) ;
	            key.len = -1 ;

#ifdef	COMMENT
	            rs = uc_malloc(sizeof(objfile_sym),&sep) ;
	            if (rs < 0)
	                break ;

	            sep->ep = eep ;
	            sep->name = (char *) (stp->strings + eep->st_name) ;

	            value.buf = sep ;
	            value.len = sizeof(objfile_sym) ;
#else
	            value.buf = eep ;
	            value.len = sizeof(Elf32_Sym) ;
#endif /* COMMENT */

	            rs = hdb_store(&op->symbols,key,value) ;
	            if (rs < 0) {

#ifdef	COMMENT
	                uc_free(sep) ;
#endif

	                break ;
	            }

	        } /* end for */

	        if (rs < 0) break ;
	    } /* end for (looping over symbol tables) */

	    if (rs < 0) {
	        objfile_symbolsfree(op) ;
	        goto bad9 ;
	    }

	    op->f.symbols = TRUE ;

	} /* end if (indexing symbols by name) */
/* clean up some stuff before exiting */
ret0:
	return rs ;

/* bad things come here */
bad9:
bad8:
bad7:
bad6:
bad5:
	if (op->fname != nullptr) {
	    uc_free(op->fname) ;
	    op->fname = nullptr ;
	}

bad4:
	if (op->f.symtab) {
	    OBJFILE_SYMTAB	*stp ;

	    for (i = 0 ; vecobj_get(&op->symtabs,i,&stp) >= 0 ; i += 1) {
	        if (stp == nullptr) continue ;

	        if (stp->pa_symtab != nullptr)
	            u_munmap(stp->pa_symtab,stp->maplen_symtab) ;

	        if (stp->pa_strings != nullptr)
	            u_munmap(stp->pa_strings,stp->maplen_strings) ;

	    } /* end for */

	} /* end if */

bad3a:
	if (op->f.symtab) {
	    op->f.symtab = FALSE ;
	    vecobj_finish(&op->symtabs) ;
	}

bad3:
	if (shstrs != nullptr)
	    uc_free(shstrs) ;

bad2:
	if (op->sheads != nullptr)
	    uc_free(op->sheads) ;

bad1:
	u_close(op->ofd) ;

bad0:
	goto ret0 ;
}
/* end subroutine (objfile_open) */

int objfile_getentry(OF *op,uint *ap) noex {
	if (op == nullptr) return SR_FAULT ;

#if	CF_SAFE
	if ((op->magic != OBJFILE_MAGIC) && (op->magic != 0))
	    return SR_BADFMT ;

	if (op->magic != OBJFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif

	*ap = op->progentry ;

	return SR_OK ;
}
/* end subroutine (objfile_getentry) */

int objfile_getpagesize(OF *op,uint *ap) noex {
	if (op == nullptr) return SR_FAULT ;

#if	CF_SAFE
	if ((op->magic != OBJFILE_MAGIC) && (op->magic != 0))
	    return SR_BADFMT ;

	if (op->magic != OBJFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif

	*ap = op->pagealign ;
	return SR_OK ;
}
/* end subroutine (objfile_getpagesize) */

/* get a symbol table entry */
/***
	Note that this subroutine is not very useful when there are
	more than one symbol by the same name!  This subroutine
	will only return the first of what could be many possible
	symbols having the same name.
***/

int objfile_getsym(OF *op,cchar *name,Elf32_Sym **sepp) noex {
	hdb_cur		cur ;
	hdb_dat	key, value ;
	Elf32_Sym	*sep ;
	int		rs = SR_OK ;
	int		f ;

	if (name == nullptr) return SR_FAULT ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if ((op->magic != OBJFILE_MAGIC) && (op->magic != 0))
	    return SR_BADFMT ;

	if (op->magic != OBJFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif

	if (sepp != nullptr)
	    *sepp = nullptr ;

	if (! op->f.symbols)
	    return SR_NOTFOUND ;

	if (name[0] == '\0')
	    return SR_INVALID ;

	key.buf = (char *) name ;
	key.len = -1 ;

/* look for STRONG symbols */

	if ((rs = hdb_curbegin(&op->symbols,&cur)) >= 0) {

	while (rs >= 0) {

	    rs = hdb_fetch(&op->symbols,key,&cur,&value) ;

	    if (rs >= 0) {
	        sep = (Elf32_Sym *) value.buf ;
	        f = (ELF32_ST_BIND(sep->st_info) == STB_GLOBAL) ;
		f = f && 
	            ((ELF32_ST_TYPE(sep->st_info) == STT_FUNC) ||
	            (ELF32_ST_TYPE(sep->st_info) == STT_OBJECT)) ;
		if (f) break ;
	    }

	} /* end while */

	hdb_curend(&op->symbols,&cur) ;
	} /* end if (cursor) */

/* look for WEAK symbols */

	if (rs == SR_NOTFOUND) {

	    if ((rs = hdb_curbegin(&op->symbols,&cur)) >= 0) {

	    while (rs >= 0) {

	        rs = hdb_fetch(&op->symbols,key,&cur,&value) ;

		if (rs >= 0) {
	            sep = (Elf32_Sym *) value.buf ;
	            f = (ELF32_ST_BIND(sep->st_info) == STB_WEAK) ;
		    f = f &&
	                ((ELF32_ST_TYPE(sep->st_info) == STT_FUNC) ||
	                (ELF32_ST_TYPE(sep->st_info) == STT_OBJECT)) ;
		    if (f) break ;
		}

	    } /* end while */

	    hdb_curend(&op->symbols,&cur) ;
	    } /* end if (cursor) */

	} /* end if (second chance) */

	if (rs >= 0) {
	    if (sepp) {
	        *sepp = sep ;
	    }
	}

	return rs ;
}
/* end subroutine (objfile_getsym) */


/* initialize a cursor for fetching symbols by name */
int objfile_sncurbegin(OF *op,OBJFILE_SNCUR *cp)
{
	int		rs ;

	if (op == nullptr) return SR_FAULT ;
	if (cp == nullptr) return SR_FAULT ;

#if	CF_SAFE
	if ((op->magic != OBJFILE_MAGIC) && (op->magic != 0)) {
	    return SR_BADFMT ;
	}

	if (op->magic != OBJFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif /* CF_SAFE */

	if (! op->f.symbols)
	    return SR_NOTAVAIL ;

	rs = hdb_curbegin(&op->symbols,cp) ;

	return rs ;
}
/* end subroutine (objfile_sncurbegin) */


int objfile_sncurend(OF *op,OBJFILE_SNCUR *cp)
{
	int		rs ;

	if (op == nullptr) return SR_FAULT ;
	if (cp == nullptr) return SR_FAULT ;

#if	CF_SAFE
	if ((op->magic != OBJFILE_MAGIC) && (op->magic != 0)) {

	    return SR_BADFMT ;
	}

	if (op->magic != OBJFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif /* CF_SAFE */

	rs = hdb_curend(&op->symbols,cp) ;

	return rs ;
}
/* end subroutine (objfile_sncurend) */


/* fetch a symbol table entry */
int objfile_fetchsym(OF *op,cchar name[],OBJFILE_SNCUR *cp,
		Elf32_Sym **sepp)
{
	hdb_dat	key, value ;
	Elf32_Sym	*sep ;
	int		rs ;

	if (name == nullptr) return SR_FAULT ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if ((op->magic != OBJFILE_MAGIC) && (op->magic != 0))
	    return SR_BADFMT ;

	if (op->magic != OBJFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif

	if (sepp != nullptr) *sepp = nullptr ;

	if (! op->f.symbols) return SR_NOTAVAIL ;

	if (name[0] == '\0') return SR_INVALID ;

	key.buf = (char *) name ;
	key.len = -1 ;

	if ((rs = hdb_fetch(&op->symbols,key,cp,&value)) >= 0) {
	    sep = (Elf32_Sym *) value.buf ;
	    if (sepp != nullptr) *sepp = sep ;
	}

	return rs ;
}
/* end subroutine (objfile_fetchsym) */


/* enumerate the symbols */
int objfile_enumsym(OF *op,OBJFILE_SNCUR *cp,cchar **namepp,
		Elf32_Sym **sepp)
{
	hdb_dat	key, value ;
	Elf32_Sym	*sep ;
	int		rs ;

#if	CF_SAFE
	if (op == nullptr)
	    return SR_FAULT ;

	if ((op->magic != OBJFILE_MAGIC) && (op->magic != 0))
	    return SR_BADFMT ;

	if (op->magic != OBJFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif

	if (sepp != nullptr)
	    *sepp = nullptr ;

	if (! op->f.symbols)
	    return SR_NOTAVAIL ;

	rs = hdb_curenum(&op->symbols,cp,&key,&value) ;
	if (rs < 0)
	    goto ret0 ;

	if (namepp != nullptr)
	    *namepp = key.buf ;

	sep = (Elf32_Sym *) value.buf ;
	if (sepp) {
	    *sepp = sep ;
	}

ret0:
	return rs ;
}
/* end subroutine (objfile_enumsym) */

int objfile_getsec(OF *op,int i,Elf32_Shdr **shpp) noex {
	int		rs = SR_OK ;

	if (op == nullptr) return SR_FAULT ;

#if	CF_SAFE
	if ((op->magic != OBJFILE_MAGIC) && (op->magic != 0)) {
	    return SR_BADFMT ;
	}

	if (op->magic != OBJFILE_MAGIC)
	    return SR_NOTOPEN ;
#endif /* CF_SAFE */

	if (shpp == nullptr) return SR_FAULT ;

	if (i < 0) return SR_INVALID ;

	if (i >= op->nsheads) return SR_NOTFOUND ;

	*shpp = (op->sheads + i) ;

	return rs ;
}
/* end subroutine (objfile_getsec) */


/* free up this whole program mapping! */
int objfile_close(OF *op)
{
	int		i ;

	if (op == nullptr) return SR_FAULT ;

#if	CF_SAFE
	if ((op->magic != OBJFILE_MAGIC) && (op->magic != 0))
	    return SR_BADFMT ;
#endif

	if (op->magic != OBJFILE_MAGIC)
	    return SR_NOTOPEN ;

/* free up the indexed symbols (if any) */

	if (op->f.symbols)
	    objfile_symbolsfree(op) ;

/* free up any symbol tables (and their string tables) */

	if (op->f.symtab) {
	    OBJFILE_SYMTAB	*stp ;

	    for (i = 0 ; vecobj_get(&op->symtabs,i,&stp) >= 0 ; i += 1) {
	        if (stp == nullptr) continue ;

	        if (stp->pa_symtab != nullptr)
	            u_munmap(stp->pa_symtab,stp->maplen_symtab) ;

	        if (stp->pa_strings != nullptr)
	            u_munmap(stp->pa_strings,stp->maplen_strings) ;

	    } /* end for */

	    vecobj_finish(&op->symtabs) ;
	    op->f.symtab = FALSE ;

	} /* end if (freeing up the symbol tables) */
	/* close any open files */
	if (op->ofd >= 0) {
	    u_close(op->ofd) ;
	}
	/* free up the data structures that were allocated */
	if (op->fname != nullptr) {
	    uc_free(op->fname) ;
	}
	/* free up sections headers */
	if (op->sheads != nullptr) {
	    uc_free(op->sheads) ;
	}

	op->magic = 0 ;
	return SR_OK ;
}
/* end subroutine (objfile_close) */


/* private subroutines */

static int objfile_hash(OF *op,Elf32_Ehdr *ehp) noex {
	int		rs = SR_NOENT ;
	int		i ; /* used-afterwards */
	for (i = 0 ; i < ehp->e_shnum ; i += 1) {
	    if (op->sheads[i].sh_type == SHT_HASH) break ;
	} /* end for */
	if (i < ehp->e_shnum) {
	    /* we have a hash section */
	    op->f.hash = (rs >= 0) ;
	} /* end if (dynamic symbols) */
	return (rs >= 0) ? op->f.hash : rs ;
}
/* end subroutine (objfile_hash) */

static int objfile_dynsym(OF *op,Elf32_Ehdr *ehp) noex {
	int		rs = SR_NOENT ;
	int		i ; /* used-afterwards */
	for (i = 0 ; i < ehp->e_shnum ; i += 1) {
	    if (op->sheads[i].sh_type == SHT_DYNSYM) break ;
	} /* end for */
	if (i < ehp->e_shnum) {
	    rs = objfile_symtabmap(op,i) ;
	    op->f.dynsym = (rs >= 0) ;
	}
	return (rs >= 0) ? op->f.dynsym : rs ;
}
/* end subroutine (objfile_dynsym) */

/* map the symbol tables along with their string tables */
static int objfile_symtabsinit(OF *op,Elf32_Ehdr *ehp) noex {
	OBJFILE_SYMTAB	st ;
	Elf32_Shdr	*sheads = op->sheads ;
	int		rs = SR_NOENT ;
	/* loop searching for symbol tables and mapping them! */
	for (int i = 0 ; i < ehp->e_shnum ; i += 1) {

	    if (sheads[i].sh_type == SHT_SYMTAB) {

	        rs = objfile_symtabmap(op,i) ;
	        if (rs < 0) break ;
		/* save this symbol table */
	        rs = vecobj_add(&op->symtabs,&st) ;
	        if (rs < 0) {
	            if (st.pa_symtab != nullptr) {
	                u_munmap(st.pa_symtab,st.maplen_symtab) ;
		    }
	            if (st.pa_strings != nullptr) {
	                u_munmap(st.pa_strings,st.maplen_strings) ;
		    }
	            break ;
	        }

	    } /* end if (got a symbol table) */

	} /* end for (searching for symbol tables) */

	if (rs < 0)
	    goto bad4 ;

ret0:
	return rs ;

/* bad things come here */
bad4:
	if (op->f.symtab) {
	    OBJFILE_SYMTAB	*stp ;

	    for (i = 0 ; vecobj_get(&op->symtabs,i,&stp) >= 0 ; i += 1) {
	        if (stp == nullptr) continue ;

	        if (stp->type == SHT_SYMTAB) {

	            if (stp->pa_symtab != nullptr)
	                u_munmap(stp->pa_symtab,stp->maplen_symtab) ;

	            if (stp->pa_strings != nullptr)
	                u_munmap(stp->pa_strings,stp->maplen_strings) ;

	        }

	    } /* end for */

	    vecobj_finish(&op->symtabs) ;
	    op->f.symtab = FALSE ;

	} /* end if */

bad3:
	goto ret0 ;
}
/* end subroutine (objfile_symtabsinit) */


/* free up the symbol tables */
static int objfile_symtabsfree(OF *op)
{
	OBJFILE_SYMTAB	*stp ;
	int		rs = SR_OK ;
	int		i ;

	for (i = 0 ; vecobj_get(&op->symtabs,i,&stp) >= 0 ; i += 1) {
	    if (stp == nullptr) continue ;

	    if (stp->pa_symtab != nullptr)
	        u_munmap(stp->pa_symtab,stp->maplen_symtab) ;

	    if (stp->pa_strings != nullptr)
	        u_munmap(stp->pa_strings,stp->maplen_strings) ;

	} /* end for */

	return rs ;
}
/* end subroutine (objfile_symtabsfree) */


static int objfile_symtabmap(op,n)
OBJFILE		*op ;
int		n ;
{
	OBJFILE_SYMTAB	st ;
	Elf32_Shdr	*sheads = op->sheads ;
	off_t	fbase ;
	ulong		fextent ;
	ulong		leadgap ;
	ulong		mapalign = op->mapalign ;
	uint		fmsize ;
	int		rs = SR_OK ;
	int		j ;
	int		flags, prot ;

	if ((sheads[n].sh_type != SHT_SYMTAB) &&
	    (sheads[n].sh_type != SHT_DYNSYM))
	    return SR_INVALID ;

	st.type = sheads[n].sh_type ;

	st.nsyms = sheads[n].sh_size / sheads[n].sh_entsize ;

	fbase = sheads[n].sh_offset & (~ (mapalign - 1)) ;
	fextent = sheads[n].sh_offset + sheads[n].sh_size ;
	fmsize = uceil(fextent,mapalign) - fbase ;

	leadgap = sheads[n].sh_offset - fbase ;
	st.maplen_symtab = (uint) fmsize ;
	st.entsize = sheads[n].sh_entsize ;

	flags = MAP_SHARED ;
	prot = PROT_READ ;
	rs = u_mmap(nullptr,(size_t) fmsize,prot,flags,
	    op->ofd,fbase,&st.pa_symtab) ;

	st.pa_strings = nullptr ;
	st.symtab = (Elf32_Sym *) (st.pa_symtab + leadgap) ;
	st.strings = nullptr ;

	if ((rs >= 0) && (sheads[n].sh_link > 0)) {

	    j = (int) sheads[n].sh_link ;

/* map the string table */

	    fbase = sheads[j].sh_offset & (~ (mapalign - 1)) ;
	    fextent = sheads[j].sh_offset + sheads[j].sh_size ;
	    fmsize = uceil(fextent,mapalign) - fbase ;

	    leadgap = sheads[j].sh_offset - fbase ;
	    st.maplen_strings = (uint) fmsize ;
	    st.entsize = sheads[j].sh_entsize ;

	    flags = MAP_SHARED ;
	    prot = PROT_READ ;
	    rs = u_mmap(nullptr,(size_t) fmsize,prot,flags,
	        op->ofd,fbase,&st.pa_strings) ;

	    st.strings = (char *) (st.pa_strings + leadgap) ;

	    if (rs < 0) {
	        if (st.pa_symtab != nullptr) {
	            u_munmap(st.pa_symtab,st.maplen_symtab) ;
		}
	    }

	} /* end if (had strings) */

	if (rs >= 0) {
	    /* save this symbol table */
	    rs = vecobj_add(&op->symtabs,&st) ;
	    if (rs < 0) {
	        if (st.pa_symtab != nullptr) {
	            u_munmap(st.pa_symtab,st.maplen_symtab) ;
		}
	        if (st.pa_strings != nullptr) {
	            u_munmap(st.pa_strings,st.maplen_strings) ;
		}
	    }
	}
	return rs ;
}
/* end subroutine (objfile_symtabmap) */

static int objfile_symtabunmap(OF *op,int n) noex {
	OBJFILE_SYMTAB	*stp ;
	int		rs ;

	rs = vecobj_get(&op->symtabs,n,&stp) ;

	if ((rs >= 0) && (stp != nullptr)) {
	    if (stp->pa_symtab != nullptr) {
	        u_munmap(stp->pa_symtab,stp->maplen_symtab) ;
	    }
	    if (stp->pa_strings != nullptr) {
	        u_munmap(stp->pa_strings,stp->maplen_strings) ;
	    }
	    vecobj_del(&op->symtabs,n) ;
	} /* end if (got one) */

	return rs ;
}
/* end subroutine (objfile_symtabunmap) */

static int objfile_symbolsinit(OF *op) noex {
	hdb_dat	key, value ;
	OBJFILE_SYMTAB	*stp ;
#ifdef	COMMENT
	objfile_sym	*sep ;
#endif
	Elf32_Sym	*eep ;
	int		rs ;
	int		i, j ;
	int		c = 0 ;

	if (! op->f.symtab)
	    return SR_NOTAVAIL ;

	rs = hdb_start(&op->symbols,100,0,nullptr,nullptr) ;
	if (rs < 0)
	    goto bad9 ;

	for (i = 0 ; vecobj_get(&op->symtabs,i,&stp) >= 0 ; i += 1) {
	    if (stp == nullptr) continue ;

	    for (j = 0 ; j < stp->nsyms ; j += 1) {

	        eep = stp->symtab + j ;
	        if (eep->st_name == 0) continue ;

	        key.buf = (stp->strings + eep->st_name) ;
	        key.len = -1 ;

#ifdef	COMMENT
	        rs = uc_malloc(sizeof(objfile_sym),&sep) ;
	        if (rs < 0)
	            break ;

	        sep->ep = eep ;
	        sep->name = (char *) (stp->strings + eep->st_name) ;

	        value.buf = sep ;
	        value.len = sizeof(objfile_sym) ;
#else
	        value.buf = eep ;
	        value.len = sizeof(Elf32_Sym) ;
#endif /* COMMENT */

	        rs = hdb_store(&op->symbols,key,value) ;

	        if (rs < 0) {

#ifdef	COMMENT /* goes with the comment above */
	            uc_free(sep) ;
#endif

	            break ;
	        }

	        c += 1 ;

	    } /* end for */

	    if (rs < 0) break ;
	} /* end for (looping over symbol tables) */

	if (rs < 0) {
	    objfile_symbolsfree(op) ;
	    goto bad9 ;
	}

	op->f.symbols = TRUE ;

bad9:
	return (rs >= 0) ? c : rs ;
}
/* end subroutine (objfile_symbolsinit) */

static int objfile_symbolsfree(OF *op) noex {
	int		rs = SR_OK ;

	if (! op->f.symbols)
	    goto ret0 ;

#ifdef	COMMENT
	{
	hdb_cur		cur ;
	hdb_dat		key ;
	hdb_dat		value ;
	objfile_sym	*sep ;

	hdb_curbegin(&op->symbols,&cur) ;

	while (hdb_curenum(&op->symbols,&cur,&key,&value) >= 0) {
	    sep = (objfile_sym *) value.buf ;
	    if (sep != nullptr) {
		uc_free(sep) ;
	    }
	} /* end while */

	hdb_curend(&op->symbols,&cur) ;

	}
#endif /* COMMENT */

	hdb_finish(&op->symbols) ;
	op->f.symbols = FALSE ;

ret0:
	return rs ;
}
/* end subroutine (objfile_symbolsfree) */

static int checkelf(Elf32_Ehdr *ehp) noex {
	int		rs = SR_OK ;

	if ((ehp->e_ident[0] != 0x7f) ||
	    (strncmp((char *) (ehp->e_ident + 1),"ELF",3) != 0)) {

	    rs = SR_BADFMT ;
	    goto bad2 ;
	}
	/* check the file class (we can only handle 32 bit) */
	if (ehp->e_ident[EI_CLASS] != ELFCLASS32) {
	    rs = SR_NOTSUP ;
	    goto bad2 ;
	}
	/* check for a version of the ELF file that we understand */
	if ((ehp->e_ident[EI_VERSION] == 0) ||
	    (ehp->e_ident[EI_VERSION] > EV_CURRENT)) {

	    rs = SR_NOTSUP ;
	    goto bad2 ;
	}
	/* check the data encoding (we can only handle 32 bit Big-Endian) */
	if (ehp->e_ident[EI_DATA] != ELFDATA2MSB) {
	    rs = SR_NOTSUP ;
	    goto bad2 ;
	}
	/* check version in the header entry */

	if ((ehp->e_version == 0) || (ehp->e_version > EV_CURRENT)) {
	    rs = SR_NOTSUP ;
	    goto bad2 ;
	}

bad2:
	return rs ;
}
/* end subroutine (checkelf) */

static int finds(Elf32_shdr *sheads,int n,cc *shstrs,cc *name,int type) noex {
	for (int i = 0 ; i < n ; i += 1) {
	    cint	namei = sheads[i].sh_name ;
	    if (strcmp(shstrs + namei,name) == 0) {
	        if (type < 0) break ;
	        if (sheads[i].sh_type == type) break ;
	    }
	} /* end for */
	return ((i < n) ? i : -1) ;
}
/* end subroutine (finds) */

/* find a section by its name (and type if specified) */
static int findhs(Elf32_Shdr *sheads,int n,cc *shstrs,cc *name,int type) noex {
	uint		maxaddr = 0 ;
	int		si = -1 ;
	int		namei ;
	for (int i = 0 ; i < n ; i += 1) {

	    if ((name != nullptr) && (shstrs != nullptr)) {
	        namei = sheads[i].sh_name ;
	        if (strcmp(shstrs + namei,name) != 0) continue ;
	    }

	    if (type < 0)
	        continue ;

	    if ((sheads[i].sh_type == type) && (sheads[i].sh_addr > maxaddr)) {
	        si = i ;
	        maxaddr = sheads[i].sh_addr ;
	    } /* end if (it was higher!) */

	} /* end for */

	return si ;
}
/* end subroutine (findhs) */


