/* clanguage HEADER */
/* lang=C20 */

/* version %I% last-modified %G% */
/* C-language defines */


/* revision history:

	= 1998-03-21, David A­D­ Morano
	This module was originally written.

	= 2017-08-01, David A­D­ Morano
	Updated for lack of interfaces in MacOS Darwin

*/

/* Copyright © 1998,2017 David A­D­ Morano.  All rights reserved. */

#ifndef	CLANGUAGE_INCLUDE
#define	CLANGUAGE_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */


#ifndef	noex
#ifdef	__cplusplus
#define	noex			noexcept
#else
#define	noex			/* noexcept */
#endif
#endif /* noex */

#ifndef	va_begin
#define	va_begin(ap,arg)	va_start((ap),(arg))
#endif
#ifndef	va_finish
#define	va_finish(ap)		va_end((ap))
#endif
#ifndef	va_get
#define	va_get(ap,atype)	va_arg(ap,atype)
#endif

#ifndef	repeat
#define repeat			do
#define	until(cond)		while(!(cond))
#endif

#ifndef	forever
#define	forever			for (;;)
#endif

#ifndef	fallthrough
#define	fallthrough		/* FALLTHROUGH */
#endif

#ifndef	nelements
#define	nelements(n)		(sizeof(n) / sizeof((n)[0]))
#endif

#ifndef	nelem
#define	nelem(n)		(sizeof(n) / sizeof((n)[0]))
#endif

#ifdef	__cplusplus
#ifndef	npack
#define	npack(args)		sizeof...(args)
#endif
#endif /* __cplusplus */

#ifdef	__cplusplus
#ifndef	typeof
#define	typeof(expr)		decltype(expr)
#endif
#endif /* __cplusplus */

#ifdef	__cplusplus
#ifndef	if_constexpr
#define	if_constexpr		if constexpr
#endif
#endif /* __cplusplus */

#ifdef	__cplusplus
#ifndef	if_consteval
#define	if_consteval		if consteval
#endif
#endif /* __cplusplus */

#ifdef	__cplusplus
#ifndef	cast_static
#define	cast_static		static_cast
#define	cast_dynamic		dynamic_cast
#define	cast_const		const_cast
#define	cast_reinterpret	reinterpret_cast
#define	cast_bit		bit_cast
#define	cast_saturate		saturate_cast
#endif
#endif /* __cplusplus */

#ifdef	__cplusplus
#ifndef	cauto
#define	cauto			const auto
#endif
#endif /* __cplusplus */


#ifndef	EXTERNC_begin
#ifdef	__cplusplus
#define	EXTERNC_begin	extern "C" {
#define	EXTERNC_end	}
#else
#define	EXTERNC_begin	/* externc_begin */
#define	EXTERNC_end	/* externc_end */
#endif /* __cplusplus */
#endif /* EXTERNC_begin */


#endif /* CLANGUAGE_INCLUDE */


