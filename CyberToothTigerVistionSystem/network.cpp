#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>

class networkclass {
    const char* IP;
    int sock, valread, client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
public: int setup(const char* ServerIP, int Serversock)
{
    IP = ServerIP;
    sock = Serversock;
}
public: int main()
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(sock);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, IP, &serv_addr.sin_addr)
            <= 0) {
            printf(
                "\nInvalid address/ Address not supported \n");
            return -2;
        }

        if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
            printf("\nConnection Failed \n");
            return -3;
        }
        return 0;
    }

public: int sendstring(char* tosend, char* reply) {
        send(sock, tosend, strlen(tosend), 0);
        printf("Hello message sent\n");
        valread = read(sock, reply, 1024);
        printf("%s\n", reply);
        return 0;
    }
public: int teststring(std::string tosend, std::string reply) {
    std::string massage = "recived" + tosend + " and yeap i got it";
    reply = massage;
    return 0;
}

public: int myclose() {
        // closing the connected socket
        close(client_fd);
        return 0;
    }
};