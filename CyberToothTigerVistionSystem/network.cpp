#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <cstring>

class networkclass {
    const char* IP;
    int sock, valread;
    
    char buffer[2048];


    

public: int setup(std::string ServerIP, int Serversock)
{
    IP = ServerIP.c_str();
    sock = Serversock;
    std::cout <<"IP:" << IP << ":" << sock << '\n';
    std::thread networkThread(network, ServerIP, sock);
    networkThread.detach();
}
int static network(std::string IP, int mysock)
    {
        int client_fd;
        int sock = mysock;
        while (1) {
            start:
            struct sockaddr_in serv_addr;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                printf("\n Socket creation error \n");
                goto start;
            }
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(sock);

            // Convert IPv4 and IPv6 addresses from text to binary form
            if (inet_pton(AF_INET, IP.c_str(), &serv_addr.sin_addr) <= 0) {
                printf("\nInvalid address/ Address not supported \n");
                std::cout << IP << ":" << sock << '\n';
                goto start;
            }

            if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
                printf("\nConnection Failed \n");
                std::cout << IP << ":" << sock <<'\n';
                goto start;
            }
            //send resive wait loop
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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

public: std::string teststring(std::string tosend) {
    std::string massage = "recived" + tosend + " and yeap i got it";
    return massage;
}

public: int myclose() {
        // closing the connected socket
        //close(client_fd);
        return 0;
    }
};