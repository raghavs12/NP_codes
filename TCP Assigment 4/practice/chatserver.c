#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
int main(){
char str[100];
int sockfd,commfd;
struct sockaddr_in servaddr;
sockfd = socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(22000);
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
listen(sockfd,10);
printf("Chat server is running \n");
while(1){
commfd = accept(sockfd,(struct sockaddr*)NULL,NULL);
   while(1){
   bzero(str,100);
   recv(commfd,str,sizeof(str),0);
   printf("Client: %s",str);
   if(strcmp(str,"exit\n") ==0){
   printf("Chat ended by client");
   close(commfd);
   close(sockfd);
   }
   bzero(str,100);
   printf("Server: ");
   fgets(str,sizeof(str),stdin);
   send(commfd,str,strlen(str),0);
   if(strcmp(str,"exit\n")==0){
   printf("Chat ended by server.\n");
   close(commfd);
   close(sockfd);
   return 0;
   }
   };
};
return 0;
}




