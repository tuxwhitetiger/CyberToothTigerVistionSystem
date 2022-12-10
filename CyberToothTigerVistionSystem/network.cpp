#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 9090

const char* IP = "127.0.0.1";
int sock = 0, valread, client_fd;
struct sockaddr_in serv_addr;
char buffer[1024] = { 0 };

int network()
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -2;
    }
    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))< 0) {
        printf("\nConnection Failed \n");
        return -3;
    }
    return 0;
}

int sendstring(char* tosend, char* reply) {
    send(sock, tosend, strlen(tosend), 0);
    printf("Hello message sent\n");
    valread = read(sock, reply, 1024);
    printf("%s\n", reply);
    return 0;
}

int close() {
    // closing the connected socket
    close(client_fd);
    return 0;
}
