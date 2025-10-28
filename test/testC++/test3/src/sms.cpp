// #include <Winsock2.h>

// #include <json/json.h>
// #include <shellapi.h>
// #include <wintoastlib.h>
// #include <fstream>
// #include <iostream>
// #include <regex>
// #include <sstream>
// #include <string>

// #include "encode_convert.h"

// class MyToastHandler : public WinToastLib::IWinToastHandler {
//    public:
//     void toastActivated() const {}
//     void toastActivated(int actionIndex) const {}
//     void toastActivated(std::wstring response) const {}

//     void toastDismissed(WinToastDismissalReason state) const {}
//     void toastFailed() const {}
// };

// // 提取第一个长度大于等于4的数字
// std::string extract_first_long_number(const std::string& text) {
//     std::string filtered_text = text;
//     std::regex pattern{R"(^(?:\d{4}|\d{6})$)"};
//     std::smatch match;

//     if (std::regex_search(filtered_text, match, pattern)) {
//         return match.str();
//     }
//     return "";
// }

// // 显示windows通知
// void show_toast_notification(const std::string& title, const std::string& message) {
//     if (!WinToastLib::WinToast::isCompatible()) {
//         std::cout << std::format("Your computer is not support WinToast\n");
//         return;
//     }

//     std::wstring wtitle = UTF8ToUnicode(title);
//     std::wstring wmessage;
//     bool first = true;
//     size_t prev = 0;
//     size_t pos = message.find(R"(\n)", prev);
//     while (pos != std::string::npos) {
//         if (!first) {
//             wmessage += L'\n';
//         }
//         wmessage += UTF8ToUnicode(message.substr(prev, pos - prev));
//         prev = pos + 2;
//         pos = pos = message.find(R"(\n)", prev);
//         first = false;
//     }
//     if (!first) {
//         wmessage += L'\n';
//     }
//     wmessage += UTF8ToUnicode(message.substr(prev));

//     WinToastLib::WinToast::instance()->setAppName(L"SMS");
//     WinToastLib::WinToast::instance()->setAppUserModelId(L"SMS验证码转发服务");
//     static bool initialized = false;
//     if (!initialized) {
//         WinToastLib::WinToast::instance()->setAppName(L"SMS");
//         WinToastLib::WinToast::instance()->setAppUserModelId(L"SMS验证码转发服务");
//         if (!WinToastLib::WinToast::instance()->initialize()) {
//             std::cout << std::format("WinToast initialize failed\n");
//             return;
//         }
//         initialized = true;
//     }
//     WinToastLib::WinToastTemplate toast(WinToastLib::WinToastTemplate::Text02);
//     toast.setTextField(wtitle, WinToastLib::WinToastTemplate::FirstLine);
//     toast.setTextField(wmessage, WinToastLib::WinToastTemplate::SecondLine);

//     WinToastLib::WinToast::instance()->showToast(toast, new MyToastHandler{});
// }

// // 复制验证码到剪贴板并显示通知
// std::string copy_verification_code(const std::string& text) {
//     std::string number = extract_first_long_number(text);

//     if (!number.empty()) {
//         if (OpenClipboard(NULL)) {
//             EmptyClipboard();

//             HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, number.size() + 1);
//             if (hGlobal != NULL) {
//                 char* pGlobal = (char*)GlobalLock(hGlobal);
//                 std::strcpy(pGlobal, number.c_str());
//                 GlobalUnlock(hGlobal);

//                 SetClipboardData(CF_TEXT, hGlobal);
//             }
//             CloseClipboard();
//         }
//         std::cout << std::format("已复制到剪贴板: {}\n", number);

//         // 显示通知
//         std::string notification_msg = std::format("验证码: {}", number);
//         if (text.size() > 3) {
//             notification_msg = text.substr(1, text.size() - 3);
//         }
//         show_toast_notification("复制成功", notification_msg);

//         return number;
//     } else {
//         std::cout << std::format("未找到符合条件的数字字符串\n");
//         show_toast_notification("复制失败", "请检查短信验证码");
//         return "";
//     }
// }

// bool receive_message(int port) {
//     WSADATA wsaData;
//     SOCKET server_socket, client_socket;
//     SOCKADDR_IN server_addr, client_addr;
//     int client_addr_size = sizeof(client_addr);
//     char buffer[1024];
//     int bytes_received;

//     // 初始化Winsock
//     if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//         std::cerr << std::format("WSAStartup failed: {}\n", WSAGetLastError());
//         return false;
//     }

//     // 创建socket
//     server_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if (server_socket == INVALID_SOCKET) {
//         std::cerr << std::format("Socket creation failed: {}\n", WSAGetLastError());
//         WSACleanup();
//         return false;
//     }

//     // 设置地址重用
//     int opt = 1;
//     if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
//         std::cerr << std::format("Setsockopt failed\n");
//         closesocket(server_socket);
//         WSACleanup();
//         return false;
//     }

//     // 绑定地址和端口
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
//     server_addr.sin_port = htons(port);

//     if (bind(server_socket, (SOCKADDR*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
//         std::cerr << std::format("Bind failed: {}\n", WSAGetLastError());
//         closesocket(server_socket);
//         WSACleanup();
//         return false;
//     }

//     // 开始监听
//     if (listen(server_socket, 5) == SOCKET_ERROR) {
//         std::cerr << std::format("Listen failed: {}\n", WSAGetLastError());
//         closesocket(server_socket);
//         WSACleanup();
//         return false;
//     }

//     std::cout << std::format("Server is listening on port {}...\n", port);

//     // 接受连接循环
//     while (true) {
//         client_socket = accept(server_socket, (SOCKADDR*)&client_addr, &client_addr_size);
//         if (client_socket == INVALID_SOCKET) {
//             std::cerr << std::format("Accept failed: {}\n", WSAGetLastError());
//             continue;
//         }

//         std::cout << std::format("Connect from {}:{}\n", inet_ntoa(client_addr.sin_addr),
//                                  ntohs(client_addr.sin_port));

//         // 接收数据
//         bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
//         if (bytes_received > 0) {
//             buffer[bytes_received] = '\0';
//             std::string text{buffer};
//             std::cout << std::format("Received Data: {}\n", text);
//             send(client_socket, "ACK", sizeof("ACK"), 0);

//             // 处理验证码
//             copy_verification_code(text);
//         }

//         closesocket(client_socket);
//     }

//     closesocket(server_socket);
//     WSACleanup();
//     return true;
// }

// int main() {
//     int port = 65432;
//     if (!receive_message(port)) {
//         return 1;
//     }
//     return 0;
// }