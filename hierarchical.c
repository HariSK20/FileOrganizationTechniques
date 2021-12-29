#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "File_Structures_S1934.h"

int main()
{
	printf("Program to simulate hierarchical file organization\n");
	printf("Available commands: \n  1. quit\n  2. list\n  3. create <filename>\n  4. search <filename>\n  5. mkdir <username> \n  6. cd <directoryname>\n");
	char command[8], buf[NAME_SIZE], pwd[NAME_SIZE+5] = "root/";
	int status;
	Directory *root = newDirectory("root", NULL);
	if(root == NULL)
	{
		printf(">! Quitting\n");
		return(-1);
	}
	Directory *user = root;

	getPWD(pwd, user, NAME_SIZE+5);
	
	do{
		// getPWD(pwd, user, NAME_SIZE+5);
		printf("\n>>(%s)> ", pwd);
		scanf("%s", command);
		if(!strcmp(command, "quit"))
		{
			// printf("quit\n");
			break;
		}
		else if(!strcmp(command, "list"))
		{
			// printf("list\n");
			clearInput();
			listDirectory(user, 0);
			continue;
		}
		scanf("%[^\n]s", buf);
		cleanName(buf);
		if(!strcmp(command, "create"))
		{
			// printf("create %s", buf);
			addFile(user, buf, &status);
			if(status == 1)
				printf("Success");
			else
				printf("Failed");
		}
		else if(!strcmp(command, "search"))
		{
			// printf("search %s\n", buf);
			status = searchFile(user, buf);
			if(status == 1)
				printf("File Found!");
			else
				printf("File not Found!");
		}
		else if(!strcmp(command, "cd"))
		{
			// cleanName(buf);
			// printf("cd %s\n", buf);
			if(!strcmp(buf, ".."))
			{
				if(!strcmp(user->name, "root"))
					printf(" >! root has no parent directory!");
				else
				{
					user = user->parent;
				}
			}
			else if(!strcmp(buf, "root"))
			{
				// if(!strcmp(user->name, "root"))
				// 	printf(" >! root has no parent directory!");
				// else
				// {
				user = root;
				// }
			}
			else
			{
				// if(!strcmp(user->name, "root"))
				// {
				Directory *temp = changeDirectory(user, buf);
				if(temp == NULL)
					printf(" Directory does not exist");
				else
					user = temp;
				// }
				// else
				// 	printf(" >! There are no other directories inside\n");
			}
			// if(user == root)
			// 	printf("success cd!\n");
			getPWD(pwd, user, NAME_SIZE+5);
		}
		else if(!strcmp(command, "mkdir"))
		{
			// printf("mkdir %s\n", buf);
			// if(!strcmp(user->name, "root"))
			// {
			Directory *temp = newDirectory(buf, user);
			if(temp == NULL)
			{
				printf(" >! Error Skipping");
			}
			else
			{
				user = temp;
			}
			// }
			// else
			// {
			// 	printf(" >! Cannot create a directory inside a user directory, Skipping");
			// }
			getPWD(pwd, user, NAME_SIZE+5);
		}
		else
		{
			// printf("%s %s\n", command, buf);
			printf(">! Invalid command!!");
		}
		if(user == NULL)
			break;
	}while(1);
	freeDirectory(root);
	printf("\n");
	return(0);
}

