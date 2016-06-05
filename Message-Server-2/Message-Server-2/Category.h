#ifndef CATEGORY_H
typedef struct bvector
{
	unsigned int status : 1;
}BitVector;
typedef struct category
{
	char name[20];
}Category;
int active_user ;
int active_categ ;
int active_msg;
void addCategory(char* name);
int loadCategory();
void joinCategory();
int deleteCategory(char* name);
#endif
