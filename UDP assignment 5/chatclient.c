#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
int sockfd;
char sendline[100];
char recvline[100];
struct sockaddr_in servaddr;
sockfd = socket(AF_INET,SOCK_DGRAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(22000);
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

while(1){
bzero(sendline,100);
bzero(recvline,100);
printf("Client: ");
fgets(sendline,100,stdin);
sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(strcmp(sendline,"exit\n")==0){
printf("Chat ended by client.\n");
close(sockfd);
return 0;
}
socklen_t len = sizeof(servaddr);
recvfrom(sockfd,recvline,100,0,(struct sockaddr*)&servaddr,&len);
printf("Server: %s",recvline);

if(strcmp(recvline,"exit\n")==0){
printf("Chat ended by server.\n");
close(sockfd);
return 0;
}
}
return 0;
}
