#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 7070
#define BUF  1024

int main() {
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);
    if (bind(lfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind"); return 1;
    }
    listen(lfd, 5);
    signal(SIGCHLD, SIG_IGN);          /* no zombie children */
    printf("File server listening on port %d\n", PORT);

    for (;;) {
        int cfd = accept(lfd, (struct sockaddr *)&cli, &len);
        if (cfd < 0) continue;

        if (fork() == 0) {             /* child */
            close(lfd);
            char name[256], buf[BUF], msg[64];
            int n = recv(cfd, name, sizeof(name) - 1, 0);
            if (n < 0) n = 0;
            name[n] = '\0';
            name[strcspn(name, "\r\n")] = '\0';

            snprintf(msg, sizeof(msg), "Server PID: %d\n", getpid());
            send(cfd, msg, strlen(msg), 0);

            FILE *fp = fopen(name, "r");
            if (fp == NULL) {
                const char *err = "File not found\n";
                send(cfd, err, strlen(err), 0);
            } else {
                size_t r;
                while ((r = fread(buf, 1, BUF, fp)) > 0)
                    send(cfd, buf, r, 0);
                fclose(fp);
            }
            close(cfd);
            exit(0);
        }
        close(cfd);                    /* parent */
    }
}
