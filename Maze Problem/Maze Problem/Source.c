#include<stdio.h>
#include<malloc.h>
void findPath(int** maze,int x1, int y1, int x2, int y2,int m,int n)
{
	if (maze[x1][y1] == 0)
		return;
	if (x1 == x2 && y1 == y2)
	{
		maze[x1][y1] = -1;
		printf("x: %d \t y: %d\n", x1, y1);
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
					findPath(maze, x1 - 1, y1, x2, y2,m,n);
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
					findPath(maze, x1 + 1, y1, x2, y2,m,n);
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
					findPath(maze, x1, y1 + 1, x2, y2,m,n);
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
					findPath(maze, x1, y1 - 1, x2, y2,m,n);
					if (maze[x1][y1 - 1] == -1)
						flag = 1;
				}
			}
			break;
		}
		if (flag == 1)
		{
			printf("x: %d \t y: %d\n", x1, y1);
			maze[x1][y1] = -1;
			break;
		}
	}
}
void readFile()
{
	FILE* ip = fopen("matrix.txt", "r");
	char c = fgetc(ip);
	int d = 0;
	while (c != ' ')
	{
		d = ((int)c-48) + d * 10;
		c = fgetc(ip);
	}
	int m = d;
	d = 0;
	while (c == ' ')
		c=fgetc(ip);
	while (c != '\n')
	{
		d = ((int)c - 48) + d * 10;
		c = fgetc(ip);
	}
	int n = d;
	c = fgetc(ip);
	int** maze;
	maze = (int**)malloc(m*sizeof(int));
	int i, j;
	for (i = 0; i < m; i++)
		maze[i] = (int*)malloc(n*sizeof(int));
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			maze[i][j] = (int)c - 48;
			c = fgetc(ip);
			while (c == ' ')
				c = fgetc(ip);
		}
		while (c != '\n')
			c = fgetc(ip);
		c = fgetc(ip);
	}
	d = 0;
	while (c != ' ')
	{
		d = ((int)c - 48) + d * 10;
		c = fgetc(ip);
	}
	int x1 = d;
	d = 0;
	while (c == ' ')
		c = fgetc(ip);
	while (c != '\n')
	{
		d = ((int)c - 48) + d * 10;
		c = fgetc(ip);
	}
	int y1 = d;
	c = fgetc(ip);
	d = 0;
	while (c != ' ')
	{
		d = ((int)c - 48) + d * 10;
		c = fgetc(ip);
	}
	int x2 = d;
	d = 0;
	while (c == ' ')
		c = fgetc(ip);
	while (!feof(ip))
	{
		d = ((int)c - 48) + d * 10;
		c = fgetc(ip);
	}
	int y2 = d;
	findPath(maze, x1, y1, x2, y2,m,n);
}
int main()
{
	readFile();
}
/*
int main()
{
	int maze[5][5] = { { 1, 0, 0, 0, 1 }, { 1, 0, 1, 1, 0 }, { 1, 1, 1, 0, 1 }, { 0, 1, 0, 1, 1 }, { 0, 1, 1, 1, 0 } };
	int** maze1;
	int m=5, n=5;
	maze1 = (int**)malloc(m*sizeof(int));
	//printf("Maze\n");
	int i, j;
	for (i = 0; i < m; i++)
		maze1[i] = (int*)malloc(n*sizeof(int));
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			maze1[i][j] = maze[i][j];
	findPath(maze1, 2, 0, 1, 2);
	return 0;
}
*/