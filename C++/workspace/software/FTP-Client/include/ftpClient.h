#pragma once

#include <winsock2.h>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

class ftpClient {
   private:
    enum { SERVER_PORT = 9999, BUFFER_SIZE = 4096 };
    sockaddr_in serverChannel;
    char buffer[BUFFER_SIZE];
    int serverSocket;
    int clientSocket;
    bool isConnect;
    char name[50];
    bool getFile();
    bool putFile();
    bool acknowledge();
    bool sendRequest(char* instruction);
    bool connect2Host(const char* hostName);
    bool getWorkDir();

   public:
    ftpClient();
    ~ftpClient();
    void start();
};