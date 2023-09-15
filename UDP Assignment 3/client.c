#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#define MAXLINE 1024

int main(int argc, char* argv[]) {
int sockfd;
int n;
socklen_t len;
char sendline[MAXLINE], recvline[MAXLINE];
struct sockaddr_in servaddr;

sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd == -1) {
    perror("socket");
    return 1;
}

// Bind the socket to a specific address and port
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
servaddr.sin_port = htons(5035);
bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

while (1) {
    bzero(sendline,MAXLINE);
    bzero(recvline,MAXLINE);
    printf("\n Enter the message (or 'exit' to quit): ");
    scanf("%s", sendline);

    len = sizeof(servaddr);
    sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr*)&servaddr, len);

    n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr*)&servaddr, len);
    recvline[n] = 0;
    printf("Server's Echo : %s\n\n", recvline);
}

close(sockfd);
return 0;

}

