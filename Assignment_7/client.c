#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#define MULTICAST_GROUP "239.0.0.1"
#define PORT 12345

int main(){
int sockfd;
struct sockaddr_in localAddr;
struct ip_mreq multicastRequest;
char buffer[1024];
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
int reuseAddr = 1;
setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr));


memset(&localAddr, 0, sizeof(localAddr));
localAddr.sin_family = AF_INET;
localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
localAddr.sin_port = htons(PORT);

bind(sockfd, (struct sockaddr*)&localAddr, sizeof(localAddr));

multicastRequest.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);

setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicastRequest, sizeof(multicastRequest));
ssize_t bytesRead = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);

printf("Received message: %s\n", buffer);

close(sockfd);
return 0;



}
