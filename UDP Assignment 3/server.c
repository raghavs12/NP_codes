#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 1024

int main(int argc, char **argv) {
    int sockfd;
    int n;
    socklen_t len;
    char buffer[MAXLINE]; // Buffer to hold the received message
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(5035);

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind");
        close(sockfd);
        return 1;
    }

    printf("\n\nBound and Listening...\n");

    while (1) {
        printf("\n ");
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr*)&cliaddr, &len);
        buffer[n] = '\0';  // Add null-terminator to make it a proper C string

        printf("\nClient's Message: %s\n", buffer);

        // Check if the received message contains the word "exit"
        if (strstr(buffer, "exit") != NULL) {
            printf("Received 'exit' command. Closing the server socket.\n");
            break;
        }

        if (sendto(sockfd, buffer, n, 0, (struct sockaddr*)&cliaddr, len) == -1) {
            perror("sendto");
            close(sockfd);
            return 1;
        }
    }

    close(sockfd);
    return 0;
}
