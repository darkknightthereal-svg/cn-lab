#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);
    char req[64], reply[256];

    signal(SIGCHLD, SIG_IGN);          /* no zombie children */

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);
    if (bind(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind"); return 1;
    }
    printf("Time server listening on port %d\n", PORT);

    for (;;) {
        int n = recvfrom(sock, req, sizeof(req) - 1, 0,
                         (struct sockaddr *)&cli, &len);
        if (n < 0) continue;
        req[n] = '\0';

        if (fork() == 0) {             /* child serves this request */
            time_t t = time(NULL);
            snprintf(reply, sizeof(reply), "%s(served by PID %d)",
                     ctime(&t), getpid());
            sendto(sock, reply, strlen(reply), 0,
                   (struct sockaddr *)&cli, len);
            close(sock);
            exit(0);
        }
        /* parent loops back to recvfrom() */
    }
}
