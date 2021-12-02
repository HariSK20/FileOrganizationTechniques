#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "File_Structures_S1934.h"

int main()
{
	printf("Program to simulate Two level file organization\n");
	printf("Available commands: \n  1. quit\n  2. list\n  3. create <filename>\n  4. search <filename>\n");
	char command[8], buf[NAME_SIZE], pwd[NAME_SIZE+5] = "root/";
	int status;
	Directory *root = newDirectory("root", NULL);
	if(root == NULL)
	{
		printf(">! Quitting\n");
		return(-1);
	}
	Directory *user = NULL;
	printf(" >> Create new user directory to start!\n > Enter name of user:: ");
	scanf("%[^\n]s", buf);
	clearInput();
	printf(" >> Creating \'%s\' Directory!", buf);
	user = newDirectory(buf, root);
	if(user == NULL)
	{
		printf(">! Quitting\n");
		freeDirectory(root);
		return(-1);
	}
	getPWD(pwd, user);
	do{
		printf("\n>>(%s)> ", pwd);
		scanf("%s", command);
		if(!strcmp(command, "quit"))
			break;
		else if(!strcmp(command, "list"))
		{
			printf("list\n");
			clearInput();
			listDirectory(user, 0);
			continue;
		}
		scanf("%[^\n]s", buf);
		if(!strcmp(command, "create"))
		{
			printf("create File= %s", buf);
			addFile(root, buf, &status);
			if(status == 1)
				printf("\nSuccess");
			else
				printf("\nFailed");
		}
		else if(!strcmp(command, "search"))
		{
			printf("search file = %s\n", buf);
			status = searchFile(root, buf);
			if(status == 1)
				printf("File Found!");
			else if(status == 0)
				printf("File not Found!");
		}
		else if(!strcmp(command, "cd"))
		{
			if(!strcmp(buf, ".."))
			{
				if(strcmp(user->name, "root"))
					user = root;
				else
					printf(" >! root has no parent directory!");
			}
			else
			{
				if(strcmp(user->name, "root"))
					;
				else
					;
			}
		}
		else if(!strcmp(command, "adduser"))
		{
			if(!strcmp(user->name, "root"))
			{
				Directory *temp = newDirectory(buf, root);
				if(temp == NULL)
				{
					printf(" >! Skipping");
				}
				else
				{
					user = temp;
				}
			}
			else
			{
				printf(" >! Cannot create a directory inside a user directory, Skipping");
			}
		}
		else
		{
			printf(">! Invalid command!!");
		}
	}while(1);
	freeDirectory(root);
	printf("\n");
	return(0);
}

