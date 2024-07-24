#pragma once

#include <winsock2.h>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

class ftpServer {
   private:
    enum { SERVER_PORT = 9999, BUFFER_SIZE = 4096, QUEUE_SIZE = 10 };
    char buffer[BUFFER_SIZE];
    sockaddr_in serverChannel;
    char name[50];
    char workDir[100];  // store like C:\Users MARK:字符串末没有斜线！！
    int serverSocket;   // socket
    int clientSocket;
    bool sendFile();
    bool receiveFile();
    bool doPwd();
    bool doCd();
    bool isValidPath(char* path);

   public:
    ftpServer();
    bool start();  // 开启服务器
};