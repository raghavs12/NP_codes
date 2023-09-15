#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Error converting server IP address");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to the server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server. Type 'exit' to quit.\n");

    while (1) {
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);

        // Send the message to the server
        send(client_socket, buffer, strlen(buffer), 0);

        // Check if the client wants to exit
        if (strcmp(buffer, "exit\n") == 0) {
            printf("Disconnected from the server\n");
            break;
        }

        // Receive and print server's response
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_received <= 0) {
            perror("Error receiving data");
            break;
        }

        printf("Server: %s", buffer);
    }

    close(client_socket);
    return 0;
}

