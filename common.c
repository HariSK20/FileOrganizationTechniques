#include "File_Structures_S1934.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* strrev(char *str)
{
    if (!str || ! *str)
        return str;

    int i = strlen(str)-1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;	
    }
	// if(str[0] == '/')
	// 	return(strrev(str));
    return str;
}

char* cleanName(char *name)
{
	for(int i = 0; i < strlen(name); i++)
	{
		if(name[i] == ' ')
		{
			int n = strlen(name) + 1;
			for( int j = i+1; j < n; j++)
			{
				name[j-1] = name[j];
			}
		}
	}
	return(name);
}

void printChildren(Directory *root)
{
	if(root != NULL)
	{
		if(root->children != NULL)
		{
			printf("\n children: ");
			Directory *temp = root->children;
			while(temp!= NULL)
			{
				printf("%s, ", temp->name);
				temp = temp->nextChild;
			}
		}
	}
}

Directory* addChildDirectory(Directory *parent_dir, Directory *child)
{
	if(parent_dir != NULL)
	{
		Directory *temp = (Directory *)malloc(sizeof(Directory));
		if(parent_dir->num_children == 0)
			parent_dir->children = child;
		else
		{
			int i = 0;
			Directory *temp = parent_dir->children;
			while(temp->nextChild != NULL && i < parent_dir->num_children)
			{
				i++;
				temp = temp->nextChild;
			}
			temp->nextChild = child;
		}
		parent_dir->num_children++;
		// parent_dir->children = (Directory *)malloc(sizeof(Directory));
	}
	return(parent_dir);
}

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
	dir->nextChild = NULL;
	dir->parent = parent;
	dir->num_files = 0;
	dir->num_children = 0;
	strcpy(dir->name, cleanName(name));
	if(dir->parent != NULL)
	{
		parent = addChildDirectory(parent, dir);
		// printChildren(parent);
	}
	return(dir);
}

void getPWD(char *pwd, Directory *dir, int size)
{
	if(dir != NULL)
	{
		if(!strcmp(dir->name, "root"))
		{
			pwd[0] = 'r';
			pwd[1] = 'o';
			pwd[2] = 'o';
			pwd[3] = 't';
			pwd[4] = '/';
			pwd[5] = '\0';
		}
		else
		{
			int n = strlen(pwd);
			for(int i = 0; i < n; i++)
				pwd[i] = '\0';
			Directory *temp = dir;
			char temp_str[size];
			// printf(" In get pwd\n");
			while(temp != NULL)
			{
				strcat(pwd, "/");
				strcpy(temp_str, temp->name);
				strcat(pwd, strrev(temp_str));
				// printf("%s\n", pwd);
				temp = temp->parent;
				// strrev()
			}
			pwd = strrev(pwd);
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
	// printChildren(root);
	for(i = 0; i < root->num_files; i++)
	{
		indentLine(indent+1);
		printf("File: %s\n", root->files[i].name);
	}
	if(root->children != NULL)
	{
		Directory *temp = root->children;
		for(i = 0; i < root->num_children; i++)
		{	
			listDirectory(temp, indent+1);
			temp = temp->nextChild;
		}
	}
}

Directory* changeDirectory(Directory *root, char *dirname)
{
	if(root == NULL)
		return(NULL);
	else
	{
		int i = 0;
		Directory *temp = root->children;
		if(temp == NULL)
			return(NULL);
		while(i < root->num_children && temp != NULL)
		{
			i++;
			if(!strcmp(temp->name, dirname))
				return(temp);
			temp = temp->nextChild;
		}
	}
	return(NULL);
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
	// printf("searching for %s \n", file_name);
	// listDirectory(root, 1);
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
		// printf(" checking %s | %s  %d", root->files[i].name, file_name,strcmp(root->files[i].name, file_name));
		//if(strcmp(root->files[i].name, file_name) == 0);
		//{
		//	printf("yes\n");
		//	return(1);
		//}
		// printf("no\n");
	}
	return(0);
}

void freeDirectory(Directory *root)
{
	// free(root->parent);
	Directory *temp1, *temp2;
	temp1 = root->children;
	temp2 = temp1;
	while(temp2!= NULL)
	{
		temp1 = temp2;
		temp2 = temp2->nextChild;
		freeDirectory(temp1);
	}
	// free(root->children);
	free(root->files);
	free(root);
}

void clearInput()
{
	char a = 'a';
	while(a != '\n')
		scanf("%c", &a);
}

