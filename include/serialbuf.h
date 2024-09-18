/* serialbuf HEADER */
/* lang=C20 */

/* object that serializes various types into a given buffer */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-02-01, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	SERIALBUF_INCLUDE
#define	SERIALBUF_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<usystem.h>


#define	SERIALBUF	struct serialbuf_head


struct serialbuf_head {
	char		*sbuf ;	/* buffer pointer (does not change) */
	int		slen ;	/* buffer length  (does not change) */
	int		i ;	/* buffer index   (changes) */
} ;

#ifdef	__cplusplus
enum serialbufmems {
	serialbufmem_getlen,
	serialbufmem_reset,
	serialbufmem_finish,
	serialbufmem_overlast
} ;
struct serialbuf ;
struct serialbuf_co {
	serialbuf	*op = nullptr ;
	int		w = -1 ;
	void operator () (serialbuf *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	operator int () noex ;
	int operator () () noex { 
	    return operator int () ;
	} ;
} ; /* end struct (serialbuf_co) */
struct serialbuf : serialbuf_head {
	serialbuf_co	getlen ;
	serialbuf_co	reset ;
	serialbuf_co	finish ;
	serialbuf() noex {
	    getlen(this,serialbufmem_getlen) ;
	    reset(this,serialbufmem_reset) ;
	    finish(this,serialbufmem_finish) ;
	} ;
	serialbuf(const serialbuf &) = delete ;
	serialbuf &operator = (const serialbuf &) = delete ;
	int start(char *,int = -1) noex ;
	int adv(int) noex ;
	int robj(void *,int) noex ;
	int rc(char *) noex ;
	int rs(short *) noex ;
	int ri(int *) noex ;
	int rl(long *) noex ;
	int rll(longlong *) noex ;
	int ria(int *,int) noex ;
	int rla(long *,int) noex ;
	int rlla(longlong *,int) noex ;
	int rstrw(char *,int) noex ;
	int rstrn(char *,int) noex ;
	int rbuf(char *,int) noex ;
	int ruc(uchar *) noex ;
	int rus(ushort *) noex ;
	int rui(uint *) noex ;
	int rul(ulong *) noex ;
	int rull(ulonglong *) noex ;
	int ruia(uint *,int) noex ;
	int rula(ulong *,int) noex ;
	int rulla(ulonglong *,int) noex ;
	int rustrw(uchar *,int) noex ;
	int rustrn(uchar *,int) noex ;
	int rubuf(uchar *,int) noex ;
	int wobj(cvoid *,int) noex ;
	int wc(char) noex ;
	int ws(short) noex ;
	int wi(int) noex ;
	int wl(long) noex ;
	int wll(longlong) noex ;
	int wia(cint *,int) noex ;
	int wla(clong *,int) noex ;
	int wlla(const longlong *,int) noex ;
	int wstrw(cchar *,int) noex ;
	int wstrn(cchar *,int) noex ;
	int wbuf(cchar *,int) noex ;
	int wuc(uchar) noex ;
	int wus(ushort) noex ;
	int wui(uint) noex ;
	int wul(ulong) noex ;
	int wull(ulonglong) noex ;
	int wuia(cuint *,int) noex ;
	int wula(culong *,int) noex ;
	int wulla(const ulonglong *,int) noex ;
	int wustrw(cuchar *,int) noex ;
	int wustrn(cuchar *,int) noex ;
	int wubuf(cuchar *,int) noex ;
	serialbuf &operator += (int incr) noex {
	    adv(incr) ;
	    return *this ;
	} ;
	template<typename T> int r(T *) noex {
	    i = SR_NOTSUP ;
	    return i ;
	} ;
	serialbuf &operator >> (auto *p) noex {
	    r(p) ;
	    return *this ;
	} ;
	template<typename T> int w(T) noex {
	    i = SR_NOTSUP ;
	    return i ;
	} ;
	serialbuf &operator << (auto v) noex {
	    w(v) ;
	    return *this ;
	} ;
	void dtor() noex ;
	~serialbuf() noex {
	    dtor() ;
	} ;
} ; /* end struct (serialbuf) */
	template<> int serialbuf::r(char *p) noex {
	    return rc(p) ;
	}
	template<> int serialbuf::r(short *p) noex {
	    return rs(p) ;
	}
	template<> int serialbuf::r(int *p) noex {
	    return ri(p) ;
	}
	template<> int serialbuf::r(long *p) noex {
	    return rl(p) ;
	}
	template<> int serialbuf::r(longlong *p) noex {
	    return rll(p) ;
	}
	template<> int serialbuf::r(uchar *p) noex {
	    return ruc(p) ;
	}
	template<> int serialbuf::r(ushort *p) noex {
	    return rus(p) ;
	}
	template<> int serialbuf::r(uint *p) noex {
	    return rui(p) ;
	}
	template<> int serialbuf::r(ulong *p) noex {
	    return rul(p) ;
	}
	template<> int serialbuf::r(ulonglong *p) noex {
	    return rull(p) ;
	}
	template<> int serialbuf::w(char v) noex {
	    return wc(v) ;
	}
	template<> int serialbuf::w(short v) noex {
	    return ws(v) ;
	}
	template<> int serialbuf::w(int v) noex {
	    return wi(v) ;
	}
	template<> int serialbuf::w(long v) noex {
	    return wl(v) ;
	}
	template<> int serialbuf::w(longlong v) noex {
	    return wll(v) ;
	}
	template<> int serialbuf::w(uchar v) noex {
	    return wuc(v) ;
	}
	template<> int serialbuf::w(ushort v) noex {
	    return wus(v) ;
	}
	template<> int serialbuf::w(uint v) noex {
	    return wui(v) ;
	}
	template<> int serialbuf::w(ulong v) noex {
	    return wul(v) ;
	}
	template<> int serialbuf::w(ulonglong v) noex {
	    return wull(v) ;
	}
#else	/* __cplusplus */
typedef SERIALBUF	serialbuf ;
#endif /* __cplusplus */

EXTERNC_begin

extern int serialbuf_start(serialbuf *,char *,int) noex ;

extern int serialbuf_robj(serialbuf *,void *,int) noex ;
extern int serialbuf_rc(serialbuf *,char *) noex ;
extern int serialbuf_rs(serialbuf *,short *) noex ;
extern int serialbuf_ri(serialbuf *,int *) noex ;
extern int serialbuf_rl(serialbuf *,long *) noex ;
extern int serialbuf_rll(serialbuf *,longlong *) noex ;
extern int serialbuf_ria(serialbuf *,int *,int) noex ;
extern int serialbuf_rla(serialbuf *,long *,int) noex ;
extern int serialbuf_rlla(serialbuf *,longlong *,int) noex ;
extern int serialbuf_rstrw(serialbuf *,char *,int) noex ;
extern int serialbuf_rstrn(serialbuf *,char *,int) noex ;
extern int serialbuf_rbuf(serialbuf *,char *,int) noex ;

extern int serialbuf_ruc(serialbuf *,uchar *) noex ;
extern int serialbuf_rus(serialbuf *,ushort *) noex ;
extern int serialbuf_rui(serialbuf *,uint *) noex ;
extern int serialbuf_rul(serialbuf *,ulong *) noex ;
extern int serialbuf_rull(serialbuf *,ulonglong *) noex ;
extern int serialbuf_ruia(serialbuf *,uint *,int) noex ;
extern int serialbuf_rula(serialbuf *,ulong *,int) noex ;
extern int serialbuf_rulla(serialbuf *,ulonglong *,int) noex ;
extern int serialbuf_rustrw(serialbuf *,uchar *,int) noex ;
extern int serialbuf_rustrn(serialbuf *,uchar *,int) noex ;
extern int serialbuf_rubuf(serialbuf *,uchar *,int) noex ;

extern int serialbuf_wobj(serialbuf *,cvoid *,int) noex ;
extern int serialbuf_wc(serialbuf *,char) noex ;
extern int serialbuf_ws(serialbuf *,short) noex ;
extern int serialbuf_wi(serialbuf *,int) noex ;
extern int serialbuf_wl(serialbuf *,long) noex ;
extern int serialbuf_wll(serialbuf *,longlong) noex ;
extern int serialbuf_wia(serialbuf *,cint *,int) noex ;
extern int serialbuf_wla(serialbuf *,clong *,int) noex ;
extern int serialbuf_wlla(serialbuf *,const longlong *,int) noex ;
extern int serialbuf_wstrw(serialbuf *,cchar *,int) noex ;
extern int serialbuf_wstrn(serialbuf *,cchar *,int) noex ;
extern int serialbuf_wbuf(serialbuf *,cchar *,int) noex ;

extern int serialbuf_wuc(serialbuf *,uchar) noex ;
extern int serialbuf_wus(serialbuf *,ushort) noex ;
extern int serialbuf_wui(serialbuf *,uint) noex ;
extern int serialbuf_wul(serialbuf *,ulong) noex ;
extern int serialbuf_wull(serialbuf *,ulonglong) noex ;
extern int serialbuf_wuia(serialbuf *,cuint *,int) noex ;
extern int serialbuf_wula(serialbuf *,culong *,int) noex ;
extern int serialbuf_wulla(serialbuf *,const ulonglong *,int) noex ;
extern int serialbuf_wustrw(serialbuf *,const uchar *,int) noex ;
extern int serialbuf_wustrn(serialbuf *,const uchar *,int) noex ;
extern int serialbuf_wubuf(serialbuf *,const uchar *,int) noex ;

extern int serialbuf_adv(serialbuf *,int) noex ;
extern int serialbuf_getlen(serialbuf *) noex ;
extern int serialbuf_reset(serialbuf *) noex ;
extern int serialbuf_finish(serialbuf *) noex ;

EXTERNC_end


#endif /* SERIALBUF_INCLUDE */


