#include"Screens.h"
#include"Category.h"
#include"User.h"
#include"Message.h"
#include<stdio.h>
void screen_wall()
{
	printf("\nCategories for the Current User are:\n");
	loadCategory();
	if (active_categ != 0)
	{
		loadMessages();
		msg_option();
	}
	else
		printf("\nInvalid Category to Load\n");
}
void msg_option()
{
	int ch;
	while (1)
	{
		printf("\nSelect a Approriate Operation\n");
		printf("1.Add\n2.Refresh\n3.View Msg\n4.Delete\n5.Go Back\n");
		printf("Enter your Choice:");
		scanf("%d", &ch);
		system("cls");
		switch (ch)
		{
		case 1:
			addMessage();
			break;
		case 2:
			loadMessages();
			break;
		case 3:
			view_msg();
			reply_option();
			break;
		case 4:
			deleteMessage();
			break;
		case 5:
			return;
		default:
			printf("Invalid Option, Enter your correct Option\n\n");
		}
		
	}
}
void reply_option()
{
	int ch;
	while (1)
	{
		printf("\n\nReply For the Message\n");
		printf("\nSelect a Approriate Operation\n");
		printf("1.Add\n2.Delete\n3.Go Back\n");
		printf("Enter your Choice:");
		scanf("%d", &ch);
		system("cls");
		switch (ch)
		{
		case 1:
			addReply();
			break;
		case 2:
			deleteReply();
			break;
		case 3:
			return;
		default:
			printf("Invalid Option, Enter your correct Option\n\n");
		}
	}
}
void view_msg()
{
	printf("Enter the Message to be Viewed:");
	int ch;
	scanf("%d", &ch);
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, 3680, SEEK_SET);
	int num_msg;
	fread(&num_msg, sizeof(int), 1, ip);
	fseek(ip, active_categ, SEEK_SET);
	Category category;
	fread(&category, sizeof(Category), 1, ip);
	printf("Message is:\n\n");
	int count = 1;
	for (int i = 0; i < num_msg; i++)
	{
		Message msg;
		fseek(ip, i * 180 + 3684, SEEK_SET);
		fread(&msg, sizeof(Message), 1, ip);
		if (!strcmp(category.name, msg.cat) && msg.reply_id == 0)
		{
			if (count == ch)
			{
				printf("%d\n", count);
				printf("Sender : %s \n\n", msg.user);
				printf("Message :\n%s\n\n", msg.msg);
				active_msg = msg.offset;
				break;
			}
			count++;
		}
	}
	loadReplies();
	fclose(ip);
}
void screen_join()
{
	joinCategory();
}
void screen_create()
{
	printf("Enter the Category to add:");
	char name[20];
	fflush(stdin);
	fgets(name, 20, stdin);
	addCategory(name);
}
void screen_leave()
{
	printf("\nScreen Underconstruction -- Sorry for Inconvince\n");
}
void screen_login()
{
	printf("Enter exit to Close\n\n");
	printf("Enter the Username:\n");
	char username[15];
	fflush(stdin);
	fgets(username, 15, stdin);
	printf("Enter the Password:\n");
	char password[15];
	fflush(stdin);
	fgets(password, 15, stdin);
	if (login(username, password))
		screen_welcome();
	else
		printf("\nInvalid Username or Password\n");
	//pause(5000);
	return;
}
void screen_welcome()
{
	int ch;
	while (1)
	{
		system("cls");
		printf("Login Screen\n");
		printf("1.Wall\n2.Join\n3.Create\n4.Leave\n5.Logout\n");
		printf("Enter your Choice:");
		scanf("%d", &ch);
		system("cls");
		switch (ch)
		{
		case 1:
			screen_wall();
			break;
		case 2:
			screen_join();
			break;
		case 3:
			screen_create();
			break;
		case 4:
			screen_leave();
			break;
		case 5:
			return;
		default:
			printf("Invalid Option, Enter your correct Option\n\n");
		}
	}
}
void screen_register()
{
	printf("press Exit\n\n");
	printf("Enter Username:\n");
	char username[15];
	fflush(stdin);
	fgets(username, 15, stdin);
	printf("Enter Password:\n");
	char password[15];
	fflush(stdin);
	fgets(password, 15, stdin);
	addUser(username, password);
}