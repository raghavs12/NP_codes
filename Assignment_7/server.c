#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#define MULTICAST_GROUP"239.0.0.1"
#define PORT 12345
int main(){
int sockfd,enableloop = 1;
struct sockaddr_in multicastAddr;
char buff[128];
printf("Input>");
fgets(buff,128,stdin);

sockfd = socket(AF_INET,SOCK_DGRAM,0);
memset(&multicastAddr,0,sizeof(multicastAddr));
multicastAddr.sin_family = AF_INET;
multicastAddr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
multicastAddr.sin_port = htons(PORT);


setsockopt(sockfd,IPPROTO_IP,IP_MULTICAST_LOOP,&enableloop,sizeof(enableloop));
sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&multicastAddr,sizeof(multicastAddr));
close(sockfd);

}
