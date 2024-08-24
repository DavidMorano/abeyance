/* sbuf HEADER */
/* lang=C20 */

/* storage buffer (SBuf) object */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-24, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SBUF_INCLUDE
#define	SBUF_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<stdarg.h>		/* |va_list(3c)| */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdintx.h>


#define	SBUF		struct sbuf_head


struct sbuf_head {
	char		*rbuf ;		/* result buffer base (constant) */
	int		rlen ;		/* result buffer length (constant) */
	int		index ;		/* current buffer index (changes) */
} ;

#ifdef	__cplusplus
enum sbufmems {
	sbufmem_deci,
	sbufmem_hexc,
	sbufmem_hexi,
	sbufmem_chr,
	sbufmem_blanks,
	sbufmem_rem,
	sbufmem_getlen,
	sbufmem_getprev,
	sbufmem_reset,
	sbufmem_finish,
	sbufmem_overlast
} ;
struct sbuf_iter {
	cchar		*cp = nullptr ;
	sbuf_iter() = default ;
	sbuf_iter(cchar *p) noex : cp(p) { } ;
	sbuf_iter(const sbuf_iter &oit) noex {
	    if (this != &oit) {
		cp = oit.cp ;
	    }
	} ;
	sbuf_iter &operator = (const sbuf_iter &oit) noex {
	    if (this != &oit) {
		cp = oit.cp ;
	    }
	    return *this ;
	} ;
	bool operator != (const sbuf_iter &) noex ;
	bool operator == (const sbuf_iter &) noex ;
	char operator * () noex {
	    return *cp ;
	} ;
	sbuf_iter operator + (int) const noex ;
	sbuf_iter operator += (int) noex ;
	sbuf_iter operator ++ () noex ; /* pre */
	sbuf_iter operator ++ (int) noex ; /* post */
	void increment(int = 1) noex ;
} ; /* end struct sbuf_iter) */
struct sbuf ;
struct sbuf_co {
	sbuf		*op = nullptr ;
	int		w = -1 ;
	void operator () (sbuf *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	int operator () (int = 1) noex ;
	operator int () noex {
	    return operator () () ;
	} ;
} ; /* end struct (sbuf_co) */
extern "C" {
   extern int sbuf_strw(sbuf *,cchar *,int) noex ;
   extern int sbuf_addquoted(sbuf *,cchar *,int) noex ;
}
struct sbuf : sbuf_head {
	sbuf_co		deci ;
	sbuf_co		hexc ;
	sbuf_co		hexi ;
	sbuf_co		chr ;
	sbuf_co		blanks ;
	sbuf_co		rem ;
	sbuf_co		getlen ;
	sbuf_co		getprev ;
	sbuf_co		reset ;
	sbuf_co		finish ;
	sbuf() noex {
	    deci(this,sbufmem_deci) ;
	    hexc(this,sbufmem_hexc) ;
	    hexi(this,sbufmem_hexi) ;
	    chr(this,sbufmem_chr) ;
	    blanks(this,sbufmem_blanks) ;
	    rem(this,sbufmem_rem) ;
	    getlen(this,sbufmem_getlen) ;
	    getprev(this,sbufmem_getprev) ;
	    reset(this,sbufmem_reset) ;
	    finish(this,sbufmem_finish) ;
	} ;
	sbuf(const sbuf &) = delete ;
	sbuf &operator = (const sbuf &) = delete ;
	int start(char *,int) noex ;
	int chrs(int,int = 1) noex ;
	int strw(cchar *sp,int sl = -1) noex {
	    return sbuf_strw(this,sp,sl) ;
	} ;
	int str(cchar *sp) noex {
	    return sbuf_strw(this,sp,-1) ;
	} ;
	int addquoted(cchar *sp,int sl = -1) noex {
	    return sbuf_addquoted(this,sp,sl) ;
	} ;
	template<typename Binary> int bin(Binary) noex ;
	template<typename Octal> int oct(Octal) noex ;
	template<typename Decimal> int dec(Decimal) noex ;
	template<typename Hexadecimal> int hex(Hexadecimal) noex ;
	sbuf &operator << (cchar *cp) noex {
	    strw(cp) ;
	    return *this ;
	} ;
	sbuf &operator << (char ch) noex {
	    chr(ch) ;
	    return *this ;
	} ;
	sbuf_iter begin() noex {
	    sbuf_iter		it(rbuf) ;
	    return it ;
	} ;
	sbuf_iter end() noex {
	    sbuf_iter		it(rbuf+index) ;
	    return it ;
	} ;
	void dtor() noex ;
	~sbuf() noex {
	    dtor() ;
	} ;
} ; /* end struct (sbuf) */
#else	/* __cplusplus */
typedef SBUF		sbuf ;
#endif /* __cplusplus */

EXTERNC_begin

extern int	sbuf_start(sbuf *,char *,int) noex ;
extern int	sbuf_finish(sbuf *) noex ;
extern int	sbuf_reset(sbuf *) noex ;
extern int	sbuf_buf(sbuf *,cchar *,int) noex ;
extern int	sbuf_strw(sbuf *,cchar *,int) noex ;
extern int	sbuf_strs(sbuf *,int,cchar **) noex ;
extern int	sbuf_bini(sbuf *,int) noex ;
extern int	sbuf_binl(sbuf *,long) noex ;
extern int	sbuf_binll(sbuf *,longlong) noex ;
extern int	sbuf_binui(sbuf *,uint) noex ;
extern int	sbuf_binul(sbuf *,ulong) noex ;
extern int	sbuf_binull(sbuf *,ulonglong) noex ;
extern int	sbuf_octi(sbuf *,int) noex ;
extern int	sbuf_octl(sbuf *,long) noex ;
extern int	sbuf_octll(sbuf *,longlong) noex ;
extern int	sbuf_octui(sbuf *,uint) noex ;
extern int	sbuf_octul(sbuf *,ulong) noex ;
extern int	sbuf_octull(sbuf *,ulonglong) noex ;
extern int	sbuf_deci(sbuf *,int) noex ;
extern int	sbuf_decl(sbuf *,long) noex ;
extern int	sbuf_decll(sbuf *,longlong) noex ;
extern int	sbuf_decui(sbuf *,uint) noex ;
extern int	sbuf_decul(sbuf *,ulong) noex ;
extern int	sbuf_decull(sbuf *,ulonglong) noex ;
extern int	sbuf_hexc(sbuf *,char) noex ;
extern int	sbuf_hexi(sbuf *,int) noex ;
extern int	sbuf_hexl(sbuf *,long) noex ;
extern int	sbuf_hexll(sbuf *,longlong) noex ;
extern int	sbuf_hexuc(sbuf *,uchar) noex ;
extern int	sbuf_hexui(sbuf *,uint) noex ;
extern int	sbuf_hexul(sbuf *,ulong) noex ;
extern int	sbuf_hexull(sbuf *,ulonglong) noex ;
extern int	sbuf_chr(sbuf *,int) noex ;
extern int	sbuf_chrs(sbuf *,int,int) noex ;
extern int	sbuf_blanks(sbuf *,int) noex ;
extern int	sbuf_adv(sbuf *,int,char **) noex ;
extern int	sbuf_rem(sbuf *) noex ;
extern int	sbuf_getlen(sbuf *) noex ;
extern int	sbuf_getbuf(sbuf *,cchar **) noex ;
extern int	sbuf_getpoint(sbuf *,cchar **) noex ;
extern int	sbuf_getprev(sbuf *) noex ;
extern int	sbuf_printf(sbuf *,cchar *,...) noex ;
extern int	sbuf_vprintf(sbuf *,cchar *,va_list) noex ;
extern int	sbuf_termconseq(sbuf *,int,cchar *,int,...) noex ;
extern int	sbuf_addquoted(sbuf *,cchar *,int) noex ;

static inline int sbuf_str(sbuf *op,cchar *sp) noex {
	return sbuf_strw(op,sp,-1) ;
}
static inline int sbuf_char(sbuf *op,int ch) noex {
	return sbuf_chr(op,ch) ;
}

EXTERNC_end

#ifdef	__cplusplus

inline int sbuf_bin(sbuf *op,int v) noex {
	return sbuf_bini(op,v) ;
}
inline int sbuf_bin(sbuf *op,long v) noex {
	return sbuf_binl(op,v) ;
}
inline int sbuf_bin(sbuf *op,longlong v) noex {
	return sbuf_binll(op,v) ;
}

inline int sbuf_bin(sbuf *op,uint v) noex {
	return sbuf_binui(op,v) ;
}
inline int sbuf_bin(sbuf *op,ulong v) noex {
	return sbuf_binul(op,v) ;
}
inline int sbuf_bin(sbuf *op,ulonglong v) noex {
	return sbuf_binull(op,v) ;
}

template<typename Binary> int sbuf::bin(Binary v) noex {
	return sbuf_bin(this,v) ;
}

inline int sbuf_oct(sbuf *op,int v) noex {
	return sbuf_octi(op,v) ;
}
inline int sbuf_oct(sbuf *op,long v) noex {
	return sbuf_octl(op,v) ;
}
inline int sbuf_oct(sbuf *op,longlong v) noex {
	return sbuf_octll(op,v) ;
}

inline int sbuf_oct(sbuf *op,uint v) noex {
	return sbuf_octui(op,v) ;
}
inline int sbuf_oct(sbuf *op,ulong v) noex {
	return sbuf_octul(op,v) ;
}
inline int sbuf_oct(sbuf *op,ulonglong v) noex {
	return sbuf_octull(op,v) ;
}

template<typename Octal> int sbuf::oct(Octal v) noex {
	return sbuf_oct(this,v) ;
}

inline int sbuf_dec(sbuf *op,int v) noex {
	return sbuf_deci(op,v) ;
}
inline int sbuf_dec(sbuf *op,long v) noex {
	return sbuf_decl(op,v) ;
}
inline int sbuf_dec(sbuf *op,longlong v) noex {
	return sbuf_decll(op,v) ;
}

inline int sbuf_dec(sbuf *op,uint v) noex {
	return sbuf_decui(op,v) ;
}
inline int sbuf_dec(sbuf *op,ulong v) noex {
	return sbuf_decul(op,v) ;
}
inline int sbuf_dec(sbuf *op,ulonglong v) noex {
	return sbuf_decull(op,v) ;
}

template<typename Decimal> int sbuf::dec(Decimal v) noex {
	return sbuf_dec(this,v) ;
}

inline int sbuf_hex(sbuf *op,int v) noex {
	return sbuf_hexi(op,v) ;
}
inline int sbuf_hex(sbuf *op,long v) noex {
	return sbuf_hexl(op,v) ;
}
inline int sbuf_hex(sbuf *op,longlong v) noex {
	return sbuf_hexll(op,v) ;
}

inline int sbuf_hex(sbuf *op,uint v) noex {
	return sbuf_hexui(op,v) ;
}
inline int sbuf_hex(sbuf *op,ulong v) noex {
	return sbuf_hexul(op,v) ;
}
inline int sbuf_hex(sbuf *op,ulonglong v) noex {
	return sbuf_hexull(op,v) ;
}

template<typename Hexadecimal> int sbuf::hex(Hexadecimal v) noex {
	return sbuf_hex(this,v) ;
}

#endif /* __cplusplus */


#endif /* SBUF_INCLUDE */


