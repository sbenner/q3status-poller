#include <postgresql/libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "q3status.h"


#define UNUSED(x) (void)(x)

//static const char* user_phone_arr[][2] = {
//    { "user111", "phone111" },
//    { "user222", "phone222" },
//    { "user333", "phone333" },
//    { NULL, NULL }
//};

//static PGconn* conn = NULL;
//static PGresult* res = NULL;

static void
terminate(int code,PGresult* res,PGconn * conn)
{
	if(code != 0)
		fprintf(stderr, "%s\n", PQerrorMessage(conn));

	if(res != NULL)
		PQclear(res);

	if(conn != NULL)
		PQfinish(conn);

	exit(code);
}

static void
clearRes(PGresult* res)
{
	PQclear(res);
	res = NULL;
}

static void
processNotice(void *arg, const char *message)
{
	UNUSED(arg);
	UNUSED(message);

	// do nothing
}


PGconn * pg_connect(){

	int libpq_ver = PQlibVersion();
	printf("Version of libpq: %d\n", libpq_ver);

	PGconn *  conn = PQconnectdb("user=postgres password= host=127.0.0.1 dbname=postgres");
	if(PQstatus(conn) != CONNECTION_OK)
		terminate(1,NULL,conn);

	PQsetNoticeProcessor(conn, processNotice, NULL);

	int server_ver = PQserverVersion(conn);
	char *user = PQuser(conn);
	char *db_name = PQdb(conn);

	printf("Server version: %d\n", server_ver);
	printf("User: %s\n", user);
	printf("Database name: %s\n", db_name);



	return conn;

}

int
save_status(q3stats_t *q3stats,PGconn * conn)
{


	const char* query =
			"INSERT INTO q3status (\
dmflags , \
fraglimit , \
timelimit , \
sv_maxclients , \
sv_maxRate , \
sv_minPing , \
sv_maxPing ,  \
sv_floodProtect , \
sv_allowDownload , \
capturelimit , \
g_maxGameClients , \
sv_hostname , \
_version  , \
g_gametype , \
protocol , \
mapname , \
sv_privateClients , \
sv_allowAnonymous , \
bot_minplayers , \
gamename , \
g_needpass , \
sv_punkbuster , \
gameversion  , \
Players_Active , \
server_ospauth \
)  \
VALUES ($1::int4, $2::int4, $3::int4, $4::int4, \
$5::int4,$6::int4,$7::int4,$8::int4,  \
$9::int4,$10::int4,$11::int4,$12,  \
$13,$14::int4,  \
$15::int4,$16,$17::int4,$18::int4, \
$19::int4,$20,$21::int4,$22::int4, \
$23,$24::int4,$25::int4);";


	const char* params[25];

	//    for(int i = 0; ; i++)
	//    {
	//        const char* user = user_phone_arr[i][0];
	//        const char* phone = user_phone_arr[i][1];
	//        if(user == NULL || phone == NULL)
	//            break;


	params[0] = q3stats->dmflags;
	params[1] =  q3stats->fraglimit;
	params[2] =  q3stats->timelimit;
	params[3] =  q3stats->sv_maxclients ;
	params[4] =  q3stats->sv_maxRate ;
	params[5] =  q3stats->sv_minPing ;
	params[6] =  q3stats->sv_maxPing ;
	params[7] =  q3stats->sv_floodProtect;
	params[8] =  q3stats->sv_allowDownload;
	params[9] =  q3stats->capturelimit;
	params[10] =  q3stats->g_maxGameClients;

	params[11] =  q3stats->sv_hostname ;
	params[12] =  q3stats->version  ;

	params[13] =  q3stats->g_gametype ;
	params[14] =  q3stats->protocol ;
	params[15] =  q3stats->mapname ;
	params[16] =  q3stats->sv_privateClients;
	params[17] =  q3stats->sv_allowAnonymous ;
	params[18] =  q3stats->bot_minplayers ;
	params[19] =  q3stats->gamename ;
	params[20] =  q3stats->g_needpass ;
	params[21] = q3stats->sv_punkbuster;
	params[22] =  q3stats->gameversion;
	params[23] =  q3stats->Players_Active;
	params[24] =  q3stats->server_ospauth;


	PGresult * prep = PQprepare(conn,"insert",query,25,NULL);

	printf("PREP PQresStatus : %s\n",   PQresStatus(PQresultStatus(prep)));
	printf("PQresultErrorMessage : %s\n",   PQresultErrorMessage(prep));
	//
	//        PGresult *  res = PQexecParams(conn, query, 27,
	//        		NULL,
	//        		params,
	//        		NULL, NULL,
	//        		0);

	PGresult * res = PQexecPrepared(conn,
			"insert",
			25,
			params,
			NULL,
			0,
			0);

	printf("RES PQresStatus : %s\n",   PQresStatus(PQresultStatus(res)));
	printf("RES PQresultErrorMessage : %s\n",   PQresultErrorMessage(res));
	if(PQresultStatus(res) != PGRES_COMMAND_OK)
		terminate(1,res,conn);
	clearRes(res);


	res = PQexec(conn, "SELECT *  \
                       FROM public.q3status");

	if(PQresultStatus(res) != PGRES_TUPLES_OK)
		terminate(1,res,conn);

	int ncols = PQnfields(res);
	printf("There are %d columns:", ncols);
	for(int i = 0; i < ncols; i++)
	{
		char *name = PQfname(res, i);
		printf(" %s", name);
	}
	printf("\n");

	int nrows = PQntuples(res);
	for(int i = 0; i < nrows; i++)
	{
		char* id = PQgetvalue(res, i, 0);
		char* gameversion = PQgetvalue(res, i, 13);
		char* gamename = PQgetvalue(res, i, 22);

		printf("Id: %s, game: %s, gameversion: %s \n",
				id, gamename, gameversion);
	}

	printf("Total: %d rows\n", nrows);

	clearRes(res);
	//terminate(0,res,conn);
	return 0;
}
