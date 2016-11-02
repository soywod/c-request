#include <stdio.h>

#include "request.h"

int main()
{
	struct request* req;
	char* raw = "GET / HTTP/1.1\r\nUser-Agent: curl/7.38.0\r\nHost: localhost:8080\r\nAccept: */*\r\n\r\nHello world !";

	req = reqNew();
	reqParse(raw, req);
	
	printf("Method: %s\n", reqGetMethod(req));
	printf("Route: %s\n", reqGetRoute(req));
	printf("Protocol: %s\n", reqGetProtocol(req));
	printf("User-Agent: %s\n", reqGetHeader("User-Agent", req));
	printf("Body: %s\n", reqGetBody(req));
	printf("Raw http request: %s\n", reqGetRaw(req));

	reqClose(req);
	return 0;
}
