#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "q3status.h"

char* tokenize(char *vals){
	char delims[] = "\\";
	char *result = NULL;
	result = strtok(vals , delims );
	while( result != NULL ) {
		printf( "result is \"%s\"\n", result );
		return result;
		//    result = strtok( NULL, delims );
	}
return result;

}


q3stats_t* showinfo(char *data) {
	int nt = 0;
	char *p;
	q3stats_t* q3st = calloc(1,sizeof(q3stats_t));

	printf("size %ld",sizeof(q3stats_t));
	printf("%s\n",data);
	while((p = strchr(data, '\\'))) {
		*p = '\0';

		if (!strcmp(data, "dmflags")) {
			data = p + 1;
			q3st->dmflags=data;
			printf("dmflags %d\n",q3st->dmflags);
		} else if (!strcmp(data,"fraglimit")){
			data = p + 1;
			q3st->fraglimit=data;
			printf("fraglimit %d\n",q3st->fraglimit);
		} else if (!strcmp(data, "timelimit")) {
			data = p + 1;
			q3st->timelimit=data;
			printf("timelimit %d\n",q3st->timelimit);
		}else if (!strcmp(data, "sv_maxclients")) {
			data = p + 1;
			q3st->sv_maxclients=data;
		}else if (!strcmp(data, "sv_maxRate")) {
			data = p + 1;
			q3st->sv_maxRate=data;
		}else if (!strcmp(data, "sv_minPing")) {
			data = p + 1;
			q3st->sv_minPing=data;
		}else if (!strcmp(data, "sv_maxPing")) {
			data = p + 1;
			q3st->sv_maxPing=data;
		}else if (!strcmp(data, "sv_floodProtect")) {
			data = p + 1;
			q3st->sv_floodProtect=data;
			printf("%d\n",q3st->sv_floodProtect);
		}else if (!strcmp(data, "sv_allowDownload")) {
			data = p + 1;
			q3st->sv_allowDownload=data;
		}else if (!strcmp(data, "capturelimit")) {
			data = p + 1;
			q3st->capturelimit=data;
		}else if (!strcmp(data, "g_maxGameClients")) {
			data = p + 1;
			q3st->g_maxGameClients=data;
		}else if (!strcmp(data, "sv_hostname")) {
			data = p + 1;
			q3st->sv_hostname=data;
		}else if (!strcmp(data, "version")) {
			data = p + 1;
			q3st->version=data;
			//memcpy(q3st->version,data,strlen(data));
			printf("VERSION!!!!! %s\n",q3st->version);
		}else if (!strcmp(data, "g_gametype")) {
			data = p + 1;
			q3st->g_gametype=data;
		}else if (!strcmp(data, "protocol")) {
			data = p + 1;
			q3st->protocol=data;
		}else if (!strcmp(data, "mapname")) {
			data = p + 1;
			q3st->mapname=data;
			//memcpy(q3st->mapname,data,strlen(data));
			printf("mapname : %s\n",(q3st->mapname));
		}else if (!strcmp(data, "sv_privateClients")) {
			data = p + 1;
			q3st->sv_privateClients=data;
		}else if (!strcmp(data, "sv_allowAnonymous")) {
			data = p + 1;
			q3st->sv_allowAnonymous=data;
		}else if (!strcmp(data, "bot_minplayers")) {
			data = p + 1;
			q3st->bot_minplayers=data;
		}else if (!strcmp(data, "gamename")) {
			data = p + 1;
			q3st->gamename=data;
			//memcpy(q3st->gamename,data,strlen(data));
			printf("GAMENAME %s\n",q3st->gamename);
		}else if (!strcmp(data, "g_needpass")) {
			data = p + 1;
			q3st->g_needpass=data;
			printf("needpass %d\n",q3st->g_needpass);
		}
		//}//endof if(!nt)
		//else {
		//          printf("zzzz %s\n", data);
		//        nt = 0;
		//  }
		data = p + 1;

	}
	return q3st;

}
