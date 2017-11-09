#ifndef COMMSOCK_H
#define COMMSOCK_H
#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#elif _WIN32
#define _WINSOCKAPI_
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <Ws2tcpip.h>
#include <WinSock2.h>
#endif

#endif // COMMSOCK_H
