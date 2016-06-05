#include"Message.h"
#include<stdio.h>
#include"User.h"
#include"Category.h"
#include<string.h>
void addMessage()
{
	printf("MAX CHARACTERS 128\n\n");
	printf("Enter your Message : \n");
	char msg[128];
	fflush(stdin);
	fgets(msg, 128, stdin);
	Message message;
	Category category;
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, active_categ, SEEK_SET);
	fread(&category, sizeof(Category), 1, ip);
	strcpy(message.cat, category.name);
	fseek(ip, active_user, SEEK_SET);
	User user;
	fread(&user, sizeof(User), 1, ip);
	strcpy(message.user, user.username);
	message.reply_id = 0;
	message.type = 0;
	strcpy(message.msg, msg);
	message.msg_pos = 0;
	fseek(ip, 3680, SEEK_SET);
	int num_msg;
	fread(&num_msg, sizeof(int), 1, ip);
	int msg_off = num_msg * 180 + 3684;
	num_msg++;
	fseek(ip, 3680, SEEK_SET);
	fwrite(&num_msg, sizeof(int), 1, ip);
	message.offset = msg_off;
	fseek(ip, msg_off, SEEK_SET);
	fwrite(&message, sizeof(Message), 1, ip);
	fclose(ip);
}
void loadMessages()
{
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, 3680, SEEK_SET);
	int num_msg;
	fread(&num_msg, sizeof(int), 1, ip);
	fseek(ip, active_categ, SEEK_SET);
	Category category;
	fread(&category, sizeof(Category), 1, ip);
	printf("Messages are:\n\n");
	int count = 1;
	for (int i = 0; i < num_msg; i++)
	{
		Message msg;
		fseek(ip, i * 180 + 3684, SEEK_SET);
		fread(&msg, sizeof(Message), 1, ip);
		if (!strcmp(category.name, msg.cat) && msg.reply_id == 0)
		{
			printf("%d\n", count++);
			printf("Sender : %s \n\n", msg.user);
			printf("Message :\n%s\n\n",msg.msg);
		}
	}
	fclose(ip);
}
void addReply()
{
	printf("MAX CHARACTERS 128\n\n");
	printf("Enter your Message : \n");
	char msg[128];
	fflush(stdin);
	fgets(msg, 128, stdin);
	Message message;
	Category category;
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, active_categ, SEEK_SET);
	fread(&category, sizeof(Category), 1, ip);
	strcpy(message.cat, category.name);
	fseek(ip, active_user, SEEK_SET);
	User user;
	fread(&user, sizeof(User), 1, ip);
	strcpy(message.user, user.username);
	message.reply_id = 1;
	message.type = 1;
	strcpy(message.msg, msg);
	message.msg_pos = active_msg;
	fseek(ip, 3680, SEEK_SET);
	int num_msg;
	fread(&num_msg, sizeof(int), 1, ip);
	int msg_off = num_msg * 180 + 3684;
	num_msg++;
	fseek(ip, 3680, SEEK_SET);
	fwrite(&num_msg, sizeof(int), 1, ip);
	message.offset = msg_off;
	fseek(ip, msg_off, SEEK_SET);
	fwrite(&message, sizeof(Message), 1, ip);
	fclose(ip);
}
void loadReplies()
{
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, 3680, SEEK_SET);
	int num_msg;
	fread(&num_msg, sizeof(int), 1, ip);
	fseek(ip, active_categ, SEEK_SET);
	Category category;
	fread(&category, sizeof(Category), 1, ip);
	printf("\nReplies are:\n\n");
	int count = 1;
	for (int i = 0; i < num_msg; i++)
	{
		Message msg;
		fseek(ip, i * 180 + 3684, SEEK_SET);
		fread(&msg, sizeof(Message), 1, ip);
		if (!strcmp(category.name, msg.cat) && msg.reply_id == 1 && msg.msg_pos == active_msg)
		{
			printf("%d\n", count++);
			printf("Sender : %s \n\n", msg.user);
			printf("Message :\n%s\n\n", msg.msg);
		}
	}
	fclose(ip);
}
int deleteMessage()
{
	printf("\nEnter the Message to delete: ");
	int ch;
	scanf("%d", &ch);
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, active_user, SEEK_SET);
	User user;
	fread(&user, sizeof(User), 1, ip);
	fseek(ip, 3680, SEEK_SET);
	int num_msg;
	fread(&num_msg, sizeof(int), 1, ip);
	fseek(ip, active_categ, SEEK_SET);
	Category category;
	fread(&category, sizeof(Category), 1, ip);
	printf("Messages are:\n\n");
	int count = 1;
	for (int i = 0; i < num_msg; i++)
	{
		Message msg;
		fseek(ip, i * 180 + 3684, SEEK_SET);
		fread(&msg, sizeof(Message), 1, ip);
		if (!strcmp(category.name, msg.cat) && msg.reply_id == 0)
		{
			if (ch == count)
			{
				if (strcmp(user.username, msg.user))
				{
					printf("\nYou are not the Owner of the Message, Deletion of Message not Possible\n");
					return 0;
				}
				int pos = msg.offset;
				deleteThread(msg.offset);
				active_msg = pos;
				for (int i = 0; i < num_msg; i++)
				{
					Message msg;
					fseek(ip, i * 180 + 3684, SEEK_SET);
					fread(&msg, sizeof(Message), 1, ip);
					if (!strcmp(category.name, msg.cat) && msg.reply_id == 1 && msg.msg_pos == active_msg)
					{
						if (!strcmp(user.username, msg.user))
						{
							deleteThread(msg.offset);
						}
					}
				}
				return 1;
			}
			count++;
		}
	}
	return 0;
	fclose(ip);
}
int deleteReply()
{
	printf("\nEnter the Reply to delete: ");
	int ch;
	scanf("%d", &ch);
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, active_user, SEEK_SET);
	User user;
	fread(&user, sizeof(User), 1, ip);
	fseek(ip, 3680, SEEK_SET);
	int num_msg;
	fread(&num_msg, sizeof(int), 1, ip);
	fseek(ip, active_categ, SEEK_SET);
	Category category;
	fread(&category, sizeof(Category), 1, ip);
	printf("\nReplies are:\n\n");
	int count = 1;
	for (int i = 0; i < num_msg; i++)
	{
		Message msg;
		fseek(ip, i * 180 + 3684, SEEK_SET);
		fread(&msg, sizeof(Message), 1, ip);
		if (!strcmp(category.name, msg.cat) && msg.reply_id == 1 && msg.msg_pos == active_msg)
		{
			if (ch == count)
			{
				if (strcmp(user.username, msg.user))
				{
					printf("\nYou are not the Owner of the Message, Deletion of Message not Possible\n");
					return 0;
				}
				deleteThread(msg.offset);
				return 1;
			}
		}
	}
	return 0;
	fclose(ip);
}
void deleteThread(long offset)
{
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, 3680, SEEK_SET);
	int num_msg;
	fread(&num_msg, sizeof(int), 1, ip);
	int pos = offset;
	int next_pos = offset + 180;
	while (1)
	{
		if (next_pos > num_msg * 180 + 3684)
			break;
		Message msg;
		fseek(ip, next_pos, SEEK_SET);
		fread(&msg, sizeof(Message), 1, ip);
		fseek(ip, pos, SEEK_SET);
		fwrite(&msg, sizeof(Message), 1, ip);
		next_pos += 180;
		pos += 180;
	}
	num_msg -= 1;
	fseek(ip, 3680, SEEK_SET);
	fwrite(&num_msg, sizeof(int), 1, ip);
	fclose(ip);
}