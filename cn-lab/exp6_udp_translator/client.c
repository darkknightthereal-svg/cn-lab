#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUF  8192

int main(int argc, char *argv[]) {
    const char *ip = (argc > 1) ? argv[1] : "127.0.0.1";
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv;
    char msg[2048], reply[BUF];

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &serv.sin_addr);

    printf("Enter sentence: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    sendto(sock, msg, strlen(msg), 0, (struct sockaddr *)&serv, sizeof(serv));
    int n = recvfrom(sock, reply, BUF - 1, 0, NULL, NULL);
    reply[n] = '\0';
    printf("Translated    : %s\n", reply);
    close(sock);
    return 0;
}
