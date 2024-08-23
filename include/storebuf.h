/* storebuf HEADER */
/* lang=C20 */

/* storage buffer manipulation subroutines */
/* version %I% last-modified %G% */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STOREBUF_INCLUDE
#define	STOREBUF_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>


EXTERNC_begin

extern int storebuf_buf(char *,int,int,cchar *,int) noex ;
extern int storebuf_strw(char *,int,int,cchar *,int) noex ;
extern int storebuf_chr(char *,int,int,int) noex ;

extern int storebuf_bini(char *,int,int,int) noex ;
extern int storebuf_binl(char *,int,int,long) noex ;
extern int storebuf_binll(char *,int,int,longlong) noex ;
extern int storebuf_binui(char *,int,int,uint) noex ;
extern int storebuf_binul(char *,int,int,ulong) noex ;
extern int storebuf_binull(char *,int,int,ulonglong) noex ;

extern int storebuf_octi(char *,int,int,int) noex ;
extern int storebuf_octl(char *,int,int,long) noex ;
extern int storebuf_octll(char *,int,int,longlong) noex ;
extern int storebuf_octui(char *,int,int,uint) noex ;
extern int storebuf_octul(char *,int,int,ulong) noex ;
extern int storebuf_octull(char *,int,int,ulonglong) noex ;

extern int storebuf_deci(char *,int,int,int) noex ;
extern int storebuf_decl(char *,int,int,long) noex ;
extern int storebuf_decll(char *,int,int,longlong) noex ;
extern int storebuf_decui(char *,int,int,uint) noex ;
extern int storebuf_decul(char *,int,int,ulong) noex ;
extern int storebuf_decull(char *,int,int,ulonglong) noex ;

extern int storebuf_hexi(char *,int,int,int) noex ;
extern int storebuf_hexl(char *,int,int,long) noex ;
extern int storebuf_hexll(char *,int,int,longlong) noex ;
extern int storebuf_hexui(char *,int,int,uint) noex ;
extern int storebuf_hexul(char *,int,int,ulong) noex ;
extern int storebuf_hexull(char *,int,int,ulonglong) noex ;

static inline int storebuf_str(char *bp,int bl,int i,cchar *sp) noex {
	return storebuf_strw(bp,bl,i,sp,-1) ;
}
static inline int storebuf_char(char *bp,int bl,int i,int ch) noex {
	return storebuf_chr(bp,bl,i,ch) ;
}

EXTERNC_end

#ifdef	__cplusplus

inline int storebuf_bin(char *bp,int bl,int i,int v) noex {
	return storebuf_bini(bp,bl,i,v) ;
}
inline int storebuf_bin(char *bp,int bl,int i,long v) noex {
	return storebuf_binl(bp,bl,i,v) ;
}
inline int storebuf_bin(char *bp,int bl,int i,longlong v) noex {
	return storebuf_binll(bp,bl,i,v) ;
}

inline int storebuf_bin(char *bp,int bl,int i,uint uv) noex {
	return storebuf_binui(bp,bl,i,uv) ;
}
inline int storebuf_bin(char *bp,int bl,int i,ulong uv) noex {
	return storebuf_binul(bp,bl,i,uv) ;
}
inline int storebuf_bin(char *bp,int bl,int i,ulonglong uv) noex {
	return storebuf_binull(bp,bl,i,uv) ;
}

inline int storebuf_oct(char *bp,int bl,int i,int v) noex {
	return storebuf_octi(bp,bl,i,v) ;
}
inline int storebuf_oct(char *bp,int bl,int i,long v) noex {
	return storebuf_octl(bp,bl,i,v) ;
}
inline int storebuf_oct(char *bp,int bl,int i,longlong v) noex {
	return storebuf_octll(bp,bl,i,v) ;
}

inline int storebuf_oct(char *bp,int bl,int i,uint uv) noex {
	return storebuf_octui(bp,bl,i,uv) ;
}
inline int storebuf_oct(char *bp,int bl,int i,ulong uv) noex {
	return storebuf_octul(bp,bl,i,uv) ;
}
inline int storebuf_oct(char *bp,int bl,int i,ulonglong uv) noex {
	return storebuf_octull(bp,bl,i,uv) ;
}

inline int storebuf_dec(char *bp,int bl,int i,int v) noex {
	return storebuf_deci(bp,bl,i,v) ;
}
inline int storebuf_dec(char *bp,int bl,int i,long v) noex {
	return storebuf_decl(bp,bl,i,v) ;
}
inline int storebuf_dec(char *bp,int bl,int i,longlong v) noex {
	return storebuf_decll(bp,bl,i,v) ;
}

inline int storebuf_dec(char *bp,int bl,int i,uint uv) noex {
	return storebuf_decui(bp,bl,i,uv) ;
}
inline int storebuf_dec(char *bp,int bl,int i,ulong uv) noex {
	return storebuf_decul(bp,bl,i,uv) ;
}
inline int storebuf_dec(char *bp,int bl,int i,ulonglong uv) noex {
	return storebuf_decull(bp,bl,i,uv) ;
}

inline int storebuf_hex(char *bp,int bl,int i,int v) noex {
	return storebuf_hexi(bp,bl,i,v) ;
}
inline int storebuf_hex(char *bp,int bl,int i,long v) noex {
	return storebuf_hexl(bp,bl,i,v) ;
}
inline int storebuf_hex(char *bp,int bl,int i,longlong v) noex {
	return storebuf_hexll(bp,bl,i,v) ;
}

inline int storebuf_hex(char *bp,int bl,int i,uint uv) noex {
	return storebuf_hexui(bp,bl,i,uv) ;
}
inline int storebuf_hex(char *bp,int bl,int i,ulong uv) noex {
	return storebuf_hexul(bp,bl,i,uv) ;
}
inline int storebuf_hex(char *bp,int bl,int i,ulonglong uv) noex {
	return storebuf_hexull(bp,bl,i,uv) ;
}

struct storebuf {
	char		*bufp ;
	int		bufl ;
	storebuf() = delete ;
	storebuf(char *p,int l) noex : bufp(p), bufl(l) { } ;
	int chr(int i,int ch) noex {
	    return storebuf_chr(bufp,bufl,i,ch) ;
	} ;
	int strw(int i,cchar *sp,int sl = -1) noex {
	    return storebuf_strw(bufp,bufl,i,sp,sl) ;
	} ;
	int str(int i,cchar *sp) noex {
	    return storebuf_str(bufp,bufl,i,sp) ;
	} ;
	int buf(int i,cchar *sp,int sl = -1) noex {
	    return storebuf_buf(bufp,bufl,i,sp,sl) ;
	} ;
	int bin(int i,auto v) noex {
	    return storebuf_bin(bufp,bufl,i,v) ;
	} ;
	int oct(int i,auto v) noex {
	    return storebuf_oct(bufp,bufl,i,v) ;
	} ;
	int dec(int i,auto v) noex {
	    return storebuf_dec(bufp,bufl,i,v) ;
	} ;
	int hexn(int i,auto v) noex {
	    return storebuf_hex(bufp,bufl,i,v) ;
	} ;
} ; /* end struct (storebuf) */

#endif /* __cplusplus */


#endif /* STOREBUF_INCLUDE */


