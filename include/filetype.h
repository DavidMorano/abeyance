/* filetype HEADER */
/* lang=C20 */

/* define file types according to the S_IFMT field of |mode_t| */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	FILETYPE_INCLUDE
#define	FILETYPE_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/stat.h>		/* |S_IFMT| */
#include	<dirent.h>		/* possielbe preprocesor 'DT_{x}' */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


#ifndef	S_IFMT
#define	S_IFMT	(0x0F << 12)
#endif


enum filetypes {
	filetype_unassigned0,		/* 0 */
	filetype_fifo,			/* 1 */
	filetype_chr,			/* 2 */
	filetype_unassigned3,		/* 3 */
	filetype_dir,			/* 4 */
	filetype_name,			/* 5 - XENIX® special named file */
	filetype_blk,			/* 6 */
	filetype_unassigned7,		/* 7 */
	filetype_reg,			/* 8 */
	filetype_unassigned9,		/* 9 */
	filetype_lnk,			/* 10 */
	filetype_unassigned11,		/* 11 */
	filetype_sock,			/* 12 */
	filetype_door,			/* 13 */
	filetype_wht,			/* 14 - "event port" on Solaris® */
	filetype_unassigned15,		/* 15 */
	filetype_overlast
} ;


#ifndef	DT_UNKNOWN
#define	DT_UNKNOWN	filetype_reg
#endif

#ifndef	DT_FIFO
#define	DT_FIFO		filetype_fifo
#endif

#ifndef	DT_CHR
#define	DT_CHR		filetype_chr
#endif

#ifndef	DT_DIR
#define	DT_DIR		filetype_dir
#endif

#ifndef	DT_NAME
#define	DT_NAME		filetype_name
#endif

#ifndef	DT_BLK
#define	DT_BLK		filetype_blk
#endif

#ifndef	DT_REG
#define	DT_REG		filetype_reg
#endif

#ifndef	DT_LNK
#define	DT_LNK		filetype_lnk
#endif

#ifndef	DT_SOCK
#define	DT_SOCK		filetype_sock
#endif

#ifndef	DT_DOOR
#define	DT_DOOR		filetype_door
#endif

#ifndef	DT_WHT
#define	DT_WHT		filetype_wht
#endif


EXTERNC_begin

static inline int filetype(mode_t m) noex {
	cuint	uv = (uint) m ;
	return ((uv & S_IFMT) >> 12) ;
}

EXTERNC_end


#endif /* FILETYPE_INCLUDE */


