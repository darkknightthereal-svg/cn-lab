#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUF  2048

struct pair { const char *abbr; const char *full; };
struct pair table[] = {
    {"tbh",  "to be honest"},     {"ig",   "I guess"},
    {"tbf",  "to be fair"},       {"atm",  "at the moment"},
    {"irl",  "in real life"},     {"lol",  "laughing out loud"},
    {"asap", "as soon as possible"}, {"omg", "oh my God"},
    {"ttyl", "talk to you later"},{"idk",  "I don't know"},
    {"nvm",  "never mind"},       {"idc",  "I don't care"}
};
#define N (sizeof(table) / sizeof(table[0]))

const char *lookup(const char *w) {
    for (size_t i = 0; i < N; i++)
        if (strcasecmp(w, table[i].abbr) == 0)
            return table[i].full;
    return NULL;
}

/* Copy non-letters as they are; replace whole words found in the table */
void translate(const char *in, char *out) {
    int i = 0, o = 0;
    while (in[i]) {
        if (isalpha((unsigned char)in[i])) {
            char w[64]; int k = 0;
            while (isalpha((unsigned char)in[i]) && k < 63)
                w[k++] = in[i++];
            w[k] = '\0';
            const char *r = lookup(w);
            const char *s = r ? r : w;
            while (*s) out[o++] = *s++;
        } else {
            out[o++] = in[i++];
        }
    }
    out[o] = '\0';
}

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);
    char in[BUF], out[BUF * 4];

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);
    if (bind(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind"); return 1;
    }
    printf("Translator server listening on port %d\n", PORT);

    for (;;) {
        int n = recvfrom(sock, in, BUF - 1, 0, (struct sockaddr *)&cli, &len);
        if (n < 0) continue;
        in[n] = '\0';
        in[strcspn(in, "\r\n")] = '\0';
        translate(in, out);
        printf("Received  : %s\nTranslated: %s\n", in, out);
        sendto(sock, out, strlen(out), 0, (struct sockaddr *)&cli, len);
    }
}
