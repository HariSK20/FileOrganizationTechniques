#ifndef INDENT_SIZE
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
	struct Directory *children, *parent;
}Directory;

Directory* newDirectory(char *name, Directory *parent);

void getPWD(char *pwd, Directory *dir);

void indentLine(int indent);

void listDirectory(Directory *root, int indent);

Directory* addFile(Directory *root, char *file, int *status);

int searchFile(Directory *root, char *file);

void freeDirectory(Directory *root);

void clearInput();

#endif

