#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _Q3_STATUS_H
#define	_Q3_STATUS_H 1



typedef struct {
	char* name;
	char* value;
	struct q3nameval *next;
}q3nameval;

typedef struct _q3statusresponse{

	char* challenge;
	char *version;
	char*  dmflags;
	char*  fraglimit;
	char*  timelimit;
	char*  g_gametype;
	char*  protocol;
	char* mapname;
	char*  sv_privateClients;
	char* sv_hostname;
	char*  sv_maxclients;
	char*  sv_minRate;
	char*   sv_maxRate;
	char*  sv_minPing;
	char*  sv_maxPing;
	char*  sv_floodProtect;
	char*  sv_allowDownload;
	char*  bot_minplayers;
	char* admin;
	char* email;
	char* www;
	char* gamename;
	char*  g_maxGameClients;
	char*  capturelimit;
	char*  g_needpass;


} q3statusresponse;

#define DEST_PORT 6666
#define DEST_ADDR "127.0.0.1"

typedef struct q3stats{

	char*  dmflags;
	char*  fraglimit;
	char*  timelimit;
	char*  sv_maxclients;
	char*  sv_maxRate;
	char*  sv_minPing;
	char*  sv_maxPing;
	char*  sv_floodProtect;
	char*  sv_allowDownload;
	char*  capturelimit;
	char*  g_maxGameClients;
	char *sv_hostname;
	char *version;
	char*  g_gametype;
	char*  protocol;
	char *mapname;
	char*  sv_privateClients;
	char*  sv_allowAnonymous;
	char*  bot_minplayers;
	char *gamename;
	char*  g_needpass;
	char*  sv_punkbuster;
	char *gameversion;
	char*  Players_Active;
	char*  server_ospauth;
}q3stats_t;

extern PGconn * pg_connect();
extern q3stats_t* showinfo(char *data);
extern int save_status(q3stats_t *q3stats,PGconn * conn);


#endif
