#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>

#pragma comment(lib, "ws2_32.lib")

void Server(){
	
	
	//initialize Wsa variable 

	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	//check initialization success
	if (wsaerr != 0) {
		std::cout << "the Winsock dll not found" << std::endl;
		return;
	}
	else {
		std::cout << "The Winsock dll found" << std::endl;
		std::cout << "The status : " << wsaData.szSystemStatus << std::endl;

	}


	//Create a socket 
	SOCKET serverSocket;
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//check for socket creation succes 
	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}
	else {
		std::cout << "Socket is ok" << std::endl;
	}

	//bind the socket to an IP address and port number

	sockaddr_in service; 
	service.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &service.sin_addr.s_addr);
	service.sin_port = htons(8080); 


	if (bind(serverSocket, reinterpret_cast<SOCKADDR*> (&service), sizeof(service)) == SOCKET_ERROR) {
		std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return; 
	}
	else {
		std::cout << "bind() is ok" << std::endl;
	}

	//listen to incomming connections 
	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		std::cout << "listen(): Error listening on socket : " << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "listen() is ok, I'm waiting for new connections.. " << std::endl; 
	}


	// accepting incoming connections
	SOCKET acceptSocket; 
	acceptSocket = accept(serverSocket, NULL, NULL); 
	if (acceptSocket == INVALID_SOCKET) {
		std::cout << "accept failed : " << WSAGetLastError() << std::endl; 
		WSACleanup();
		return; 
	}
	else {
		std::cout << "accept() is ok " << std:: endl;
	}

	//reciving data 

	char receiveBuffer[200];
	int rbyteCount = recv(acceptSocket, receiveBuffer, 200, 0);
	if(rbyteCount < 0){
		std::cout << "Server recv error : " << WSAGetLastError() << std::endl; 
		return; 
	}
	else {
		std::cout << "Receive data : " << receiveBuffer << std::endl; 
	}


	//sending data 
	char buffer[200]; 
	printf("Enter the message : "); 
	std::cin.getline(buffer, 200);
	int sbyteCount = send(acceptSocket, buffer, 200, 0); 
	if (sbyteCount == SOCKET_ERROR) {
		std::cout << "Server send error: " << WSAGetLastError() << std::endl; 
		return;
	}
	else {
		std::cout << "Server : sent" << sbyteCount << std::endl;
	}


	closesocket(serverSocket);

	return;
}



