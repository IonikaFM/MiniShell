#ifndef __FILE_H__
#define __FILE_H__
#include "list.h"

typedef struct Directory {
	// The name of the directory
	char *name;

	Node *startFile, *lastFile;

	Node *startDirectory, *lastDirectory;

	// The parent directory of the current directory
	// (NULL for the root directory)
	struct Directory *parentDir;
} Directory;

typedef struct File {
	// The name of the file
	char *name;

	// The size of the file
	int size;

	// The content of the file
	char *data;

	// The directory in which the file is located
	Directory *dir;
} File;

void addFile(File **newFile, char *fileName,
char *fileData, Directory **parent);

void addDirectory(Directory **newDirectory,
char *directoryName, Directory **parent);

#endif /* __FILE_H__ */
