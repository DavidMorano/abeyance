/* objfile HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 */

/* simulated program mapping manager */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-07-26, David A­D­ Morano
	This code was started.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	OBJFILE_INCLUDE
#define	OBJFILE_INCLUDE


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<unistd.h>
#include	<stddef.h>
#include	<stdint.h>
#include	<elf.h>
#include	<vecobj.h>
#include	<hdb.h>


#define	OBJFILE_MAGIC		0x14253592
#define	OBJFILE			struct objfile_head
#define	OBJFILE_FL		struct objfile_flags
#define	OBJFILE_HA		struct objfile_hash
#define	OBJFILE_TAB		struct objfile_symtab
#define	OBJFILE_SYM		struct objfile_symbol
#define	OBJFILE_SNCUR		HDB_CUR


/* a single humble symbol */
struct objfile_symbol {
	Elf32_Sym	*ep ;
	cchar		*name ;
} ;

struct objfile_hash {
	caddr_t		pa_hash ;
	caddr_t		pa_dynsym ;
	caddr_t		pa_dynstr ;
	Elf32_Sym	*symtab ;	/* the symbol table */
	uint		*hashtab ;
	char		*strings ;
	uint		maplen_hash ;
	uint		maplen_dynsym ;
	uint		maplen_strtab ;
} ;

/* this is a symbol table, there can be many per object file ! */
struct objfile_symtab {
	caddr_t		pa_symtab ;	/* base address */
	caddr_t		pa_strings ;	/* base address */
	Elf32_Sym	*symtab ;	/* the symbol table */
	char		*strings ;	/* the string table */
	uint		maplen_symtab ;
	uint		maplen_strings ;
	uint		entsize ;	/* entry size */
	uint		nsyms ;		/* number of symbols */
	uint		type ;
} ;

struct objfile_flags {
	uint		symtab:1 ;	/* there were symbol tables */
	uint		symbols:1 ;	/* there are indexed symbols */
	uint		bss:1 ;		/* there was a BSS section */
	uint		hash:1 ;
	uint		dynsym:1 ;
} ;

struct objfile_head {
	OBJFILE_FL	f ;
	OBJFILE_HA	h ;
	hdb		symbols ;	/* fast symbol access */
	vecobj		symtabs ;	/* symbol tables */
	cchar		*fname ;	/* ELF program file name */
	Elf32_Shdr	*sheads  ;
	time_t		lastaccess ;	/* last access time (informational) */
	uintptr_t	pagealign ;	/* virtual page alignment */
	uintptr_t	mapalign ;	/* alignment for mapping */
	uintptr_t	progentry ;	/* program entry address */
	uint		magic ;
	int		nsheads ;	/* number of sections */
	int		ofd ;		/* object file descriptor */
} ;

typedef	OBJFILE			objfile ;
typedef	OBJFILE_FL		objfile_fl ;
typedef	OBJFILE_HA		objfile_ha ;
typedef	OBJFILE_TAB		objfile_tab ;
typedef	OBJFILE_SYM		objfile_sym ;
typedef	OBJFILE_SNCUR		objfile_sncur ;

EXTERNC_begin

extern int objfile_open(objfile *,cchar *) noex ;
extern int objfile_getentry(objfile *,uint *) noex ;
extern int objfile_getpagesize(objfile *,uint *) noex ;
extern int objfile_getsym(objfile *,cchar *,Elf32_Sym **) noex ;
extern int objfile_sncurbegin(objfile *,objfile_sncur *) noex ;
extern int objfile_sncurend(objfile *,objfile_sncur *) noex ;
extern int objfile_fetchsym(objfile *,cc *,objfile_sncur *,Elf32_Sym **) noex ;
extern int objfile_enumsym(objfile *,objfile_sncur *,cc **,Elf32_Sym **) noex ;
extern int objfile_getsec(objfile *,int,Elf32_Shdr **) noex ;
extern int objfile_close(objfile *) noex ;

EXTERNC_end


#endif /* OBJFILE_INCLUDE */


