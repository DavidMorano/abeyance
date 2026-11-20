/*
 * Copyright (c) 1998 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef _ADAPTOR_H
#define	_ADAPTOR_H

#pragma ident	"@(#)adaptor.h	1.9	98/07/22 SMI"

/*
 * The API used by the BSD print protocol adaptor to glue the front end
 * request receiving code to the back end request fufilling code.
 */

#ifdef __cplusplus
extern "C" {
#endif

#define	ADAPTOR_PATH "/etc/print/bsd-adaptor,/usr/lib/print/bsd-adaptor"
#define	NS_KEY_ADAPTOR_PATH	"spooling-type-path"
#define	NS_KEY_ADAPTOR_NAME	"spooling-type"
#define	CASCADE			"cascade"
#define	LPSCHED			"lpsched"

extern	int  adaptor_available(cchar *printer);
extern	int  adaptor_spooler_available(cchar *printer);
extern	int  adaptor_spooler_accepting_jobs(cchar *printer);
extern  int  adaptor_client_access(cchar *printer, cchar *host);
extern  int  adaptor_restart_printer(cchar *printer);
extern  char *adaptor_temp_dir(cchar *printer, cchar *host);
extern  int  adaptor_submit_job(cchar *printer, cchar *host,
				char *cf, char **df_list);
extern  int  adaptor_show_queue(cchar *printer, FILE *ofp,
				const int type, char **list);
extern  int  adaptor_cancel_job(cchar *printer, FILE *ofp,
				cchar *user, cchar *host,
				char **list);

#ifdef __cplusplus
}
#endif

#endif /* _ADAPTOR_H */
