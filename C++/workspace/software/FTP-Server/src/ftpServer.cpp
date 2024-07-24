#define NOMINMAX

#include <direct.h>
#include <winsock2.h>

#include <algorithm>
#include <charconv>
#include <codecvt>
#include <cstring>
#include <cwchar>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <sstream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

struct Instruction {
	std::string operation;
	std::string parameter;
};

class FtpServer {
public:
	FtpServer();
	bool start();  // open server
private:
	const int SERVER_PORT = 9999;
	const int BUFFER_SIZE = 4096;
	const int QUEUE_SIZE = 10;
	std::string buffer;
	sockaddr_in serverChannel;
	std::filesystem::path path;
	std::filesystem::path workDir;
	int serverSocket;
	int clientSocket;
	bool sendFile();
	bool receiveFile();
	bool doPwd();
	bool doLs();
	bool doCd(const std::filesystem::path& path);
	bool isValidPath(const std::filesystem::path& path);
	bool ftpSend(std::istream& in);
	bool ftpReceive(std::ostream& out);
};

FtpServer::FtpServer() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int ret;
	buffer.resize(BUFFER_SIZE, 0);

	// Winsock init
	wVersionRequested = MAKEWORD(2, 2);  // willing Winsock DLL version
	ret = WSAStartup(wVersionRequested, &wsaData);
	if (ret != 0) {
		std::cout << "WSAStartip() failed!" << std::endl;
	}

	// confirm Winsock DLL support version 2.2
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		std::cout << "Invalid Winsock version!" << std::endl;
	}

	// init workDir to current path
	workDir = std::filesystem::current_path();
}

bool FtpServer::start() {
	int on = 1;
	// init server
	std::memset(&serverChannel, 0, sizeof(serverChannel));
	serverChannel.sin_family = AF_INET;
	serverChannel.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverChannel.sin_port = htons(SERVER_PORT);

	// create socket
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket < 0) {
		std::cout << "cannot create socket" << std::endl;
		return false;
	}
	else {
		std::cout << "successfully create socket" << std::endl;
	}
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

	// bind
	int b = bind(serverSocket, (sockaddr*)&serverChannel, sizeof(serverChannel));
	if (b < 0) {
		std::cout << "bind error" << std::endl;
		return false;
	}
	else {
		std::cout << "successfully bind" << std::endl;
	}

	// listen
	int l = listen(serverSocket, QUEUE_SIZE);
	if (l < 0) {
		std::cout << "listen failed" << std::endl;
		return false;
	}
	else {
		std::cout << "successfully listen" << std::endl;
	}
	int len = sizeof(serverChannel);

	// server wait for connection
	while (true) {
		std::cout << "waiting for connection..." << std::endl;

		// accept a connection
		clientSocket = accept(serverSocket, (sockaddr*)&serverChannel, &len);
		if (clientSocket < 0) {
			std::cout << "accept failed" << std::endl;
		}
		else {
			std::cout << "successfully connect" << std::endl;
			while (true) {
				std::fill(std::begin(buffer), std::end(buffer), 0);
				int ret = recv(clientSocket, buffer.data(), buffer.size(), 0);
				if (ret == SOCKET_ERROR) {
					std::cout << "receive failed" << std::endl;
				}
				else {
					std::cout << "successfully receive" << std::endl;
					Instruction instruction;
					std::cout << "buffer = " << buffer << "\n";
					int i = 0;
					while (buffer[i] != ' ' && buffer[i] != '\0') {
						instruction.operation += buffer[i];
						i++;
					}
					i++;
					while (buffer[i] != '\0') {
						instruction.parameter += buffer[i];
						i++;
					}
					path = instruction.parameter;
					std::string ret(4, 0);
					if (instruction.operation == "get") {
						if (!sendFile()) {
							ret = "NAK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
						else {
							ret = "ACK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
					}
					else if (instruction.operation == "put") {
						if (!receiveFile()) {
							ret = "NAK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
						else {
							ret = "ACK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
					}
					else if (instruction.operation == "pwd") {
						if (!doPwd()) {
							ret = "NAK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
						else {
							ret = "ACK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
					}
					else if (instruction.operation == "ls") {
						if (!doLs()) {
							ret = "NAK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
						else {
							ret = "ACK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
					}
					else if (instruction.operation == "cd") {
						if (!doCd(path)) {
							ret = "NAK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
						else {
							ret = "ACK";
							send(clientSocket, ret.c_str(), ret.size(), 0);
						}
					}
					else if (instruction.operation == "close") {
						break;
					}
					else {
						std::cout << "unknown operation, please enter <help> to learn more"
							<< std::endl;
					}
				}
			}
		}
	}
	return true;
}

bool FtpServer::ftpSend(std::istream& in) {
	if (!in) {
		std::cout << "cannot open the file" << std::endl;
		return false;
	}
	std::fill(std::begin(buffer), std::end(buffer), 0);

	// get file bytes
	in.seekg(0, std::ios_base::end);
	long long sp = in.tellg();
	long long total_size = 0;
	int ret;
	std::string length(40, 0);
	std::to_chars(length.data(), length.data() + length.size(), sp);

	// send bytes
	ret = send(clientSocket, length.c_str(), length.size(), 0);
	if (ret == SOCKET_ERROR) {
		std::cout << "send failed" << std::endl;
		return false;
	}
	else {
		std::cout << "send success" << std::endl;
	}
	while (sp > 0) {
		in.clear();
		in.seekg(total_size, std::ios_base::beg);
		std::fill(std::begin(buffer), std::end(buffer), 0);

		// read file
		in.read(buffer.data(), buffer.size());
		long long size = std::min(sp, (long long)buffer.size());
		total_size += size;

		// send file
		ret = send(clientSocket, buffer.c_str(), buffer.size(), 0);
		sp -= size;
		if (ret == SOCKET_ERROR) {
			std::cout << "send failed" << std::endl;
			return false;
		}
		else {
			std::cout << "send success" << std::endl;
		}
	}
	return true;
}

bool FtpServer::ftpReceive(std::ostream& out) {
	std::fill(std::begin(buffer), std::end(buffer), 0);
	std::string length(40, 0);
	int ret = recv(clientSocket, length.data(), length.size(), 0);
	if (ret == SOCKET_ERROR) {
		std::cout << "receive failed" << std::endl;
		return false;
	}
	else {
		std::cout << "receive success" << std::endl;
	}
	long long size = 0;
	std::from_chars(length.c_str(), length.c_str() + length.size(), size);

	if (!out) {
		std::cout << "cannot save the file" << std::endl;
		return false;
	}
	while (size > 0) {
		ret = recv(clientSocket, buffer.data(), buffer.size(), 0);
		long long s = std::min(size, (long long)buffer.size());
		if (ret == SOCKET_ERROR) {
			std::cout << "receive failed" << std::endl;
			break;
		}
		else {
			std::cout << "receive success" << std::endl;
			out.write(buffer.c_str(), s);
		}
		size -= buffer.size();
	}
	return true;
}

bool FtpServer::sendFile() {
	std::filesystem::path filePath = workDir / path;
	std::ifstream in(filePath, std::ios::binary);
	return ftpSend(in);
}

bool FtpServer::receiveFile() {
	std::filesystem::path name{ path.filename() };
	std::filesystem::path filePath = workDir / name;
	std::ofstream out(filePath, std::ios::binary);
	return ftpReceive(out);
}

bool FtpServer::doPwd() {
	std::ostringstream out;
	out << workDir << "\n";
	std::istringstream in{ out.str() };
	return ftpSend(in);
}

bool FtpServer::doLs() {
	std::ostringstream out;
	for (const auto& file : std::filesystem::directory_iterator(workDir)) {
		out << file.path().filename() << "\n";
	}
	std::istringstream in{ out.str() };
	return ftpSend(in);
}

bool FtpServer::isValidPath(const std::filesystem::path& path) {
	return system(std::string("cd " + path.string()).c_str()) == 0;
}

bool FtpServer::doCd(const std::filesystem::path& path) {
	if (isValidPath(path)) {
		int res = _chdir(path.string().c_str());
		if (res == 0) {
			workDir = std::filesystem::current_path();
			return true;
		}
		else {
			std::cout << "invalid path" << std::endl;
			return false;
		}
	}
	else {
		std::cout << "invalid path" << std::endl;
		return false;
	}
}

int main() {
	std::locale::global(std::locale(".utf8"));
	FtpServer s;
	s.start();
}