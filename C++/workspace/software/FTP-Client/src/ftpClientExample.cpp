// #include "ftpClient.h"

// ftpClient::ftpClient() {
//     WORD wVersionRequested;
//     WSADATA wsaData;
//     int ret;

//     // WinSock初始化：
//     wVersionRequested = MAKEWORD(2, 2);  // 希望使用的WinSock DLL的版本
//     ret = WSAStartup(wVersionRequested, &wsaData);
//     if (ret != 0) {
//         printf("WSAStartup() failed!\n");
//     }

//     // 确认WinSock DLL支持版本2.2：
//     if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
//         WSACleanup();
//         printf("Invalid Winsock version!\n");
//     }
//     isConnect = false;
// }

// void ftpClient::start() {
//     char c[100];
//     char d[100];
//     printf("这里是FTP客户端, 您可以输入help查看操作方法, 输入quit退出客户端\n");
//     while (1) {
//         scanf("%s", c);
//         if (strcmp(c, "help") == 0) {
//             printf(
//                 "get [fileName] -- 下载文件\n"
//                 "put [fileName] -- 上传文件\n"
//                 "ftp [ip] -- 登录FTP\n"
//                 "pwd -- 显示服务器当前工作文件夹\n"
//                 "cd [dirName] -- 更改当前文件夹\n"
//                 "close -- 关闭与当前ftp的连接\n"
//                 "quit -- 退出客户端\n");
//             fflush(stdout);
//         } else if (strcmp(c, "get") == 0) {
//             scanf("%s", d);
//             strcat(c, " ");
//             strcat(c, d);
//             if (!isConnect) {
//                 printf("you haven't connected to any server!\n");
//             } else
//                 sendRequest(c);
//         } else if (strcmp(c, "put") == 0) {
//             scanf("%s", d);
//             strcat(c, " ");
//             strcat(c, d);
//             if (!isConnect) {
//                 printf("you haven't connected to any server!\n");
//             } else
//                 sendRequest(c);
//         } else if (strcmp(c, "ftp") == 0) {
//             scanf("%s", d);
//             if (!isConnect && connect2Host(d)) {
//                 isConnect = true;
//             } else if (isConnect) {
//                 printf(
//                     "you have already connected to server\n"
//                     "please close the connection before connect to a new server\n");
//             }
//         } else if (strcmp(c, "pwd") == 0) {
//             if (!isConnect) {
//                 printf("you haven't connected to any server!\n");
//             } else
//                 sendRequest(c);
//         } else if (strcmp(c, "cd") == 0) {
//             scanf("%s", d);
//             strcat(c, " ");
//             strcat(c, d);
//             if (!isConnect) {
//                 printf("you haven't connected to any server!\n");
//             } else
//                 sendRequest(c);
//         } else if (strcmp(c, "quit") == 0) {
//             if (isConnect) {
//                 strcpy(c, "close");
//                 isConnect = false;
//                 send(clientSocket, c, strlen(c) + 1, 0);
//                 closesocket(clientSocket);
//             }
//             break;
//         } else if (strcmp(c, "close") == 0) {
//             if (isConnect) {
//                 isConnect = false;
//                 send(clientSocket, c, strlen(c) + 1, 0);
//                 closesocket(clientSocket);
//             }
//         } else {
//             printf("syntex error\n");
//         }
//     }
// }

// bool ftpClient::connect2Host(const char* hostName) {
//     // 创建socket
//     clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if (clientSocket < 0) {
//         printf("cannot create socket\n");
//         return false;
//     } else
//         printf("successfully create socket\n");
//     memset(&serverChannel, 0, sizeof(serverChannel));          // 初始化为0
//     serverChannel.sin_family = AF_INET;                        // channel协议家族AF_INET
//     serverChannel.sin_addr.S_un.S_addr = inet_addr(hostName);  // 地址
//     serverChannel.sin_port = htons(SERVER_PORT);               // 服务器端口

//     // 建立连接
//     serverSocket = connect(clientSocket, (sockaddr*)&serverChannel, sizeof(serverChannel));
//     if (serverSocket < 0) {
//         printf("cannot connect to the host\n");
//         return false;
//     } else {
//         printf("successfully connect to the host\n");
//         return true;
//     }
// }

// bool ftpClient::sendRequest(char* instruction) {
//     int r = send(clientSocket, instruction, strlen(instruction) + 1, 0);
//     if (r == SOCKET_ERROR) {
//         printf("request failed\n");
//         return false;
//     } else {
//         printf("request success\n");
//         char opt[5];
//         int i = 0, j = 0;
//         while (instruction[i] != ' ' && instruction[i] != '\0') {
//             opt[i] = instruction[i];
//             i++;
//         }
//         opt[i] = '\0';
//         i++;
//         while (instruction[i] != '\0') {
//             name[j] = instruction[i];
//             i++, j++;
//         }
//         name[j] = '\0';
//         if (strcmp(opt, "get") == 0) {
//             if (getFile()) {
//                 printf("successfully download\n");
//             } else
//                 printf("download failed\n");
//         } else if (strcmp(opt, "put") == 0) {
//             if (putFile()) {
//                 printf("successfully upload\n");
//             } else
//                 printf("upload failed\n");
//         } else if (strcmp(opt, "pwd") == 0) {
//             if (!getWorkDir())
//                 printf("get work directory failed\n");
//         } else if (strcmp(opt, "cd") == 0) {
//             printf("operation finished\n");
//         } else {
//             printf("syntex error\n");
//             return false;
//         }
//         return true;
//     }
// }

// bool ftpClient::getFile() {
//     memset(buffer, 0, sizeof(buffer));
//     int ret;
//     char length[20];
//     ret = recv(clientSocket, length, sizeof(length), 0);
//     if (ret == SOCKET_ERROR) {
//         return false;
//     } else if (strcmp(length, "NAK") == 0) {
//         return false;
//     }
//     int size = atoi(length);
//     std::ofstream out;
//     out.open(name, std::ios::binary);
//     if (!out) {
//         printf("cannot save the file\n");
//         return false;
//     }
//     while (size > 0) {
//         ret = recv(clientSocket, buffer, BUFFER_SIZE, 0);
//         int s = size < BUFFER_SIZE ? size : BUFFER_SIZE;
//         if (ret == SOCKET_ERROR) {
//             out.close();
//             return false;
//         } else if (strcmp(buffer, "NAK") == 0) {
//             out.close();
//             return false;
//         } else {
//             out.write(buffer, s);
//         }
//         size -= BUFFER_SIZE;
//     }
//     out.close();
//     return acknowledge();
// }

// bool ftpClient::putFile() {
//     std::ifstream in;

//     // 打开文件
//     in.open(name, std::ios::binary);
//     if (!in) {
//         printf("cannot open the file\n");
//         return false;
//     }
//     memset(buffer, 0, sizeof(buffer));

//     // 得到文件的字节数
//     in.seekg(0, std::ios_base::end);
//     int sp = in.tellg();
//     int total_size = 0;
//     int r;
//     char length[20];
//     sprintf(length, "%d", sp);

//     // 发送字节
//     r = send(clientSocket, length, sizeof(length), 0);
//     if (r == SOCKET_ERROR) {
//         return false;
//     }
//     while (sp > 0) {
//         in.clear();
//         in.seekg(total_size, std::ios_base::beg);
//         memset(buffer, 0, sizeof(buffer));

//         // 读取文件
//         in.read(buffer, sizeof(buffer));
//         int size = sp < BUFFER_SIZE ? sp : BUFFER_SIZE;
//         total_size += size;

//         // 发送文件
//         r = send(clientSocket, buffer, size, 0);
//         sp -= size;
//         if (r == SOCKET_ERROR) {
//             in.close();
//             return false;
//         }
//     }
//     in.close();
//     return true;
// }

// bool ftpClient::getWorkDir() {
//     printf("getWorkDir\n");
//     memset(buffer, 0, sizeof(buffer));
//     int ret;
//     char length[20];
//     ret = recv(clientSocket, length, sizeof(length), 0);
//     if (ret == SOCKET_ERROR) {
//         return false;
//     }
//     int size = atoi(length);
//     while (size > 0) {
//         ret = recv(clientSocket, buffer, BUFFER_SIZE, 0);
//         if (ret == SOCKET_ERROR) {
//             return false;
//         } else {
//             printf("%s", buffer);
//         }
//         size -= BUFFER_SIZE;
//     }
//     return true;
// }

// bool ftpClient::acknowledge() {
//     int ret = recv(clientSocket, buffer, BUFFER_SIZE, 0);
//     if (ret > 0) {
//         if (strcmp(buffer, "NAK") == 0)
//             return false;
//         else if (strcmp(buffer, "ACK") == 0)
//             return true;
//     }
//     return false;
// }

// ftpClient::~ftpClient() {
//     if (isConnect) {
//         isConnect = false;
//         char c[6];
//         strcpy(c, "close");
//         send(clientSocket, c, strlen(c) + 1, 0);
//         closesocket(clientSocket);
//     }
// }

// int main() {
//     ftpClient a;
//     a.start();
// }