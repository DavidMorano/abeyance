
/* missing library subroutines */

/* Copyright © 2017 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#if	(!defined(SYSHAS_STRNLEN)) || (SYSHAS_STRNLEN == 0)
#ifndef	SUBROUTINE_STRNLEN
#define	SUBROUTINE_STRNLEN
#ifdef	__cplusplus
extern "C" {
#endif
extern int	strnlen(cchar *,int) noex ;
#ifdef	__cplusplus
}
#endif
#endif /* SUBROUTINE_STRNLEN */
#endif /* defined(SYSHAS_STRNLEN) */

#if	(!defined(SYSHAS_STRLCPY)) || (SYSHAS_STRLCPY == 0)
#ifndef	SUBROUTINE_STRLCPY
#define	SUBROUTINE_STRLCPY
#ifdef	__cplusplus
extern "C" {
#endif
extern int	strlcpy(char *,cchar *,int) noex ;
#ifdef	__cplusplus
}
#endif
#endif /* SUBROUTINE_STRLCPY */
#endif /* defined(SYSHAS_STRLCPY) */


