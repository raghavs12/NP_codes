#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#define MAXLINE 1024
int main(){
char sendline[MAXLINE],recvline[MAXLINE];
int sockfd,n;
socklen_t len;
struct sockaddr_in servaddr;
sockfd = socket(AF_INET,SOCK_DGRAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(22000);
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
while(1){
bzero(sendline,MAXLINE);
bzero(recvline,MAXLINE);
fgets(sendline,MAXLINE,stdin);
len = sizeof(servaddr);
sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
n = recvfrom(sockfd,recvline,MAXLINE,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
recvline[n] = 0;
printf("Echoing Back - %s",recvline);
}
close(sockfd);
}
