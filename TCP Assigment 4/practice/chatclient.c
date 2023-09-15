#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<ctype.h>
int main(){
char sendline[100],recvline[100];
int sockfd;
struct sockaddr_in servaddr;
sockfd = socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(22000);
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   while(1){
   bzero(sendline,100);
   bzero(recvline,100);
   printf("Client: ");
   fgets(sendline,100,stdin);
   send(sockfd,sendline,strlen(sendline),0);
   recv(sockfd,recvline,100,0);
   printf("Server: %s",recvline);
   if(strcmp(recvline,"exit\n")==0){
   printf("Chat ended by server.\n");
   close(sockfd);
   return 0;
   }
   if(strcmp(sendline,"exit\n")==0){
   printf("Chat ended by client.\n");
   close(sockfd);
   return 0;
   }
}
return 0;
}
