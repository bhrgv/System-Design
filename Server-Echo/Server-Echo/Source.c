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
char* statement(int x, int y)
{
	char* stmt = (char*)malloc(20 * sizeof(char));
	stmt[0] = 'x';
	stmt[1] = ':';
	stmt[2] = ' ';
	int j = 3;
	char num1[5];
	char num2[5];
	sprintf(num1, "%d", x);
	sprintf(num2, "%d", y);
	int i = 0;
	char c = num1[i++];
	while (c != '\0')
	{
		stmt[j++] = c;
		c = num1[i++];
	}
	stmt[j++] = ' ';
	stmt[j++] = 'y';
	stmt[j++] = ':';
	i = 0;
	c = num2[i++];
	while (c != '\0')
	{
		stmt[j++] = c;
		c = num2[i++];
	}
	stmt[j] = '\0';
	return stmt;
}
void findPath(int** maze, int x1, int y1, int x2, int y2, int m, int n,int acceptid)
{
	if (maze[x1][y1] == 0)
		return;
	if (x1 == x2 && y1 == y2)
	{
		maze[x1][y1] = -1;
		char* stmt = statement(x1, y1);
		send(acceptid, stmt, 1024, 0);
		free(stmt);
		return;
	}
	int i;
	int flag = 0;
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			if (x1 - 1 >= 0)
			{
				if (maze[x1 - 1][y1] == 1)
				{
					maze[x1][y1] = 0;
					findPath(maze, x1 - 1, y1, x2, y2, m, n,acceptid);
					if (maze[x1 - 1][y1] == -1)
						flag = 1;
				}
			}
			break;
		case 1:
			if (x1 + 1 < m)
			{
				if (maze[x1 + 1][y1] == 1)
				{
					maze[x1][y1] = 0;
					findPath(maze, x1 + 1, y1, x2, y2, m, n,acceptid);
					if (maze[x1 + 1][y1] == -1)
						flag = 1;
				}
			}
			break;
		case 2:
			if (y1 + 1 < n)
			{
				if (maze[x1][y1 + 1] == 1)
				{
					maze[x1][y1] = 0;
					findPath(maze, x1, y1 + 1, x2, y2, m, n,acceptid);
					if (maze[x1][y1 + 1] == -1)
						flag = 1;
				}
			}
			break;
		case 3:
			if (y1 - 1 >= 0)
			{
				if (maze[x1][y1 - 1] == 1)
				{
					maze[x1][y1] = 0;
					findPath(maze, x1, y1 - 1, x2, y2, m, n,acceptid);
					if (maze[x1][y1 - 1] == -1)
						flag = 1;
				}
			}
			break;
		}
		if (flag == 1)
		{
			char* stmt=statement(x1, y1);
			send(acceptid, stmt, 1024, 0);
			free(stmt);
			maze[x1][y1] = -1;
			break;
		}
	}
}
void readFile(char* str,int acceptid)
{
	int k = 0;
	char c = str[k++];
	int d = 0;
	while (c != ' ')
	{
		d = ((int)c - 48) + d * 10;
		c = str[k++];
	}
	int m = d;
	d = 0;
	while (c == ' ')
		c = str[k++];
	while (c != '\n')
	{
		d = ((int)c - 48) + d * 10;
		c = str[k++];
	}
	int n = d;
	c = str[k++];
	int** maze;
	maze = (int**)malloc(m*sizeof(int));
	int i,j;
	for (i = 0; i < m; i++)
		maze[i] = (int*)malloc(n*sizeof(int));
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			maze[i][j] = (int)c - 48;
			c = str[k++];
			while (c == ' ')
				c = str[k++];
		}
		while (c != '\n')
			c = str[k++];
		c = str[k++];
	}
	d = 0;
	while (c != ' ')
	{
		d = ((int)c - 48) + d * 10;
		c = str[k++];
	}
	int x1 = d;
	d = 0;
	while (c == ' ')
		c = str[k++];
	while (c != '\n')
	{
		d = ((int)c - 48) + d * 10;
		c = str[k++];
	}
	int y1 = d;
	c = str[k++];
	d = 0;
	while (c != ' ')
	{
		d = ((int)c - 48) + d * 10;
		c = str[k++];
	}
	int x2 = d;
	d = 0;
	while (c == ' ')
		c = str[k++];
	while (c!='\n')
	{
		d = ((int)c - 48) + d * 10;
		c = str[k++];
	}
	int y2 = d;
	findPath(maze, x1, y1, x2, y2, m, n,acceptid);
}
DWORD WINAPI service(int acceptid)
{
	char rec_buff[1024];
	recv(acceptid, rec_buff, 1024, 0);
	readFile(rec_buff,acceptid);
	strcpy(rec_buff, "end");
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