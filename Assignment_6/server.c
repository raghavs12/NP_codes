#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

int main(){

int socket_id,broad = 1;
char msg[2000];

struct sockaddr_in broadcastaddress;
socket_id = socket(AF_INET,SOCK_DGRAM,0);
broadcastaddress.sin_family = AF_INET;
broadcastaddress.sin_addr.s_addr = inet_addr("192.168.43.129 ");
broadcastaddress.sin_port = htons(22000);


setsockopt(socket_id,SOL_SOCKET,SO_BROADCAST,&broad,sizeof(broad));

bzero(msg,2000);
printf("Enter the broadcast message...\n");
fgets(msg,2000,stdin);
sendto(socket_id,msg,sizeof(msg),0,(struct sockaddr*)&broadcastaddress,sizeof(broadcastaddress));
}
