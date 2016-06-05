#include <Ws2tcpip.h>
#include <winsock2.h>
//winsock2.h is the header file to be included for winsock functions
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
/*
ws2_32.lib is the library file to be linked with the program to be able
to use winsock functions
*/
void initialise()
{
	WSADATA wsa;
	/*
	WSADATA structure which will hold additional information
	after winsock has been loaded
	*/
	printf("\nInitialising Winsock...\n\n");
	//The WSAStartup function is used to start or initialise winsock library
	unsigned short wVersionRequested = MAKEWORD(2, 2);
	//the version we want to load
	if (WSAStartup(wVersionRequested, &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return;
	}
	printf("Initialised.\n");
}
SOCKET create_socket()
{
	SOCKET s;
	/*
	Function socket() creates a socket and returns a socket descriptor
	which can be used in other network commands
	*/
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");
	return s;
}
void socket_server(char SERVER_IP[], int port)
{
	//Initialise Winsock
	initialise();
	//Create a TCP socket
	SOCKET socket = create_socket();
	//connect to server
	struct sockaddr_in server;
	//server.sin_addr.s_addr = inet_pton(SERVER_IP);
	inet_pton(AF_INET, SERVER_IP, &server.sin_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	//Connect to remote server
	if (connect(socket, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		printf("Connect error");
		return;
	}
	while (1)
	{
		char rec_buff[1024];
		char send_buff[1024];
		printf("Enter the Message:");
		fflush(stdin);
		fgets(send_buff, 1024, stdin);
		send(socket, send_buff, 1024, 0);
		recv(socket, rec_buff, 1024, 0);
		printf("Message Received from Server: %s\n\n", rec_buff);
	}
}
int main()
{
	char SERVER_IP[] = "192.168.43.69";
	int port = 9511;
	socket_server(SERVER_IP, port);
}