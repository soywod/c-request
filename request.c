#include <stdlib.h>
#include <string.h>

#include "request.h"
#include "string.h"
#include "node_modules/c-map/map.h"

typedef struct request
{
	char* method;
	char* route;
	char* protocol;
	char* raw;
	char* body;
	struct map* headers;
} R;

R* reqNew()
{
	R* req;
	req = malloc(sizeof(R));

	return req;
}

char* reqParse(char* raw, R* req)
{
	char *cursor, *key, *val;
	int cursorpos;

	req->raw = raw;
	req->headers = mapNew();

	// Set method
	cursorpos = charpos(raw, ' ');
	req->method = substr(raw, 0, cursorpos - 1);
	cursor = raw + cursorpos + 1;

	// Set route
	cursorpos = charpos(cursor, ' ');
	req->route = substr(cursor, 0, cursorpos - 1);
	cursor += cursorpos + 1;

	// Set protocol
	cursorpos = charpos(cursor, '\r');
	req->protocol = substr(cursor, 0, cursorpos - 1);
	cursor += cursorpos + 2;

	// Set headers
	while(*cursor != '\r')
	{
		cursorpos = charpos(cursor, ':');
		key = substr(cursor, 0, cursorpos - 1);
		cursor += cursorpos + 2;

		cursorpos = charpos(cursor, '\r');
		val = substr(cursor, 0, cursorpos - 1);
		cursor += cursorpos + 2;

		mapDynAdd(key, val, req->headers);
		free(key);
	}

	cursor += 2;
	req->body = substr(cursor, 0, strlen(cursor));

	return req->body;
}

char* reqGetMethod(R* req)
{
	return req->method;
}

char* reqGetRoute(R* req)
{
	return req->route;
}

char* reqGetProtocol(R* req)
{
	return req->protocol;
}

char* reqGetBody(R* req)
{
	return req->body;
}

char* reqGetRaw(R* req)
{
	return req->raw;
}

char* reqGetHeader(char* key, struct request* req)
{
	return mapGet(key, req->headers);
}

void reqClose(R* req)
{
	mapClose(req->headers);

	free(req->method);
	free(req->route);
	free(req->protocol);
	free(req->body);
	free(req);
}
