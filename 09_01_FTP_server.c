#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERV_TCP_PORT 5035
#define MAX 4096  // Increased buffer size for efficiency

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, clength;
    struct sockaddr_in serv_addr, cli_addr;
    char str[MAX], buff[MAX];
    FILE *f1;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Binding failed");
        close(sockfd);
        exit(1);
    }
    printf("Server started. Listening on port %d...\n", SERV_TCP_PORT);

    // Start listening for connections
    listen(sockfd, 5);
    clength = sizeof(cli_addr);

    // Accept client connection
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clength);
    if (newsockfd < 0) {
        perror("Accept failed");
        close(sockfd);
        exit(1);
    }
    printf("Client connected.\n");

    // Receive filename from client
    memset(str, 0, MAX);
    if (read(newsockfd, str, MAX) <= 0) {
        perror("Failed to read filename");
        close(newsockfd);
        close(sockfd);
        exit(1);
    }
    printf("Client requested file: %s\n", str);

    // Open the requested file
    f1 = fopen(str, "r");
    if (f1 == NULL) {
        perror("File not found");
        write(newsockfd, "File not found", 14);
    } else {
        // Read file and send contents to client
        while (fgets(buff, MAX, f1) != NULL) {
            write(newsockfd, buff, strlen(buff));  // Send actual data size
        }
        fclose(f1);
        printf("File transferred successfully.\n");
    }

    // Close sockets
    close(newsockfd);
    close(sockfd);
    return 0;
}
