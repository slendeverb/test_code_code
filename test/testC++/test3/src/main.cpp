#include <iostream>
#include <Winsock2.h>
#include <string>
#include <fstream>
#include <json/json.h>
#include "utils.h"

bool receive_message(int port){
    WSADATA wsaData;
    SOCKET server_socket,client_socket;
    SOCKADDR_IN server_addr,client_addr;
    int client_addr_size=sizeof(client_addr);
    char buffer[1024];
    int bytes_received;

    // 初始化Winsock
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        std::cerr<<std::format("WSAStartup failed: {}\n",WSAGetLastError());
        return false;
    }

    // 创建socket
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket==INVALID_SOCKET){
        std::cerr<<std::format("Socket creation failed: {}\n",WSAGetLastError());
        WSACleanup();
        return false;
    }

    // 设置地址重用
    int opt=1;
    if(setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt))<0){
        std::cerr<<std::format("Setsockopt failed\n");
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    // 绑定地址和端口
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.S_un.S_addr=INADDR_ANY;
    server_addr.sin_port=htons(port);

    if(bind(server_socket,(SOCKADDR*)&server_addr,sizeof(server_addr))==SOCKET_ERROR){
        std::cerr<<std::format("Bind failed: {}\n",WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    // 开始监听
    if(listen(server_socket,5)==SOCKET_ERROR){
        std::cerr<<std::format("Listen failed: {}\n",WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    std::cout<<std::format("Server is listening on port {}...\n",port);

    // 接受连接循环
    while(true){
        client_socket=accept(server_socket,(SOCKADDR*)&client_addr,&client_addr_size);
        if(client_socket==INVALID_SOCKET){
            std::cerr<<std::format("Accept failed: {}\n",WSAGetLastError());
            continue;
        }

        std::cout<<std::format("Connect from {}:{}\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        // 接收数据
        bytes_received=recv(client_socket,buffer,sizeof(buffer)-1,0);
        if(bytes_received>0){
            buffer[bytes_received]='\0';
            std::string text{buffer};
            std::cout<<std::format("Received Data: {}\n",text);
            send(client_socket,"ACK",sizeof("ACK"),0);

            // 处理验证码
            copy_verification_code(text);
        }

        closesocket(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return true;
}

int main() {
    int port=65432;
    if(!receive_message(port)){
        return 1;
    }
    return 0;
}