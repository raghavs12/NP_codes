#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_CONNECTIONS 10
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Chat server is listening on port %d...\n", PORT);

    // Accept incoming connections and handle them
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Error accepting client connection");
            continue;
        }

        printf("Client connected\n");

        // Create a child process to handle the client
        pid_t pid = fork();
        if (pid == -1) {
            perror("Error creating child process");
            close(client_socket);
            continue;
        }

        if (pid == 0) { // Child process
            close(server_socket); // Close the server socket in the child process
            char buffer[BUFFER_SIZE];

            while (1) {
                memset(buffer, 0, sizeof(buffer));
                int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

                if (bytes_received <= 0) {
                    perror("Error receiving data");
                    break;
                }

                printf("Client: %s", buffer);

                // Check if the client wants to exit
                if (strcmp(buffer, "exit\n") == 0) {
                    printf("Client disconnected\n");
                    break;
                }

                // Send a response
                printf("Server: ");
                fgets(buffer, sizeof(buffer), stdin);
                send(client_socket, buffer, strlen(buffer), 0);
            }

            close(client_socket);
            exit(0);
        } else { // Parent process
            close(client_socket); // Close the client socket in the parent process
        }
    }

    close(server_socket);
    return 0;
}

