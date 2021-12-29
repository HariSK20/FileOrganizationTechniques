#ifndef FILE_STRUCTURES_S1934_H
#define FILE_STRUCTURES_S1934_H 1
#define INDENT_SIZE 4
#define NAME_SIZE 20
#define INCEPTION_LIMIT 5

typedef struct File
{
	char name[NAME_SIZE];
}File;

typedef struct Directory
{
	char name[NAME_SIZE];
	int num_files, num_children;
	struct File *files;
	struct Directory *parent;
	struct Directory *children;
	struct Directory *nextChild;
}Directory;

char* strrev(char *str);

char* cleanName(char *name);

Directory* addChildDirectory(Directory *parent_dir, Directory *child);

Directory* newDirectory(char *name, Directory *parent);

Directory* changeDirectory(Directory *root, char *dirname);
void getPWD(char *pwd, Directory *dir, int size);

void indentLine(int indent);

void listDirectory(Directory *root, int indent);

Directory* addFile(Directory *root, char *file, int *status);

int searchFile(Directory *root, char *file);

void freeDirectory(Directory *root);

void clearInput();

#endif

