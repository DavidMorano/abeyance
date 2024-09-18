/* commandment HEADER */
/* lang=C++20 */

/* COMMANDMENT object-load management */
/* version %I% last-modified %G% */


/* revision history:

	= 2008-03-01, David A­D­ Morano
	This module was originally written.

*/

/* Copyright © 2008 David A­D­ Morano.  All rights reserved. */

#ifndef	COMMANDMENT_INCLUDE
#define	COMMANDMENT_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<clanguage.h>
#include	<modload.h>
#include	<localmisc.h>
#include	<commandments.h>


#define	COMMANDMENT_MAGIC	0x99447242
#define	COMMANDMENT		struct commandment_head
#define	COMMANDMENT_CA		struct commandment_calls
#define	COMMANDMENT_CUR		struct commandment_cursor


struct commandment_cursor {
	void	*scp ;
	uint	magic ;
} ;

EXTERNC_begin

struct commandment_calls {
	int	(*open)(void *,cchar *,cchar *) noex ;
	int	(*audit)(void *) noex ;
	int	(*count)(void *) noex ;
	int	(*nmax)(void *) noex ;
	int	(*read)(void *,char *,int,uint) noex ;
	int	(*get)(void *,int,char *,int) noex ;
	int	(*curbegin)(void *,void *) noex ;
	int	(*curend)(void *,void *) noex ;
	int	(*enumerate)(void *,void *,void *,char *,int) noex ;
	int	(*close)(void *) noex ;
} ;

EXTERNC_end

struct commandment_head {
	modload		loader ;
	COMMANDMENT_CA	call ;
	void		*obj ;		/* object pointer */
	uint		magic ;
	int		objsize ;
	int		cursize ;
} ;

EXTERNC_begin

extern int	commandment_open(commandment *,cchar *,cchar *) noex ;
extern int	commandment_audit(commandment *) noex ;
extern int	commandment_count(commandment *) noex ;
extern int	commandment_max(commandment *) noex ;
extern int	commandment_read(commandment *,char *,int,int) noex ;
extern int	commandment_get(commandment *,int,char *,int) noex ;
extern int	commandment_curbegin(commandment *,commandment_cur *) noex ;
extern int	commandment_curend(commandment *,commandment_cur *) noex ;
extern int	commandment_enum(commandment *,commandment_cur *,
			uint *,char *,int) noex ;
extern int	commandment_close(commandment *) noex ;

EXTERNC_end


#endif /* COMMANDMENT_INCLUDE */


