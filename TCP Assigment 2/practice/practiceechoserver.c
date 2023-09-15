#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

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
     commfd = accept(sockfd,(struct sockaddr*)NULL,NULL);
 while(1){
           bzero(str,100);
           recv(commfd,str,100,0);
            if(strcmp(str,"exit\n") ==0 || strcmp(str,"Exit\n")==0){ 
            close(commfd);
            break;
            }
            else{
            printf("Echoing back - %s",str);
            send(commfd,str,strlen(str),0);
            }
 }
return 0;
}
