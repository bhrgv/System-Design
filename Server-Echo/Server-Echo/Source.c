#include <winsock2.h>
#include <Windows.h>
//winsock2.h is the header file to be included for winsock functions
#include <stdio.h>
#include<string.h>
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
DWORD WINAPI service(int acceptid)
{
	char rec_buff[1024];
	recv(acceptid, rec_buff, 1024, 0);
	send(acceptid, rec_buff, 1024, 0);
	return 0;
}
void socket_server(char SERVER_IP[],int port)
{
	//Initialise Winsock
	initialise();
	//Create a TCP socket
	SOCKET socket=create_socket();
	//connect to server
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	//Connect to remote server
	if (bind(socket, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		printf("Binding error");
		return;
	}
	if (listen(socket, 10) < 0)
	{
		printf("Listing Error\n");
		return;
	}
	printf("Server Ready to Listen\n");
	struct sockaddr_in sadr;
	int	addr_size = sizeof(SOCKADDR);
	while (1)
	{
		int acceptid = accept(socket, (SOCKADDR*)&sadr, &addr_size);
		if (acceptid == INVALID_SOCKET)
		{
			printf("Error Accepting\n\n");
			return;
		}
		HANDLE thread = CreateThread(NULL, 0, service,acceptid,0,NULL);
	}
}
int main()
{
	char SERVER_IP[] = "192.168.43.69";
	int port = 9511;
	socket_server(SERVER_IP,port);
}