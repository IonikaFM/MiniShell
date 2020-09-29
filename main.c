#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "list.h"
#include "main.h"

void createFs(Directory **root)
{
	(*root) = (Directory *)malloc(sizeof(Directory));
	(*root)->name = "/";
	(*root)->startDirectory = NULL;
	(*root)->startFile = NULL;
	(*root)->lastDirectory = NULL;
	(*root)->lastFile = NULL;
	(*root)->parentDir = NULL;
}

const unsigned long hash(const char *str)
{
	unsigned long hash;

	hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c;
	return hash;
}

void tree(Directory *currentParent, Node *files, int i)
{
	files = currentParent->startDirectory;
	if (i == 0) {
		if (strcmp(currentParent->name, "/") == 0)
			printf("%s\n", currentParent->name);
		else
			printf("%s\n", currentParent->name);
		i = 1;
	} else {
		int j;

		for (j = 1; j <= 4 * (i - 1); j++)
			printf(" ");
		printf("%s\n", currentParent->name);
	}
	printFilesTreeFormat(currentParent->startFile, 4 * i);
	while (files) {
		tree(((Directory *)(files->data)), files, i + 1);
		files = files->next;
	}
}

void verifyIfExists(char *searchedName, Node **toBeDeleted, int *exists)
{
	while (*toBeDeleted) {
		if (strcmp(((Directory *)((*toBeDeleted)->data))
		->name, searchedName) == 0) {
			*exists = 1;
			break;
		}
		*toBeDeleted = (*toBeDeleted)->next;
	}
}

void doOperation(void)
{
	Directory *root, *currentParent;

	char *s;

	s = (char *)malloc(100*sizeof(char));
	int ok;

	ok = 1;
	while (ok) {
		fgets(s, 20, stdin);
		char *p;

		p = (char *)malloc(sizeof(char));
		p = strtok(s, " ");
		switch (hash(p)) {
		case CREATEFS:
		{
			createFs(&root);
			currentParent = (Directory *)malloc(sizeof(Directory));
			currentParent = root;
			break;
		}
		case DELETEFS:
		{
			ok = 0;
			root = NULL;
			currentParent = NULL;
			//free(root);
			break;
		}
		case TOUCH:
		{
			p = strtok(NULL, " ");
			char *fileName, *fileData, *pos;

			fileName = (char *)malloc(sizeof(char));
			fileData = (char *)malloc(sizeof(char));
			fileName = strdup(p);
			pos = strchr(fileName, '\n');
			if (pos != NULL)
				*pos = '\0';
			p = strtok(NULL, " ");
			if (p) {
				fileData = strdup(p);
				pos = strchr(fileData, '\n');
				if (pos != NULL)
					*pos = '\0';
			} else
				fileData = "-";
			File *newFile;

			addFile(&newFile, fileName, fileData, &currentParent);
			break;
		}
		case MKDIR:
		{
			p = strtok(NULL, " ");
			char *directoryName, *pos;

			directoryName = (char *)malloc(sizeof(char));
			directoryName = strdup(p);
			pos = strchr(directoryName, '\n');
			if (pos != NULL)
				*pos = '\0';
			Directory *newDirectory;

			addDirectory(&newDirectory, directoryName,
			&currentParent);
			break;
		}
		case LS:
		{
			printFileList(currentParent->startFile);
			printDirectoryList(currentParent->startDirectory);
			printf("\n");
			break;
		}
		case PWD:
		{
			char *path, *aux;

			path = (char *)malloc(sizeof(char));
			aux = (char *)malloc(sizeof(char));
			Directory *whereIAm;

			whereIAm = (Directory *)malloc(sizeof(Directory));
			whereIAm = currentParent;
			*path = '\0';
			if (whereIAm == root)
				printf("/\n");
			else {
				while (whereIAm != root) {
					strcpy(aux, "/");
					strcat(aux, whereIAm->name);
					strcat(aux, path);
					strcpy(path, aux);
					whereIAm = whereIAm->parentDir;
				}
				printf("%s\n", path);
			}
			//free(path);
			//free(aux);
			break;
		}
		case CD:
		{
			p = strtok(NULL, " ");
			char *pos;

			pos = strchr(p, '\n');
			if (pos != NULL)
				*pos = '\0';
			if (strcmp(p, "..") == 0)
				currentParent = currentParent->parentDir;
			else {
				Node *searchToVerify;

				searchToVerify = (Node *)malloc(sizeof(Node));
				searchToVerify = currentParent->startDirectory;
				int ok;

				ok = 0;
				while (searchToVerify) {
					if (strcmp(((Directory *)
					(searchToVerify->data))->name,
					p) == 0) {
						currentParent = (Directory *)
						(searchToVerify->data);
						ok = 1;
						break;
					}
					searchToVerify = searchToVerify->next;
				}
				if (ok == 0)
					printf
				("Cannot move to '%s': No such directory!\n",
				p);
			}
			break;
		}
		case TREE:
		{
			Node *whereIAm;

			whereIAm = (Node *)malloc(sizeof(Node));
			tree(currentParent, whereIAm, 0);
			break;
		}
		case RM:
		{
			p = strtok(NULL, " ");
			char *pos;

			pos = strchr(p, '\n');
			if (pos != NULL)
				*pos = '\0';
			deleteFileFromList(&(currentParent)->startFile,
			&(currentParent)->lastFile, p);
			break;
		}
		case RMDIR:
		{
			p = strtok(NULL, " ");
			char *pos;

			pos = strchr(p, '\n');
			if (pos != NULL)
				*pos = '\0';
			Node *toBeDeleted;
				toBeDeleted = currentParent->startDirectory;
			int exists;

			exists = 0;
			verifyIfExists(p, &toBeDeleted, &exists);
			if (exists == 0)
				printf
				("Cannot remove '%s': No such directory!\n", p);
			else
				deleteDirectoryFromList
				(&(currentParent)->startDirectory,
				&(currentParent)->lastDirectory, &toBeDeleted);
			break;
		}
		default:
			break;
		}
	}
}

int main(void)
{
	doOperation();
	return 0;
}
