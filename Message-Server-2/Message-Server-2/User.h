#ifndef USER_H
#include<stdio.h>
typedef struct user
{
	char username[15];
	int num_cat;
	char password[15];
	long category[5];
	long offset;
}User;
#endif
void addUser(char* username, char* password);
int login(char* username, char* password);
int deactivate(char* username, char* password);