#include<stdio.h>
#include"User.h"
#include"Category.h"
#include<string.h>
void addUser(char* username, char* password)
{
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, 0, SEEK_SET);
	BitVector users[20];
	fread(users, sizeof(BitVector), 20, ip);
	int i;
	for (i = 0; i < 20; i++)
		if (users[i].status == 0)
			break;
	if (i == 20)
	{
		printf("\nNo More Space for Users\n");
		return;
	}
	User user;
	strcpy(user.username,username);
	strcpy(user.password,password);
	user.num_cat = 0;
	user.offset = i * 60 + 480;
	users[i].status = 1;
	fseek(ip, 0, SEEK_SET);
	fwrite(users, sizeof(BitVector), 20, ip);
	fseek(ip, user.offset, SEEK_SET);
	fwrite(&user, sizeof(User), 1, ip);
	fclose(ip);
	printf("User has been Added\n");
	//pause(5000);
}
int login(char* username, char* password)
{
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, 0, SEEK_SET);
	BitVector users[20];
	fread(users, sizeof(BitVector), 20, ip);
	int i;
	User user;
	for (i = 0; i < 20; i++)
	{
		if (users[i].status == 1)
		{
			int pos = i * 60 + 480;
			fseek(ip, pos, SEEK_SET);
			fread(&user, sizeof(User), 1, ip);
			if (!strcmp(username, user.username) && !strcmp(password,user.password))
			{
				active_user = user.offset;
				return user.offset;
			}
		}
	}
	return 0;
}
int deactivate(char* username, char* password)
{
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, 0, SEEK_SET);
	BitVector users[20];
	fread(users, sizeof(BitVector), 20, ip);
	int i;
	User user;
	for (i = 0; i < 20; i++)
	{
		if (users[i].status == 1)
		{
			int pos = i * 60 + 480;
			fseek(ip, pos, SEEK_SET);
			fread(&user, sizeof(User), 1, ip);
			if (!strcmp(username, user.username))
			{
				users[i].status = 0;
				break;
			}
		}
	}
	if (i == 20)
	{
		return 0;
	}
	fseek(ip, 0, SEEK_SET);
	fwrite(users, sizeof(BitVector), 20, ip);
	return 1;
}