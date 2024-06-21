// #include "ftpServer.h"

// ftpServer::ftpServer() {
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

//     // workDir初始化为当前路径
//     system("cd > tempFile");
//     std::ifstream in("tempFile", std::ifstream::in);
//     in >> workDir;
//     in.close();
// }

// bool ftpServer::start() {
//     int on = 1;

//     // 初始化服务器
//     memset(&serverChannel, 0, sizeof(serverChannel));
//     serverChannel.sin_family = AF_INET;
//     serverChannel.sin_addr.s_addr = htonl(INADDR_ANY);
//     serverChannel.sin_port = htons(SERVER_PORT);

//     // 创建套接字
//     this->serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if (serverSocket < 0) {
//         printf("cannot create socket\n");
//         return false;
//     } else
//         printf("successfully create socket\n");
//     setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

//     // 绑定
//     int b = bind(serverSocket, (sockaddr*)&serverChannel, sizeof(serverChannel));

//     if (b < 0) {
//         printf("bind error\n");
//         return false;
//     } else
//         printf("successfully bind\n");

//     // 监听
//     int l = listen(serverSocket, QUEUE_SIZE);
//     if (l < 0) {
//         printf("listen failed\n");
//         return false;
//     } else
//         printf("successfully listen\n");
//     int len = sizeof(serverChannel);

//     // 服务器等待连接
//     while (1) {
//         printf("waiting for connection...\n");

//         // 接受一个连接
//         clientSocket = accept(serverSocket, (sockaddr*)&serverChannel, &len);
//         if (clientSocket < 0) {
//             printf("accept failed\n");
//         } else {
//             printf("successfully connect\n");
//             while (1) {
//                 memset(buffer, 0, sizeof(buffer));
//                 int ret;
//                 ret = recv(clientSocket, buffer, BUFFER_SIZE, 0);
//                 if (ret == SOCKET_ERROR) {
//                     printf("receive failed\n");
//                 } else {
//                     char opt[50];
//                     printf("successfully receive\n");
//                     int i = 0, j = 0;
//                     printf("buffer = %s\n", buffer);
//                     while (buffer[i] != ' ' && buffer[i] != '\0') {
//                         opt[i] = buffer[i];
//                         i++;
//                     }
//                     opt[i] = '\0';
//                     if (buffer[i] != '\0') {
//                         i++;
//                     }
//                     while (buffer[i] != '\0') {
//                         name[j] = buffer[i];
//                         i++, j++;
//                     }
//                     name[j] = '\0';
//                     if (strcmp(opt, "get") == 0) {
//                         char ret[4];
//                         if (!sendFile()) {
//                             strcpy(ret, "NAK");
//                             send(clientSocket, ret, sizeof(ret), 0);
//                         } else {
//                             strcpy(ret, "ACK");
//                             send(clientSocket, ret, sizeof(ret), 0);
//                         }
//                     } else if (strcmp(opt, "put") == 0) {
//                         receiveFile();
//                     } else if (strcmp(opt, "pwd") == 0) {
//                         doPwd();
//                     } else if (strcmp(opt, "cd") == 0) {
//                         doCd();
//                     } else if (strcmp(opt, "close") == 0) {
//                         break;
//                     } else {
//                         printf("syntex error\n");
//                     }
//                 }
//             }
//         }
//     }
//     return true;
// }

// bool ftpServer::sendFile() {
//     std::ifstream in;
//     char path[100];
//     strcpy(path, workDir);
//     strcat(path, "\\");
//     strcat(path, name);
//     in.open(path, std::ios::binary);
//     if (!in) {
//         printf("cannot open the file\n");
//         return false;
//     }
//     memset(buffer, 0, sizeof(buffer));
//     in.seekg(0, std::ios_base::end);
//     int sp = in.tellg();
//     int total_size = 0;
//     int r;
//     char length[20];
//     sprintf(length, "%d", sp);
//     r = send(clientSocket, length, sizeof(length), 0);
//     if (r == SOCKET_ERROR) {
//         printf("send failed\n");
//         return false;
//     } else {
//         printf("send success\n");
//     }
//     while (sp > 0) {
//         in.clear();
//         in.seekg(total_size, std::ios_base::beg);
//         memset(buffer, 0, sizeof(buffer));
//         in.read(buffer, sizeof(buffer));
//         int size = sp < BUFFER_SIZE ? sp : BUFFER_SIZE;
//         total_size += size;
//         r = send(clientSocket, buffer, size, 0);
//         sp -= size;
//         if (r == SOCKET_ERROR) {
//             printf("send failed\n");
//             return false;
//         } else {
//             printf("send success\n");
//         }
//     }
//     in.close();
//     return true;
// }

// bool ftpServer::receiveFile() {
//     char path[100];
//     strcpy(path, workDir);
//     strcat(path, "\\");
//     strcat(path, name);
//     memset(buffer, 0, sizeof(buffer));
//     int ret;
//     char length[20];
//     ret = recv(clientSocket, length, sizeof(length), 0);
//     if (ret == SOCKET_ERROR) {
//         printf("receive failed\n");
//         return false;
//     } else {
//         printf("successfully receive\n");
//     }
//     int size = atoi(length);
//     std::ofstream out;
//     out.open(path, std::ios::binary);
//     if (!out) {
//         printf("cannot save the file\n");
//         return false;
//     }
//     while (size > 0) {
//         int s = size < BUFFER_SIZE ? size : BUFFER_SIZE;
//         ret = recv(clientSocket, buffer, BUFFER_SIZE, 0);
//         if (ret == SOCKET_ERROR) {
//             printf("receive failed\n");
//             break;
//         } else {
//             printf("successfully receive\n");
//             out.write(buffer, s);
//         }
//         size -= BUFFER_SIZE;
//     }
//     out.close();
//     return true;
// }

// bool ftpServer::doPwd() {
//     char temCMD[150];
//     memset(temCMD, 0, sizeof(temCMD));
//     strcat(temCMD, "echo ");
//     strcat(temCMD, workDir);
//     strcat(temCMD, " > tempFile");
//     system(temCMD);
//     memset(temCMD, 0, sizeof(temCMD));
//     strcat(temCMD, "dir /b ");
//     strcat(temCMD, workDir);
//     strcat(temCMD, " >> tempFile");
//     system(temCMD);
//     std::ifstream in("tempFile", std::fstream::in);
//     if (!in) {
//         printf("cannot open the file\n");
//         return false;
//     }
//     memset(buffer, 0, sizeof(buffer));
//     in.seekg(0, std::ios_base::end);
//     int sp = in.tellg();
//     int total_size = 0;
//     int r;
//     char length[20];
//     sprintf(length, "%d", sp);
//     r = send(clientSocket, length, sizeof(length), 0);
//     if (r == SOCKET_ERROR) {
//         printf("send failed\n");
//         return false;
//     } else {
//         printf("send success\n");
//     }
//     while (sp > 0) {
//         in.clear();
//         in.seekg(total_size, std::ios_base::beg);
//         memset(buffer, 0, sizeof(buffer));
//         in.read(buffer, sizeof(buffer));
//         int size = sp < BUFFER_SIZE ? sp : BUFFER_SIZE;
//         total_size += size;
//         printf("transfer size = %d\n", total_size);
//         r = send(clientSocket, buffer, size, 0);
//         sp -= size;
//         if (r == SOCKET_ERROR) {
//             printf("send failed\n");
//             return false;
//         } else {
//             printf("send success\n");
//         }
//     }
//     in.close();
//     return true;
// }

// bool ftpServer::isValidPath(char* path) {
//     char temCMD[100];
//     memset(temCMD, 0, sizeof(temCMD));
//     strcat(temCMD, "cd ");
//     strcat(temCMD, path);
//     int res = system(temCMD);
//     return res == 0;
// }

// bool ftpServer::doCd() {
//     for (int i = 0; name[i] != '\0'; ++i) {
//         if (name[i] == '/')
//             name[i] = '\\';
//     }
//     if (name[0] == '.' && name[1] == '.') {
//         char temDir[100];
//         strcpy(temDir, workDir);
//         for (int i = sizeof(temDir); i >= 0; --i) {
//             if (temDir[i] == '\\') {
//                 temDir[i] = '\0';
//                 break;
//             }
//         }
//         strcat(temDir, name + 2);
//         if (isValidPath(temDir)) {
//             strcpy(workDir, temDir);
//         } else {
//             return false;
//         }
//     } else if (name[0] == '.' && name[1] != '.') {
//         char temDir[100];
//         strcpy(temDir, workDir);
//         strcat(temDir, name + 1);
//         if (isValidPath(temDir)) {
//             strcpy(workDir, temDir);
//         } else {
//             return false;
//         }
//     } else if (name[1] == ':') {
//         if (isValidPath(name)) {
//             strcpy(workDir, name);
//         } else {
//             return false;
//         }

//     } else {
//         char temDir[100];
//         strcpy(temDir, workDir);
//         strcat(temDir, "\\");
//         strcat(temDir, name);
//         if (isValidPath(temDir)) {
//             strcpy(workDir, temDir);
//         } else {
//             return false;
//         }
//     }
//     return true;
// }

// int main() {
//     ftpServer f;
//     f.start();
// }