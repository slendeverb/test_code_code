#include "header.h"

using namespace std;
#define STATUS_FALIED 0xFFFF
unsigned long serverIP;
long MaxThread = 200;
long ThreadCount = 0;
long* aa = &ThreadCount;

// 扫描端口的线程
DWORD WINAPI ScanPort(LPVOID lpParam) {
    short Port = *(short*)lpParam;
    InterlockedIncrement(aa);
    // 创建流式套接字
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cout << "创建套接字失败！" << endl;
        return 0;

    } else {
        // 填充服务器地址
        sockaddr_in severAddr;
        severAddr.sin_family = AF_INET;
        severAddr.sin_port = htons(Port);
        severAddr.sin_addr.S_un.S_addr = serverIP;
        // 判断此机器是否打开
        connect(sock, (sockaddr*)&severAddr, sizeof(severAddr));
        struct fd_set write;
        FD_ZERO(&write);
        FD_SET(sock, &write);
        // 初始化超时时间
        struct timeval timeout;
        timeout.tv_sec = 100 / 1000;
        timeout.tv_usec = 0;
        if (select(0, NULL, &write, NULL, &timeout) > 0) {
            cout << Port << ",";
        };
        closesocket(sock);
    }

    InterlockedDecrement(aa);
    return 0;
}

int main(int argc, char** argv) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        std::cout<<"WSAStartup failed! "<<GetLastError()<<std::endl;
        ExitProcess(STATUS_FALIED);
    }
    std::string ip="127.0.0.1";
    serverIP=inet_addr(ip.c_str());
    std::cout<<"下列端口已开放: "<<std::endl;
    for (int i=1;i<1024;i++){
        while (ThreadCount>=MaxThread){
            Sleep(10);
        }
        DWORD ThreadID;
        CreateThread(NULL,0,ScanPort,(LPVOID)std::make_unique<short>(i).get(),0,&ThreadID);
    }
    while (ThreadCount>0){
        Sleep(50);
    }
    WSACleanup();
}