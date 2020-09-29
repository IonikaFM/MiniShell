#ifndef __LIST_H__
#define __LIST_H__

typedef struct Node {
	void *data;

	struct Node *next, *prev;
} Node;

void insertFileInList(Node **start, Node **last, void **myFile);

void insertDirectoryInList(Node **start, Node **last, void **myDirectory);

void deleteFileFromList(Node **start, Node **last, char *searchedName);

void deleteDirectoryFromList(Node **start, Node **last, Node **toBeDeleted);

void printFileList(Node *start);

void printDirectoryList(Node *start);

void printFilesTreeFormat(Node *start, int spaces);

#endif /* __LIST_H__ */
