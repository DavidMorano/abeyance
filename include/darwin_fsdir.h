/* fsdir HEADER (Darwin) */
/* lang=C20 */

/* UNIX® file system dirextory operations */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Traverse a directory and read out the entries.

	Implementation-note:
	I employ a sub-object (named |posixdirent|) to actually
	implement the whole "fsdir" functionality.

*******************************************************************************/

#ifndef	FSDIR_INCLUDE
#define	FSDIR_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<limits.h>
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<localmisc.h>


#define	FSDIR_MAGIC	0x31415926
#define	FSDIR		struct fsdir_head
#define	FSDIR_ENT	struct fsdir_entry
#define	FSDIR_FL	struct fsdir_flags


struct fsdir_entry {
	ino_t		ino ;		/* UNIX® "inode number" of entry */
	char		*name ;		/* name of file */
	ushort		nlen ;		/* length of this record */
	ushort		type ;		/* some systems support this */
} ;

struct fsdir_flags {
	uint		descname:1 ;	/* name was really a descriptor */
} ;

struct fsdir_head {
	void		*posixp ;	/* pointer to POSIX® adapater */
	FSDIR_FL	f ;
	uint		magic ;
	int		dfd ;		/* directory file-descriptor */
} ;

typedef	FSDIR_FL	fsdir_fl ;
typedef	FSDIR_ENT	fsdir_ent ;

#ifdef	__cplusplus
enum fsdirmems {
	fsdirmem_rewind,
	fsdirmem_audit,
	fsdirmem_close,
	fsdirmem_overlast
} ;
struct fsdir ;
struct fsdir_opener {
	fsdir		*op = nullptr ;
	cchar		*name = nullptr ;
	void operator () (fsdir *p,cchar *n) noex {
	    op = p ;
	    name = n ;
	} ;
	operator int () noex ;
	int operator () (cchar * = nullptr) noex ;
} ; /* end struct (fsdir_opener) */
struct fsdir_co {
	fsdir		*op = nullptr ;
	int		w = -1 ;
	void operator () (fsdir *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (fsdir_co) */
struct fsdir : fsdir_head {
	typedef fsdir_entry	ent ;
	fsdir_opener	open ;
	fsdir_co	rewind ;
	fsdir_co	audit ;
	fsdir_co	close ;
	fsdir(cchar *n = nullptr) noex {
	    open(this,n) ;
	    rewind(this,fsdirmem_rewind) ;
	    audit(this,fsdirmem_audit) ;
	    close(this,fsdirmem_close) ;
	} ; /* end ctor */
	fsdir(const fsdir &) = delete ;
	fsdir &operator = (const fsdir &) = delete ;
	int read(ent *,char *,int) noex ;
	int tell(off_t * = nullptr) noex ;
	int seek(off_t = 0) noex ;
	~fsdir() noex {
	    (void) int(close) ;
	} ;
} ; /* end struct (fsdir) */
#else	/* __cplusplus */
typedef struct fsdir_head	fsdir ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	fsdir_open(fsdir *,cchar *) noex ;
extern int	fsdir_read(fsdir *,fsdir_ent *,char *,int) noex ;
extern int	fsdir_tell(fsdir *,off_t *) noex ;
extern int	fsdir_seek(fsdir *,off_t) noex ;
extern int	fsdir_rewind(fsdir *) noex ;
extern int	fsdir_audit(fsdir *) noex ;
extern int	fsdir_close(fsdir *) noex ;

EXTERNC_end


#endif /* FSDIR_INCLUDE */


