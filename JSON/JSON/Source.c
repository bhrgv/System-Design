#include<stdio.h>
#include<malloc.h>
#include"json.h"
void readValues();
void readJSON(Json *head,FILE* ip)
{
	char c;
	do
	{
		c = getc(ip);
	} while (c != '{' && !feof(ip));
	if (feof(ip))
		return;
	head->next = (Json*)malloc(sizeof(Json));
	head->next->next = NULL;
	readValues(head, ip);
	readJSON(head->next, ip);
}
void readArray(Number* head, FILE* ip)
{
	return;
}
void readValues(Json* head, FILE* ip)
{
	char c;
	do
	{
		c = getc(ip);
	} while (c != '"' && !feof(ip));
	if (feof(ip))
		return;
	char d = fgetc(ip);
	do
	{
		c = fgetc(ip);
	} while (c != ':');
	int i=0;
	switch (d)
	{
	case 'f':
		do
		{
			c = fgetc(ip);
		} while (c != '"');
		c = fgetc(ip);
		while (c != '"')
		{
			head->next->firstName[i++] = c;
			c = fgetc(ip);
		}
		head->next->firstName[i] = '\0';
		break;
	case 'l':
		do
		{
			c = fgetc(ip);
		} while (c != '"');
		c = fgetc(ip);
		while (c != '"')
		{
			head->next->lastName[i++] = c;
			c = fgetc(ip);
		}
		head->next->lastName[i] = '\0';
		break;
	case 'a':
		do
		{
			c = fgetc(ip);
		} while (c == ' ');
		int d = 0;
		while (c != ',')
		{
			d = d*10+(int)c - 48;
			c = fgetc(ip);
		}
		head->next->age = d;
		break;
	case 'h':
		do
		{
			c = fgetc(ip);
		} while (c == ' ');
		float d1 = 0,d2=0;
		while (c != '.')
		{
			d1 = d1 * 10 + (int)c - 48;
			c = fgetc(ip);
		}
		c = fgetc(ip);
		while (c != ',')
		{
			d2 = d2 / 10 + (int)c - 48;
			c = fgetc(ip);
		}
		head->next->height = d1 + d2;
		break;
	case 'p':
		readArray(&(head->next->head),ip);
		while (c != '}')
			c = fgetc(ip);
		break;
	default:
		return;
	}
	if (c == '}')
		return;
	readValues(head, ip);
}
int main()
{
	Json head;
	head.next=NULL;
	head.head.next = NULL;
	FILE* ip = fopen("sample.json", "r");
	readJSON(&head, ip);
	fclose(ip);
	return 0;
}