#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netdb.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#define MAXLINE 1024 
int main(){
char buffer[MAXLINE];
int sockfd,n;
socklen_t len;
struct sockaddr_in servaddr,cliaddr;
sockfd = socket(AF_INET,SOCK_DGRAM,0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(22000);
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
while(1){
len = sizeof(cliaddr);
n =recvfrom(sockfd,buffer,MAXLINE,0,(struct sockaddr*)&cliaddr,&len);
buffer[n] = '\0';
printf("\nClient's Message: %s\n", buffer);
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
return 0;
}
