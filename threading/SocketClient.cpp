#include <SFML/Graphics.hpp>

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>



void Client() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "Caca");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		window.display();
	}

	// socket creation 
	SOCKET clientSocket; 
	clientSocket = INVALID_SOCKET; 
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Error at socket() :" << WSAGetLastError() << std::endl; 
		WSACleanup();
		return; 
	}
	else {
		std::cout << "socket is ok" << std::endl;
		
	}


	//connection to server
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(55555);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		std::cout << "Client: connect() - Failed to connect: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}
	else {
		std::cout << "Client: Connect() is OK!" << std::endl;
		std::cout << "Client: Can start sending and receiving data..." << std::endl;
	}




	// sending data 

	char buffer[200]; 
	printf("Entrer un message: "); 
	std::cin.getline(buffer, 200);
	int sbyteCount = send(clientSocket, buffer, 200, 0);
	if (sbyteCount == SOCKET_ERROR ) {
		std::cout << "Server send error : " << WSAGetLastError << std::endl; 
		return;
	}
	else {
		std::cout << "Server : sent" << sbyteCount << std::endl;
	}


	closesocket(clientSocket);

	return; 
}