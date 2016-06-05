#include<stdio.h>
#include"Message.h"
#include"User.h"
#include"Screens.h"
#include"Category.h"
active_user = 0;
active_categ = 0;
active_msg = 0;
void intialize()
{
	FILE* ip = fopen("file.bin", "wb");
	BitVector user_bit[20];
	for (int i = 0; i < 20; i++)
		user_bit[i].status = 0;
	long pos = ftell(ip);
	printf("Initial:%d\n", pos);
	fwrite(user_bit, sizeof(BitVector), sizeof(user_bit) / sizeof(user_bit[0]), ip);
	pos = ftell(ip);
	printf("BitVector Users:%d\n", pos);
	BitVector categ_bit[100];
	for (int i = 0; i < 100; i++)
		categ_bit[i].status = 0;
	fwrite(categ_bit, sizeof(BitVector), sizeof(categ_bit) / sizeof(categ_bit[0]), ip);
	pos = ftell(ip);
	printf("BitVector Categories:%d\n", pos);
	User group;
	for (int i = 0; i < 20;i++)
		fwrite(&group, sizeof(User), 1, ip);
	pos = ftell(ip);
	printf("User:%d,sizeof User:%d\n", pos,sizeof(User));
	Category cat;
	for (int i = 0; i < 100; i++)
		fwrite(&cat, sizeof(Category), 1, ip);
	pos = ftell(ip);
	printf("Category:%d,sizeof Category:%d\n", pos, sizeof(Category));
	int number_msg=0;
	fwrite(&number_msg, sizeof(int), 1, ip);
	pos = ftell(ip);
	printf("Number of Messages: %d\n", pos);
	Message msg[500];
	for (int i = 0; i < 100; i++)
		fwrite(&msg, sizeof(Message), sizeof(msg)/sizeof(msg[0]), ip);
	pos = ftell(ip);
	printf("Message:%d,sizeof Message:%d\n", pos, sizeof(Message));
	fclose(ip);
}

void start()
{
	int ch;
	while (1)
	{
		system("cls");
		printf("\nWelcome to Message Server\n\n");
		printf("1.Login\n2.Register\n3.Exit\n");
		printf("Enter your Choice:");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			screen_login();
			break;
		case 2:
			screen_register();
			break;
		case 3:
			exit(0);
		default:
			printf("Invalid Option, Enter your correct Option\n\n");
		}
		
	}
}
void test_user()
{
	char a[15] = "bhargav";
	char b[15] = "password";
	//addUser(a, b);
	printf("%d\n", login(a, b));
	//deactivate(a, b);
}
void test_cat()
{
	char a[15] = "bhargav";
	char b[15] = "password";
	char c[20] = "Computers";
	printf("%d\n", login(a, b));
	//addCategory(c);
	loadCategory();
}
void test_msgs()
{
	char a[15] = "bhargav";
	char b[15] = "password";
	char c[20] = "Computers";
	printf("%d\n", login(a, b));
	//addCategory(c);
	loadCategory();
	//addMessage();
	loadMessages();
	view_msg();
	//addReply();
	//loadMessages();
}
int main()
{
	//intialize();
	start();
	return 0;
}