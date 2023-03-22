#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/types.h>
#include <sys/ioctl.h>

#define INT "eth0"

int main() {
        int sock = socket(AF_INET, SOCK_DGRAM, 0);

        if(sock < 0) {
                perror("while creating raw socket");
                exit(-1);
        }

        struct ifreq ip;
        memset(&ip, 0, sizeof(ip));

        strncpy(ip.ifr_name, INT, IFNAMSIZ-1);

        if((ioctl(sock, SIOCGIFADDR, &ip)) < 0) {
                perror("While grabing our own ip");
                exit(-1);
        }

        struct sockaddr_in* ipaddr = (struct sockaddr_in*)(&ip.ifr_addr);
        printf("%s\n", inet_ntoa(ipaddr->sin_addr));

        close(sock);
}