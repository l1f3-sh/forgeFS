#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define port 9000
#define BACKLOG 1
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size;
    char buffer[BUFFER_SIZE];

    // create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    // set up sddress struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), 0, 0);

    //bind am
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("[+] Server started on port %d\n", port);

    //Accept connection
    sin_size = sizeof(struct sockaddr_in);
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &sin_size)) == -1) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("[+] Connection from %s\n", inet_ntoa(client_addr.sin_addr));

    //Send Welcome message
    char *message = "Welcome to ForgeFS!\n";
    send(client_fd, message, strlen(message), 0);

    //close sockets 
    close(client_fd);
    close(server_fd);

    printf("[+] Server shutdown.\n");
    return 0;
}
