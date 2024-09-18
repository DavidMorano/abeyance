/* fsdirtree HEADER */
/* lang=C++20 */

/* traverse directory tree */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FSDIRTREE_INCLUDE
#define	FSDIRTREE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>
#include	<fsdir.h>
#include	<fifostr.h>
#include	<hdb.h>


#define	FSDIRTREE		struct fsdirtree_head
#define	FSDIRTREE_FL		struct fsdirtree_flags
#define	FSDIRTREE_STAT		USTAT
#define	FSDIRTREE_MAGIC		0x98653217

/* options */
#define	FSDIRTREE_MFOLLOW	(1<<0)	/* follow symbolic links */
#define	FSDIRTREE_MLINK		(1<<1)
#define	FSDIRTREE_MREG		(1<<2)
#define	FSDIRTREE_MBLOCK	(1<<3)
#define	FSDIRTREE_MCHAR		(1<<4)
#define	FSDIRTREE_MPIPE		(1<<5)
#define	FSDIRTREE_MSOCK		(1<<6)
#define	FSDIRTREE_MDIR		(1<<7)
#define	FSDIRTREE_MNOENT	(1<<8)
#define	FSDIRTREE_MUNIQ		(1<<9)	/* unique directories */
#define	FSDIRTREE_MUNIQDIR	FSDIRTREE_MUNIQ


struct fsdirtree_flags {
	uint		feof:1 ;
	uint		dir:1 ;
	uint		dirids:1 ;	/* dir-id tracking */
} ;

struct fsdirtree_head {
	cchar		**prune ;
	char		*bnbuf ;
	char		*nbuf ;
	void		*bsp ;		/* Bit-Set-Pointer */
	fifostr		dirq ;
	fsdir		dir ;
	hdb		dirids ;
	uint		magic ;
	int		opts ;
	int		bndlen ;
	int		cdnlen ;
	int		bnlen ;
	int		nlen ;
	FSDIRTREE_FL	f ;
} ;

typedef FSDIRTREE	fsdirtree ;
typedef	FSDIRTREE_FL	fsdirtree_fl ;
typedef	FSDIRTREE_STAT	fsdirtree_stat ;

EXTERNC_begin

extern int fsdirtree_open(fsdirtree *,cchar *,int) noex ;
extern int fsdirtree_prune(fsdirtree *,cchar **) noex ;
extern int fsdirtree_read(fsdirtree *,USTAT *,char *,int) noex ;
extern int fsdirtree_close(fsdirtree *) noex ;

EXTERNC_end


#ifndef	FSDIRTREESTAT
#define	FSDIRTREESTAT
EXTERNC_begin

extern int fsdirtreestat(cchar *,int,FSDIRTREE_STAT *) noex ;

EXTERNC_end
#endif /* FSDIRTREESTAT */


#endif /* FSDIRTREE_INCLUDE */


