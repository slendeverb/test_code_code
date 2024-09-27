#include "header.h"

// 目标地址
#define IP "127.0.0.1"
// 线程个数
#define THREADCOUNT 6400
DWORD WINAPI ThreadProc(LPVOID lpParameter);
// 端口号
int PortNum = 0;
// 临界区变量
CRITICAL_SECTION cs;

// 线程函数
DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    // 创建套接字
    SOCKET TryConnect;
    while (1) {
        if (PortNum > 65535) {
            break;
        }
        // 进入临界区
        EnterCriticalSection(&cs);
        int tmpport = PortNum;
        PortNum++;
        // DWORD threadID=GetCurrentThreadId();
        // printf("线程%d正在检测端口%d\n",threadID,PortNum);//所有使用临界区资源的代码都要加锁
        // 离开临界区
        LeaveCriticalSection(&cs);

        TryConnect = socket(AF_INET, SOCK_STREAM, 0);
        if (INVALID_SOCKET == TryConnect) {
            printf("Invalid socket.\n");
        }
        // 尝试连接
        sockaddr_in addrMe = {0};
        addrMe.sin_family = AF_INET;

        addrMe.sin_port = htons(tmpport);
        addrMe.sin_addr.S_un.S_addr = inet_addr(IP);
        int retCon = connect(TryConnect, (sockaddr*)&addrMe, sizeof(sockaddr_in));
        if (SOCKET_ERROR != retCon) {
            printf("检测到目标主机开放%d端口\n", tmpport);
        }
        closesocket(TryConnect);  // 防止开启太多socket连接，导致后面socket分配无效
    }
    return 0;
}

int main(int argc, char** argv) {
    auto fp=freopen("../../out.txt","w",stdout);
    // 初始化套接字
    WSADATA ws;
    ::WSAStartup(MAKEWORD(2, 0), &ws);

    DWORD start = GetTickCount();
    // 初始化临界区
    InitializeCriticalSection(&cs);

    // 多线程扫描
    HANDLE hThread[THREADCOUNT];
    for (int i = 0; i < THREADCOUNT; i++) {
        hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)0, 0, NULL);
    }

    // 当thread数量超过64的处理
    int tempNumThreads = THREADCOUNT;
    int tempMax = 0;
    while (tempNumThreads >= MAXIMUM_WAIT_OBJECTS) {
        tempNumThreads -= MAXIMUM_WAIT_OBJECTS;
        WaitForMultipleObjects(MAXIMUM_WAIT_OBJECTS, &hThread[tempMax], false, INFINITE);
        tempMax += MAXIMUM_WAIT_OBJECTS;
    }
    WaitForMultipleObjects(tempNumThreads, &hThread[tempMax], false, INFINITE);

    // 删除临界区
    DeleteCriticalSection(&cs);

    DWORD end = GetTickCount();
    printf("use time(s):%f\n", (end - start) / 1000.0);
    fclose(fp);
    fp=nullptr;
}