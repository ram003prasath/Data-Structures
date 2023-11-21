#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {

    int client_socket;

    struct sockaddr_in server_addr;

    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) {

        perror("[-] Socket creation error");

        exit(EXIT_FAILURE);

    }
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the server's IP address

    server_addr.sin_port = htons(5566);

    // Connect to the server

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {

        perror("[-] Connection error");

        exit(EXIT_FAILURE);

    }

    printf("[+] Connected to the server\n");

    // Start chatting

    while (1) {

        printf("Client: ");

        fgets(buffer, sizeof(buffer), stdin);

        // Send data to the server

        send(client_socket, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit\n") == 0) {

            break;

        }

        // Receive data from the server

        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_received <= 0) {

            printf("[-] Server disconnected.\n");

            break;

        }

        buffer[bytes_received] = '\0'; // Null-terminate the received data

        printf("Server: %s", buffer);

    }

    close(client_socket);

    return 0;

}
