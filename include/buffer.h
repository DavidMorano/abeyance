/* buffer HEADER */
/* lang=C20 */

/* variable-length buffer management */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-24, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	BUFFER_INCLUDE
#define	BUFFER_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<stdarg.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<ascii.h>
#include	<stdintx.h>


#define	BUFFER		struct buffer_head


struct buffer_head {
	char		*dbuf ;		/* the "buffer" */
	int		dlen ;		/* current buffer extent */
	int		startlen ;	/* saved for expansion purposes */
	int		len ;		/* occupied length */
} ;

#ifdef	__cplusplus
enum buffermems {
	buffermem_start,
	buffermem_strsize,
	buffermem_reset,
	buffermem_finish,
	buffermem_overlast
} ;
struct buffer ;
struct buffer_co {
	buffer		*op = nullptr ;
	int		w = -1 ;
	void operator () (buffer *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex {
	    return operator () () ;
	} ;
	int operator () (int = 0) noex ;
} ; /* end struct (buffer_co) */
struct buffer : buffer_head {
	buffer_co	start ;
	buffer_co	strsize ;
	buffer_co	reset ;
	buffer_co	finish ;
	buffer() noex {
	    strsize(this,buffermem_start) ;
	    strsize(this,buffermem_strsize) ;
	    reset(this,buffermem_reset) ;
	    finish(this,buffermem_finish) ;
	} ;
	buffer(const buffer &) = delete ;
	buffer &operator = (const buffer &) = delete ;
	int adv(int = 1) noex ;
	int strw(cchar *,int = -1) noex ;
	int chr(int) noex ;
	int get(cchar **) noex ;
	template<typename Binary> int bin(Binary) noex ;
	template<typename Octal> int oct(Octal) noex ;
	template<typename Decimal> int dec(Decimal) noex ;
	template<typename Hexadecimal> int hex(Hexadecimal) noex ;
	void dtor() noex ;
	~buffer() noex {
	    dtor() ;
	} ;
} ; /* end struct (buffer) */
#else	/* __cplusplus */
typedef BUFFER		buffer ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	buffer_start(buffer *,int) noex ;
extern int	buffer_reset(buffer *) noex ;
extern int	buffer_adv(buffer *,int) noex ;
extern int	buffer_strw(buffer *,cchar *,int) noex ;
extern int	buffer_chr(buffer *,int) noex ;
extern int	buffer_buf(buffer *,cchar *,int) noex ;
extern int	buffer_deci(buffer *,int) noex ;
extern int	buffer_decl(buffer *,long) noex ;
extern int	buffer_decll(buffer *,longlong) noex ;
extern int	buffer_decui(buffer *,uint) noex ;
extern int	buffer_decul(buffer *,ulong) noex ;
extern int	buffer_decull(buffer *,ulonglong) noex ;
extern int	buffer_hexc(buffer *,int) noex ;
extern int	buffer_hexi(buffer *,int) noex ;
extern int	buffer_hexl(buffer *,long) noex ;
extern int	buffer_hexll(buffer *,longlong) noex ;
extern int	buffer_hexuc(buffer *,uint) noex ;
extern int	buffer_hexui(buffer *,uint) noex ;
extern int	buffer_hexul(buffer *,ulong) noex ;
extern int	buffer_hexull(buffer *,ulonglong) noex ;
extern int	buffer_printf(buffer *,cchar *,...) noex ;
extern int	buffer_vprintf(buffer *,cchar *,va_list) noex ;
extern int	buffer_getprev(buffer *) noex ;
extern int	buffer_get(buffer *,cchar **) noex ;
extern int	buffer_finish(buffer *) noex ;

extern int	buffer_strcompact(buffer *,cchar *,int) noex ;
extern int	buffer_stropaque(buffer *,cchar *,int) noex ;
extern int	buffer_strquote(buffer *,cchar *,int) noex ;
extern int	buffer_chrs(buffer *,int,int) noex ;
extern int	buffer_blanks(buffer *,int) noex ;

static inline int buffer_backs(buffer *op,int n) noex {
	return buffer_chrs(op,CH_BS,n) ;
}
static inline int buffer_str(buffer *op,cchar *sp) noex {
	return buffer_strw(op,sp,-1) ;
}

EXTERNC_end

#ifdef	__cplusplus

inline int buffer_dec(buffer *op,int v) noex {
	return buffer_deci(op,v) ;
}
inline int buffer_dec(buffer *op,long v) noex {
	return buffer_decl(op,v) ;
}
inline int buffer_dec(buffer *op,longlong v) noex {
	return buffer_decll(op,v) ;
}

inline int buffer_dec(buffer *op,uint v) noex {
	return buffer_decui(op,v) ;
}
inline int buffer_dec(buffer *op,ulong v) noex {
	return buffer_decul(op,v) ;
}
inline int buffer_dec(buffer *op,ulonglong v) noex {
	return buffer_decull(op,v) ;
}

inline int buffer_hex(buffer *op,int v) noex {
	return buffer_hexi(op,v) ;
}
inline int buffer_hex(buffer *op,long v) noex {
	return buffer_hexl(op,v) ;
}
inline int buffer_hex(buffer *op,longlong v) noex {
	return buffer_hexll(op,v) ;
}

inline int buffer_hex(buffer *op,uint v) noex {
	return buffer_hexui(op,v) ;
}
inline int buffer_hex(buffer *op,ulong v) noex {
	return buffer_hexul(op,v) ;
}
inline int buffer_hex(buffer *op,ulonglong v) noex {
	return buffer_hexull(op,v) ;
}

template<typename Binary> int buffer::bin(Binary v) noex {
	return buffer_bin(this,v) ;
}
template<typename Octal> int buffer::oct(Octal v) noex {
	return buffer_oct(this,v) ;
}
template<typename Decimal> int buffer::dec(Decimal v) noex {
	return buffer_dec(this,v) ;
}
template<typename Hexadecimal> int buffer::hex(Hexadecimal v) noex {
	return buffer_hex(this,v) ;
}

#endif /* __cplusplus */


#endif /* BUFFER_INCLUDE */


