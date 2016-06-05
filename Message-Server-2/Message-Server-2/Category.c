#include"Category.h"
#include"User.h"
#include<stdio.h>
void addCategory(char* name)
{
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, 80, SEEK_SET);
	BitVector categories[100];
	fread(categories, sizeof(BitVector), 100, ip);
	int i;
	for (i = 0; i < 100; i++)
		if (categories[i].status == 0)
			break;
	if (i == 100)
	{
		printf("\nNo More Space for New Category\n");
		return;
	}
	User user;
	fseek(ip,active_user, SEEK_SET);
	fread(&user, sizeof(User), 1, ip);
	if (user.num_cat == 5)
	{
		printf("\nNo More Space for New Category by Current User\n");
		return;
	}
	Category category;
	user.category[user.num_cat++] = i * 20 + 1680;
	strcpy(category.name, name);
	categories[i].status = 1;
	fseek(ip, 80, SEEK_SET);
	fwrite(categories, sizeof(BitVector), 20, ip);
	fseek(ip, user.offset, SEEK_SET);
	fwrite(&user, sizeof(User), 1, ip);
	fseek(ip, i*20+1680, SEEK_SET);
	fwrite(&category, sizeof(Category), 1, ip);
	fclose(ip);
}
int loadCategory()
{
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, active_user, SEEK_SET);
	User user;
	fread(&user, sizeof(User), 1, ip);
	int num_cat = user.num_cat;
	for (int i = 0; i < num_cat; i++)
	{
		Category category;
		fseek(ip, user.category[i], SEEK_SET);
		fread(&category, sizeof(Category), 1, ip);
		printf("\n%d --> %s \n\n ", i + 1, category.name);
	}
	printf("Enter the Category to Load:\n");
	int ch;
	scanf("%d", &ch);
	if (ch <= num_cat)
		active_categ = user.category[ch - 1];
	else
		active_categ = 0;
	fclose(ip);
	system("cls");
}
void joinCategory()
{
	FILE* ip = fopen("file.bin", "rb+");
	fseek(ip, active_user, SEEK_SET);
	User user;
	fread(&user, sizeof(User), 1, ip);
	int num_cat = user.num_cat;
	BitVector categories[100];
	fseek(ip, 80, SEEK_SET);
	fread(categories, sizeof(BitVector), 100, ip);
	int i;
	for (i = 0; i < 100; i++)
	{
		if (categories[i].status == 1)
		{
			Category category;
			fseek(ip, i * 20 + 1680, SEEK_SET);
			fread(&category, sizeof(Category), 1, ip);
			printf("\n%d --> %s \n\n ", i + 1, category.name);
		}
	}
	printf("Enter the Category to Join:\n");
	int ch;
	scanf("%d", &ch);
	if (categories[ch - 1].status == 1)
	{
		user.category[user.num_cat++] = (ch - 1) * 20 + 1680;
		active_categ = (ch - 1) * 20 + 1680;
	}
	else
		active_categ = 0;
	fseek(ip, user.offset, SEEK_SET);
	fwrite(&user, sizeof(User), 1, ip);
	fclose(ip);
}
int deleteCategory(char* name)
{
	return 0;
}