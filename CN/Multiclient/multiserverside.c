#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

void handle_client(int client_socket);

int main() {
    int server_socket, client_sockets[MAX_CLIENTS], client_count = 0;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("[-] Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Initialize server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(5566); // Choose any available port

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-] Bind error");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("[-] Listen error");
        exit(EXIT_FAILURE);
    }

    printf("[+] Server listening on port 5566\n");

    while (1) {
        // Accept a new connection
        client_sockets[client_count] = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        if (client_sockets[client_count] < 0) {
            perror("[-] Accept error");
            continue;
        }

        printf("[+] New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Create a new process to handle the client
        if (fork() == 0) {
            close(server_socket); // Child process doesn't need the listener

            // Handle the client
            handle_client(client_sockets[client_count]);

            close(client_sockets[client_count]);
            exit(EXIT_SUCCESS);
        } else {
            close(client_sockets[client_count]); // Parent process doesn't need the client socket
            client_count++;
        }
    }

    close(server_socket);

    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];

    while (1) {
        // Receive data from the client
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            printf("[-] Client disconnected.\n");
            break;
        }

        buffer[bytes_received] = '\0'; // Null-terminate the received data
        printf("Client: %s", buffer);

        // Send data back to the client
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, strlen(buffer), 0);
    }
}

