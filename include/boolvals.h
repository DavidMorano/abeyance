/* boolvals HEADER */
/* encoding=ISO8859-1 */
/* lang=C20 */

#if	(! defined(false)) && (! defined(true))

enum truthvals {
	false,		/* <- = intx(0) */
	true,		/* <- = intx(1) */
	overlast	/* <- = intx(2) */
} ;

#endif /* */

#ifndef	false
#define	false		0
#endif

#ifndef	true
#define	true		1
#endif


