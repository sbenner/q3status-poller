
-- Drop table

-- DROP TABLE public.q3status;

CREATE TABLE public.q3status (
	id serial NOT NULL,
	dmflags int4 NULL,
	fraglimit int4 NULL,
	timelimit int4 NULL,
	sv_maxclients int4 NULL,
	sv_maxrate int4 NULL,
	sv_minping int4 NULL,
	sv_maxping int4 NULL,
	sv_floodprotect int4 NULL,
	sv_allowdownload int4 NULL,
	capturelimit int4 NULL,
	g_maxgameclients int4 NULL,
	sv_hostname varchar(100) NULL,
	"_version" varchar(100) NULL,
	g_gametype int4 NULL,
	protocol int4 NULL,
	mapname varchar(100) NULL,
	sv_privateclients int4 NULL,
	sv_allowanonymous int4 NULL,
	bot_minplayers int4 NULL,
	gamename varchar(100) NULL,
	g_needpass int4 NULL,
	sv_punkbuster int4 NULL,
	gameversion varchar(100) NULL,
	players_active int4 NULL,
	server_ospauth int4 NULL,
	ts timestamp NOT NULL DEFAULT now(),
	source_ip inet NULL,
	CONSTRAINT q3stats_pkey PRIMARY KEY (id)
);

