#define NOMINMAX

#include <winsock2.h>
#include <algorithm>
#include <charconv>
#include <codecvt>
#include <cstring>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <filesystem>
#pragma comment(lib, "ws2_32.lib")

std::string UnicodeToUTF8(const std::wstring& wstr) {
	std::string ret;
	try {
		std::wstring_convert<std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.to_bytes(wstr);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return ret;
}

struct Instruction {
	std::string operation;
	std::string parameter;
};

class FtpClient {
public:
	FtpClient();
	virtual ~FtpClient();
	void start();

private:
	const int SERVER_PORT = 9999;
	const int BUFFER_SIZE = 4096;
	sockaddr_in serverChannel;
	std::string buffer;
	int serverSocket;
	int clientSocket;
	bool isConnected;
	std::filesystem::path path;
	bool getFile();
	bool putFile();
	bool acknowledge();
	bool sendRequest(Instruction& instruction);
	bool connectToHost(const std::string& hostName);
	bool getWorkDir();
};

FtpClient::FtpClient() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int ret;
	buffer.resize(BUFFER_SIZE, 0);

	// WinSock init
	wVersionRequested = MAKEWORD(2, 2);  // willing Winsock DLL version
	ret = WSAStartup(wVersionRequested, &wsaData);
	if (ret != 0) {
		std::cout << "WSAStarup() failed!" << std::endl;
	}

	// confirm Winsock DLL support version 2.2
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		std::cout << "Invalid Winsock version!" << std::endl;
	}
	isConnected = false;
}

void FtpClient::start() {
	Instruction instruction;
	std::cout << "This is FTP Server, you can enter <help> or <?> to get operating methods, or enter "
		"<quit> to exit"
		<< std::endl;
	while (true) {
		std::cin >> instruction.operation;
		std::wstring wtemp;
		instruction.parameter.clear();
		if (instruction.operation == "help" || instruction.operation == "<help>" || instruction.operation == "?" || instruction.operation == "<?>") {
			std::cout << "get [fileName] -- download file\n"
				<< "put [fileName] -- upload file\n"
				<< "ftp [ip] -- login ftp\n"
				<< "pwd -- display current directory ftp server working in\n"
				<< "ls -- list files and directories in current working directory\n"
				<< "cd [dir] -- move to target directory\n"
				<< "close -- close connection to ftp server\n"
				<< "quit -- exit client" << std::endl;
		}
		else if (instruction.operation == "get") {
			std::cin.get();
			std::getline(std::wcin, wtemp);
			if (wtemp[0] == '\"') {
				wtemp = wtemp.substr(1, wtemp.size() - 2);
			}
			instruction.parameter = UnicodeToUTF8(wtemp);
			if (!isConnected) {
				std::cout << "you haven't connected to any server!" << std::endl;
			}
			else {
				sendRequest(instruction);
			}
		}
		else if (instruction.operation == "put") {
			std::cin.get();
			std::getline(std::wcin, wtemp);
			if (wtemp[0] == '\"') {
				wtemp = wtemp.substr(1, wtemp.size() - 2);
			}
			instruction.parameter = UnicodeToUTF8(wtemp);
			if (!isConnected) {
				std::cout << "you haven't connected to any server!" << std::endl;
			}
			else {
				sendRequest(instruction);
			}
		}
		else if (instruction.operation == "ftp") {
			std::cin.get();
			std::getline(std::wcin, wtemp);
			if (wtemp[0] == '\"') {
				wtemp = wtemp.substr(1, wtemp.size() - 2);
			}
			instruction.parameter = UnicodeToUTF8(wtemp);
			if (!isConnected && connectToHost(instruction.parameter)) {
				isConnected = true;
			}
			else if (isConnected) {
				std::cout << "you have connected to a server\n"
					<< "please close connection before connecting to a new one" << std::endl;
			}
		}
		else if (instruction.operation == "pwd" || instruction.operation == "ls") {
			if (!isConnected) {
				std::cout << "you haven't connected to any server!" << std::endl;
			}
			else {
				sendRequest(instruction);
			}
		}
		else if (instruction.operation == "cd") {
			std::cin.get();
			std::getline(std::wcin, wtemp);
			if (wtemp[0] == '\"') {
				wtemp = wtemp.substr(1, wtemp.size() - 2);
			}
			instruction.parameter = UnicodeToUTF8(wtemp);
			if (!isConnected) {
				std::cout << "you haven't connected to any server!" << std::endl;
			}
			else {
				sendRequest(instruction);
			}
		}
		else if (instruction.operation == "close") {
			if (isConnected) {
				isConnected = false;
				send(clientSocket, instruction.operation.c_str(), instruction.operation.size(), 0);
				closesocket(clientSocket);
			}
			else {
				std::cout << "you haven't connected to any server!" << std::endl;
			}
		}
		else if (instruction.operation == "quit" || instruction.operation == "<quit>") {
			if (isConnected) {
				instruction.operation = "close";
				isConnected = false;
				send(clientSocket, instruction.operation.c_str(), instruction.operation.size(), 0);
				closesocket(clientSocket);
			}
			break;
		}
		else {
			std::cout << "unknown operation, please enter <help> or <?> to learn more" << std::endl;
		}
	}
}

bool FtpClient::connectToHost(const std::string& hostName) {
	// create socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket < 0) {
		std::cout << "cannot create socket" << std::endl;
		return false;
	}
	else {
		std::cout << "successfully create socket" << std::endl;
	}
	std::memset(&serverChannel, 0, sizeof(serverChannel));  // init to 0
	serverChannel.sin_family = AF_INET;                     // channel protocol family AF_INET
	serverChannel.sin_addr.S_un.S_addr = inet_addr(hostName.data());  // address
	serverChannel.sin_port = htons(SERVER_PORT);                      // server port

	// build connection
	serverSocket = connect(clientSocket, (sockaddr*)&serverChannel, sizeof(serverChannel));
	if (serverSocket < 0) {
		std::cout << "cannot connect to the host!" << std::endl;
		return false;
	}
	else {
		std::cout << "successfully connect to the host!" << std::endl;
		return true;
	}
}

bool FtpClient::sendRequest(Instruction& instruction) {
	std::string buf;
	if (instruction.parameter.empty()) {
		buf = instruction.operation;
	}
	else {
		buf = instruction.operation + " " + instruction.parameter;
	}
	int ret = send(clientSocket, buf.c_str(), buf.size(), 0);
	if (ret == SOCKET_ERROR) {
		std::cout << "request failed!" << std::endl;
		return false;
	}
	else {
		std::cout << "request success!" << std::endl;
		path = instruction.parameter;
		if (instruction.operation == "get") {
			if (getFile()) {
				std::cout << "successfully download!" << std::endl;
			}
			else {
				std::cout << "download failed!" << std::endl;
			}
		}
		else if (instruction.operation == "put") {
			if (putFile()) {
				std::cout << "successfully upload!" << std::endl;
			}
			else {
				std::cout << "upload failed!" << std::endl;
			}
		}
		else if (instruction.operation == "pwd" || instruction.operation == "ls") {
			if (!getWorkDir()) {
				std::cout << "get work directory failed!" << std::endl;
			}
		}
		else if (instruction.operation == "cd") {
			if (acknowledge()) {
				std::cout << "operation completed" << std::endl;
			}
			else {
				std::cout << "operation failed" << std::endl;
			}
		}
		else {
			return false;
		}
		return true;
	}
}

bool FtpClient::getFile() {
	std::fill(std::begin(buffer), std::end(buffer), 0);
	int ret;
	std::string length(40, 0);
	ret = recv(clientSocket, length.data(), length.size(), 0);
	if (ret == SOCKET_ERROR) {
		return false;
	}
	long long size = 0;
	std::from_chars(length.c_str(), length.c_str() + length.size(), size);
	std::ofstream out;
	std::filesystem::path name{ path.filename() };
	out.open(name, std::ios::binary);
	if (!out) {
		std::cout << "cannot save the file" << std::endl;
		return false;
	}
	while (size > 0) {
		ret = recv(clientSocket, buffer.data(), buffer.size(), 0);
		long long s = std::min(size, (long long)buffer.size());
		if (ret == SOCKET_ERROR) {
			out.close();
			return false;
		}
		else {
			out.write(buffer.c_str(), s);
		}
		size -= buffer.size();
	}
	out.close();
	return acknowledge();
}

bool FtpClient::putFile() {
	std::ifstream in;
	// open file
	in.open(path, std::ios::binary);
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
		in.close();
		return false;
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
			in.close();
			return false;
		}
	}
	in.close();
	return acknowledge();
}

bool FtpClient::getWorkDir() {
	std::fill(std::begin(buffer), std::end(buffer), 0);
	int ret;
	std::string length(40, 0);
	ret = recv(clientSocket, length.data(), length.size(), 0);
	if (ret == SOCKET_ERROR) {
		return false;
	}
	long long size = 0;
	std::from_chars(length.c_str(), length.c_str() + length.size(), size);

	while (size > 0) {
		ret = recv(clientSocket, buffer.data(), buffer.size(), 0);
		if (ret == SOCKET_ERROR) {
			return false;
		}
		else {
			std::cout << buffer;
		}
		size -= buffer.size();
	}
	return acknowledge();
}

bool FtpClient::acknowledge() {
	int ret = recv(clientSocket, buffer.data(), buffer.size(), 0);
	std::string buf;
	for (int i = 0; i < 3; i++) {
		buf += buffer[i];
	}
	if (ret > 0) {
		if (buf == "NAK") {
			return false;
		}
		else if (buf == "ACK") {
			return true;
		}
	}
	return false;
}

FtpClient::~FtpClient() {
	if (isConnected) {
		isConnected = false;
		std::string operation{ "close" };
		send(clientSocket, operation.c_str(), operation.size(), 0);
		closesocket(clientSocket);
	}
}

int main() {
	std::locale loc{ ".utf8" };
	std::locale::global(loc);
	std::wcin.imbue(loc);
	FtpClient c;
	c.start();
}