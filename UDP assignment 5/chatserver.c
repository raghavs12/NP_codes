#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
int sockfd;
socklen_t len;
char buffer[100];
struct sockaddr_in servaddr,clientaddr;
sockfd = socket(AF_INET,SOCK_DGRAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(22000);
bind(sockfd,(struct sockaddr*)&servaddr, sizeof(servaddr));
while(1){
len = sizeof(clientaddr);
bzero(buffer,sizeof(buffer));
recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&clientaddr,&len);
printf("Client: %s",buffer);
if(strcmp(buffer,"exit\n") ==0){
printf("chat ended by client\n");
close(sockfd);
return 0;
}
bzero(buffer,100);
printf("Server: ");
fgets(buffer,sizeof(buffer),stdin);
sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&clientaddr,len);
if(strcmp(buffer,"exit\n")==0){
printf("Chat ended by server.\n");
close(sockfd);
return 0;
};
}
return 0;
}
