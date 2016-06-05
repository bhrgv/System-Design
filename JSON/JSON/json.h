#ifndef JSON_H
typedef struct node
{
	char type[20];
	char number[20];
	struct node* next;
}Number;
typedef struct json
{
	char firstName[20];
	char lastName[20];
	int age;
	float height;
	Number head;
	struct json* next;
}Json;
#endif