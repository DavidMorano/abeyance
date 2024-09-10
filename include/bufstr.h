/* bufstr HEADER */
/* lang=C20 */

/* string buffer object */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	bufstr

	Description:
	This module can be used to construct strings or messages
	in buffers WITHOUT using the |snsprint(3c)| subroutine.  This
	module is useful when the user does NOT supply a buffer to
	be used as the working store.  Rather, an internally,
	dynamically grown and managed buffer is maintained.  This
	module uses an object, that must be initialized and eventually
	freed, to track the state of the dynamically used internal
	buffer.

*******************************************************************************/

#ifndef	BUFSTR_INCLUDE
#define	BUFSTR_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<stdintx.h>


#define	BUFSTR		struct bufstr_head
#define	BUFSTR_LEN	100		/* default value */


struct bufstr_head {
	char		*dbuf ;		/* dynamic- buffer */
	int		dlen ;		/* extent */
	int		len ;		/* index (active length) */
	char		sbuf[BUFSTR_LEN + 1] ; /* static-buffer */
} ;

#ifdef	__cplusplus
enum bufstrmems {
	bufstrmem_start,
	bufstrmem_strsize,
	bufstrmem_finish,
	bufstrmem_overlast
} ;
struct bufstr ;
struct bufstr_co {
	bufstr		*op = nullptr ;
	int		w = -1 ;
	void operator () (bufstr *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (bufstr_co) */
struct bufstr : bufstr_head {
	bufstr_co	start ;
	bufstr_co	strsize ;
	bufstr_co	finish ;
	bufstr() noex {
	    start(this,bufstrmem_start) ;
	    strsize(this,bufstrmem_strsize) ;
	    finish(this,bufstrmem_finish) ;
	} ;
	bufstr(const bufstr &) = delete ;
	bufstr &operator = (const bufstr &) = delete ;
	int strw(cchar *,int = -1) noex ;
	int chr(int) noex ;
	int get(cchar **) noex ;
	template<typename Binary> int bin(Binary) noex ;
	template<typename Octal> int oct(Octal) noex ;
	template<typename Decimal> int dec(Decimal) noex ;
	template<typename Hexadecimal> int hex(Hexadecimal) noex ;
	void dtor() noex ;
	~bufstr() noex {
	    dtor() ;
	} ;
} ; /* end struct (bufstr) */
#else	/* __cplusplus */
typedef BUFFER		bufstr ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	bufstr_start(bufstr *) noex ;
extern int	bufstr_strw(bufstr *,cchar *,int) noex ;
extern int	bufstr_chr(bufstr *,int) noex ;
extern int	bufstr_deci(bufstr *,int) noex ;
extern int	bufstr_decl(bufstr *,long) noex ;
extern int	bufstr_decll(bufstr *,longlong) noex ;
extern int	bufstr_decui(bufstr *,uint) noex ;
extern int	bufstr_decul(bufstr *,ulong) noex ;
extern int	bufstr_decull(bufstr *,ulonglong) noex ;
extern int	bufstr_hexi(bufstr *,int) noex ;
extern int	bufstr_hexl(bufstr *,long) noex ;
extern int	bufstr_hexll(bufstr *,longlong) noex ;
extern int	bufstr_hexui(bufstr *,uint) noex ;
extern int	bufstr_hexul(bufstr *,ulong) noex ;
extern int	bufstr_hexull(bufstr *,ulonglong) noex ;
extern int	bufstr_get(bufstr *,cchar **) noex ;
extern int	bufstr_finish(bufstr *) noex ;

EXTERNC_end

#ifdef	__cplusplus

inline int bufstr_dec(bufstr *op,int v) noex {
	return bufstr_deci(op,v) ;
}
inline int bufstr_dec(bufstr *op,long v) noex {
	return bufstr_decl(op,v) ;
}
inline int bufstr_dec(bufstr *op,longlong v) noex {
	return bufstr_decll(op,v) ;
}

inline int bufstr_dec(bufstr *op,uint v) noex {
	return bufstr_decui(op,v) ;
}
inline int bufstr_dec(bufstr *op,ulong v) noex {
	return bufstr_decul(op,v) ;
}
inline int bufstr_dec(bufstr *op,ulonglong v) noex {
	return bufstr_decull(op,v) ;
}

inline int bufstr_hex(bufstr *op,int v) noex {
	return bufstr_hexi(op,v) ;
}
inline int bufstr_hex(bufstr *op,long v) noex {
	return bufstr_hexl(op,v) ;
}
inline int bufstr_hex(bufstr *op,longlong v) noex {
	return bufstr_hexll(op,v) ;
}

inline int bufstr_hex(bufstr *op,uint v) noex {
	return bufstr_hexui(op,v) ;
}
inline int bufstr_hex(bufstr *op,ulong v) noex {
	return bufstr_hexul(op,v) ;
}
inline int bufstr_hex(bufstr *op,ulonglong v) noex {
	return bufstr_hexull(op,v) ;
}

template<typename Binary> int bufstr::bin(Binary v) noex {
	return bufstr_bin(this,v) ;
}
template<typename Octal> int bufstr::oct(Octal v) noex {
	return bufstr_oct(this,v) ;
}
template<typename Decimal> int bufstr::dec(Decimal v) noex {
	return bufstr_dec(this,v) ;
}
template<typename Hexadecimal> int bufstr::hex(Hexadecimal v) noex {
	return bufstr_hex(this,v) ;
}

#endif /* __cplusplus */


#endif /* BUFSTR_INCLUDE */


