#include "File_Structures_S1934.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Directory* newDirectory(char *name, Directory *parent)
{
	Directory *dir = (Directory *)malloc(sizeof(Directory));
	if(dir == NULL)
	{
		printf("\n>! Unable to create directory %s\n", name);
		return(NULL);
	}
	dir->files = NULL;
	dir->children = NULL;
	dir->parent = parent;
	dir->num_files = 0;
	dir->num_children = 0;
	strcpy(dir->name, name);
	return(dir);
}

void getPWD(char *pwd, Directory *dir)
{
	if(dir != NULL)
	{
		if(strcmp(dir->name, "root"))
		{
			for(int i = 0; i < strlen(dir->name); i++)
			{
				pwd[i + 5] = dir->name[i];
			}
		}
	}
}

void indentLine(int indent)
{
	int i, j;
	for(i = 0; i < indent; i++)
		for(j = 0; j < INDENT_SIZE; j++)
			printf("-");
}

void listDirectory(Directory *root, int indent)
{
	int i;
	if(root == NULL)
		return;
	if(indent == 0)
		printf("Listing...\n");
	indentLine(indent);
	printf("Directory: %s\n", root->name);
	for(i = 0; i < root->num_files; i++)
	{
		indentLine(indent+1);
		printf("File: %s\n", root->files[i].name);
	}
	if(root->children != NULL)
	{
		for(i = 0; i < root->num_children; i++)
			listDirectory(&root->children[i], indent+1);
	}
}

Directory* addFile(Directory* root, char *file_name, int *status)
{
	if(root == NULL)
	{
		*status = 0;
		return(NULL);
	}
	root->num_files++;
	File *temp = root->files;
	if(root->num_files == 1)
	{
		temp = (File *)malloc(sizeof(File));
	}
	else
	{
		temp = (File *)realloc(root->files, root->num_files*sizeof(File));
	}
	if(temp == NULL)
	{
		printf("\n>! Unable to add file!");
		root->num_files--;
		*status = -1;
	}
	else
	{
		root->files = temp;
		strcpy(root->files[root->num_files - 1].name, file_name);
		*status = 1;
	}
	return(root);
}

int searchFile(Directory *root, char *file_name)
{
	printf("searching for %s \n", file_name);
	listDirectory(root, 1);
	if(root == NULL)
		return(-1);
	if(root->num_files == 0)
		return(-2);
	for(int i=0; i < root->num_files; i++)
	{
		int cmp = strcmp(root->files[i].name, file_name);
		if(cmp == 0)
		{
			return (1);
		}
		//printf(" checking %s | %s  %d", root->files[i].name, file_name,strcmp(root->files[i].name, file_name));
		//if(strcmp(root->files[i].name, file_name) == 0);
		//{
		//	printf("yes\n");
		//	return(1);
		//}
		printf("no\n");
	}
	return(0);
}

void freeDirectory(Directory *root)
{
	free(root->parent);
	free(root->children);
	free(root->files);
	free(root);
}

void clearInput()
{
	char a = 'a';
	while(a != '\n')
		scanf("%c", &a);
}

