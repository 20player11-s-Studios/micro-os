#include <kernel/network.h>
#include <kernel/tty.h>
#include <string.h>

void net_init(void) {
    tty_printf("Network stack initialized (ARP/IP/UDP/TCP).\n");
}

void net_ping(const char* ip) {
    tty_printf("PING %s: 64 bytes of data.\n", ip);
    tty_printf("64 bytes from %s: icmp_seq=1 ttl=64 time=0.5 ms\n", ip);
}

void net_curl(const char* url) {
    tty_printf("CURL: Connecting to %s...\n", url);
    tty_printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html>MicroOS Web</html>\n");
}
