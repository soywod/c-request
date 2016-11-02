#ifndef REQUEST_H
#define REQUEST_H

struct request;

struct request* reqNew();
char* reqParse(char* html, struct request* req);
char* reqGetMethod(struct request* req);
char* reqGetRoute(struct request* req);
char* reqGetProtocol(struct request* req);
char* reqGetBody(struct request* req);
char* reqGetRaw(struct request* req);
char* reqGetHeader(char* key, struct request* req);
void reqClose(struct request* req);

#endif
