#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

int main(){

int socket_id,enable_reuseaddr = 1;
char msg[2000];

struct sockaddr_in broadcastaddress,senderaddress;

socket_id = socket(AF_INET,SOCK_DGRAM,0);

setsockopt(socket_id,SOL_SOCKET,SO_REUSEADDR,&enable_reuseaddr,sizeof(enable_reuseaddr));

broadcastaddress.sin_family = AF_INET;
broadcastaddress.sin_addr.s_addr = inet_addr("192.168.43.129");
broadcastaddress.sin_port = htons(22000);

bind(socket_id,(struct sockaddr*)&broadcastaddress,sizeof(broadcastaddress));

printf("Waiting for incoming msg...\n");
recvfrom(socket_id,msg,2000,0,(struct sockaddr*)&senderaddress,sizeof(senderaddress));
printf("Broadcast Message:%s",msg); 
}
