#ifndef COMMSOCK_H
#define COMMSOCK_H
#ifdef APPLI_LIN
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#ifdef APPLI_WIN
#include <sys/types.h>
#include <winsock2.h>
#endif

#endif // COMMSOCK_H
