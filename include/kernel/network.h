#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

void net_init(void);
void net_ping(const char* ip);
void net_curl(const char* url);

#endif
