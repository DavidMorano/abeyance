/* cleanup */


/* users who can cleanup (remove files from) the messages spool area */

static cchar	*cleanup_users[] = {
	"root",
	"special",
	"daemon",
	"sys",
	"adm",
	"admin",
	"uucp",
	"nuucp",
	"listen",
	"news",
	"pcs",
	"dam",
	NULL
} ;

static cchar	*cleanup_groups[] = {
	"pcs",
	"sys",
	"staff",
	"adm",
	NULL
} ;


