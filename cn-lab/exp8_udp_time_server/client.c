#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090

int main(int argc, char *argv[]) {
    const char *ip = (argc > 1) ? argv[1] : "127.0.0.1";
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv;
    char reply[256];

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &serv.sin_addr);

    sendto(sock, "TIME", 4, 0, (struct sockaddr *)&serv, sizeof(serv));
    int n = recvfrom(sock, reply, sizeof(reply) - 1, 0, NULL, NULL);
    reply[n] = '\0';
    printf("Server time: %s\n", reply);
    close(sock);
    return 0;
}
