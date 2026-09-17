/* getua */

/* user-attribute database access */


#ifndef	GETUA_INCLUDE
#define	GETUA_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<user_attr.h>


EXTERNC_begin

extern int getua_begin() ;
extern int getua_ent(userattr_t *,char *,int) ;
extern int getua_end() ;
extern int getua_name(userattr_t *,char *,int,const char *) ;
extern int getua_uid(userattr_t *,char *,int,uid_t) ;

EXTERNC_end


#endif /* GETUA_INCLUDE */


