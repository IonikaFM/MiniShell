#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "list.h"

void addFile(File **newFile, char *fileName, char *fileData, Directory **parent)
{
	*newFile = (File *)malloc(sizeof(File));
	(*newFile)->name = (char *)malloc(strlen(fileName)*sizeof(char));
	(*newFile)->data = (char *)malloc(strlen(fileData)*sizeof(char));
	(*newFile)->name = strdup(fileName);
	(*newFile)->data = strdup(fileData);
	(*newFile)->size = strlen(fileData);
	(*newFile)->dir = (*parent);
	insertFileInList(&((*parent)->startFile),
	&((*parent)->lastFile), (void **)newFile);
}

void addDirectory(Directory **newDirectory, char *directoryName,
Directory **parent)
{
	*newDirectory = (Directory *)malloc(sizeof(Directory));
	(*newDirectory)->name =
	(char *)malloc(strlen(directoryName)*sizeof(char));
	(*newDirectory)->name = strdup(directoryName);
	(*newDirectory)->parentDir = *parent;
	(*newDirectory)->startFile = NULL;
	(*newDirectory)->lastFile = NULL;
	(*newDirectory)->startDirectory = NULL;
	(*newDirectory)->lastDirectory = NULL;
	insertDirectoryInList(&((*parent)->startDirectory),
	&(*parent)->lastDirectory, (void **)newDirectory);
}
