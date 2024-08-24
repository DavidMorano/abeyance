/* stdintx HEADER */
/* lang=C20 */

/* extended integer types */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	STDINTX_INCLUDE
#define	STDINTX_INCLUDE


#include	<envstandards.h>	/* MUST be first to configure */
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<stdint.h>


/* non-constants */

#ifndef	TYPEDEF_INT128
#define	TYPEDEF_INT128
typedef __int128		int128_t ;
#endif /* TYPEDEF_INT128 */

#ifndef	TYPEDEF_UINT128
#define	TYPEDEF_UINT128
typedef unsigned __int128	uint128_t ;
#endif /* TYPEDEF_UINT128 */

#ifndef	TYPEDEF_LONGLONG
#define	TYPEDEF_LONGLONG
typedef __int128		longlong ;
#endif /* TYPEDEF_LONGLONG */

#ifndef	TYPEDEF_ULONGLONG
#define	TYPEDEF_ULONGLONG
typedef unsigned __int128	ulonglong ;
#endif /* TYPEDEF_ULONGLONG */

/* constants */

#ifndef	TYPEDEF_CLONGLONG
#define	TYPEDEF_CLONGLONG
typedef const longlong		clonglong ;
#endif

#ifndef	TYPEDEF_CULONGLONG
#define	TYPEDEF_CULONGLONG
typedef const ulonglong		culonglong ;
#endif

/* pointers */

#ifndef	TYPEDEF_LONGLONGP
#define	TYPEDEF_LONGLONGP
typedef __int128 *		longlongp ;
#endif /* TYPEDEF_LONGLONGP */

#ifndef	TYPEDEF_ULONGLONGP
#define	TYPEDEF_ULONGLONGP
typedef unsigned __int128 *	ulonglongp ;
#endif /* TYPEDEF_ULONGLONGP */

/* pointers-to-constant */

#ifndef	TYPEDEF_CLONGLONGP
#define	TYPEDEF_CLONGLONGP
typedef const longlong *	clonglongp ;
#endif

#ifndef	TYPEDEF_CULONGLONGP
#define	TYPEDEF_CULONGLONGP
typedef const ulonglong *	culonglongp ;
#endif

#ifdef	__cplusplus /* C++ only */

#include	<type_traits>
#include	<concepts>

template<typename T>
struct is_stdintx : std::false_type { } ;

template<>
struct is_stdintx<signed char> : std::true_type { } ;

template<>
struct is_stdintx<signed short> : std::true_type { } ;

template<>
struct is_stdintx<signed int> : std::true_type { } ;

template<>
struct is_stdintx<signed long> : std::true_type { } ;

template<>
struct is_stdintx<signed longlong> : std::true_type { } ;

template<>
struct is_stdintx<unsigned char> : std::true_type { } ;

template<>
struct is_stdintx<unsigned short> : std::true_type { } ;

template<>
struct is_stdintx<unsigned int> : std::true_type { } ;

template<>
struct is_stdintx<unsigned long> : std::true_type { } ;

template<>
struct is_stdintx<unsigned longlong> : std::true_type { } ;

template<typename T>
inline constexpr bool is_stdintx_v = is_stdintx<T>::value ;

template<typename T>
concept stdintx = is_stdintx<T>::value ;

#endif /* __cplusplus */


#endif /* STDINTX_INCLUDE */


