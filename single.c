#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "File_Structures_S1934.h"

int main()
{
	printf("Program to simulate Single level file organization\n");
	printf("Available commands: \n  1. quit\n  2. list\n  3. create <filename>\n  4. search <filename>\n");
	char command[7], buf[NAME_SIZE];
	int status;
	Directory *root = newDirectory("root", NULL);
	do{
		printf("\n>>> ");
		scanf("%s", command);
		if(!strcmp(command, "quit"))
			break;
		else if(!strcmp(command, "list"))
		{
			// printf("list\n");
			clearInput();
			listDirectory(root, 0);
			continue;
		}
		scanf("%[^\n]s", buf);
		if(!strcmp(command, "create"))
		{
			// printf("create File= %s", buf);
			addFile(root, buf, &status);
			if(status == 1)
				printf("Success");
			else
				printf("Failed");
		}
		else if(!strcmp(command, "search"))
		{
			// printf("search file = %s\n", buf);
			status = searchFile(root, buf);
			if(status == 1)
				printf("File Found!");
			else if(status == 0)
				printf("File not Found!");
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

