#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define LEN 4096

int main() {
        int sock = socket(AF_INET, SOCK_STREAM, 0x6);

        if(sock < 0) {
                perror("while creating socket");
                exit(-1);
        }

        struct sockaddr_in addr = {};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9000);
        inet_aton("192.168.80.131", &addr.sin_addr);

        int con = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        if(con < 0) {
                perror("while connect to remote host");
                exit(-1);
        }

        FILE* file = fopen("./main.cpp", "r");

        if(!file) {
                fprintf(stderr, "no such file or directory\n");
                exit(-1);
        }

        char buffer[LEN];
        memset(buffer, 0, LEN);
        int counter = 0;

        while( (buffer[counter] = getc(file)) != EOF) {
                counter++;
        }

        fclose(file);

        int res = send(sock, buffer, LEN, 0);
        if(res < 0) {
                perror("while sending data");
                exit(-1);
        } 

        close(sock);
}
