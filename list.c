#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file.h"
#include "main.h"

void insertFileInList(Node **start, Node **last, void **myFile)
{

	File **new;

	new = (File **)myFile;
	if ((*start) == NULL) {

		(*start) = (Node *)malloc(sizeof(Node));
		(*start)->data = *new;
		(*start)->next = NULL;
		(*start)->prev = NULL;
		(*last) = (*start);
	} else {
		Node *use;

		use = (Node *)malloc(sizeof(Node));
		use->data = *new;
		use->next = NULL;
		use->prev = NULL;
		if (strcmp((*new)->name,
		((File *)((*start)->data))->name) < 0) {
			use->next = (*start);
			(*start)->prev = use;
			(*start) = use;
		} else {
			Node *count;

			count = (Node *)malloc(sizeof(Node));
			count = (*start)->next;
			int ok;

			ok = 0;
			if (count)
				while (count != NULL) {
					if (strcmp((*new)->name,
					((File *)(count->data))->name) < 0) {
						(count->prev)->next = use;
						use->next = count;
						use->prev = count->prev;
						count->prev = use;
						ok = 1;
						break;
					}
				count = count->next;
				}
			if (ok == 0) {
				use->prev = (*last);
				(*last)->next = use;
				(*last) = use;
			}
		}
	}
}

void insertDirectoryInList(Node **start, Node **last, void **myDirectory)
{
	Directory **new;

	new = (Directory **)myDirectory;
	if (*start == NULL) {
		*start = (Node *)malloc(sizeof(Node));
		(*start)->data = *new;
		(*start)->next = NULL;
		(*start)->prev = NULL;
		*last = *start;
	} else {
		Node *use;

		use = (Node *)malloc(sizeof(Node));
		use->data = *new;
		use->next = NULL;
		use->prev = NULL;
		if (strcmp((*new)->name,
		((Directory *)((*start)->data))->name) < 0) {
			use->next = *start;
			(*start)->prev = use;
			*start = use;
		} else {
			Node *count;

			count = (Node *)malloc(sizeof(Node));
			count = (*start)->next;
			int ok;

			ok = 0;
			if (count)
				while (count != NULL) {
					if (strcmp((*new)->name,
					((Directory *)(count->data))->name)
					< 0) {
						(count->prev)->next = use;
						use->next = count;
						use->prev = count->prev;
						count->prev = use;
						ok = 1;
						break;
					}
					count = count->next;
				}
			if (ok == 0) {
				use->prev = *last;
				(*last)->next = use;
				*last = use;
			}
		}
	}
}

void deleteFileFromList(Node **start, Node **last, char *searchedName)
{
int ok;

ok = 0;
if ((*start) == NULL)
	printf("Cannot remove '%s': No such file!\n", searchedName);
else {
	if ((*start) == (*last) &&
	strcmp(((File *)((*start)->data))->name, searchedName) == 0) {
		ok = 1;
		(*start) = NULL;
		(*last) = NULL;
	} else {
		if (strcmp(((File *)((*start)->data))->name,
		searchedName) == 0) {
			(*start)->next->prev = NULL;
			(*start) = (*start)->next;
			ok = 1;
		} else
			if (strcmp(((File *)((*last)->data))->name,
			searchedName) == 0) {
				(*last)->prev->next = NULL;
				(*last) = (*last)->prev;
				ok = 1;
			} else {
				Node *currentElm;

				currentElm =
				(Node *)malloc(sizeof(Node));
				currentElm = *start;
				while (currentElm != NULL) {
					if (strcmp(((File *)(currentElm->data))
					->name, searchedName) == 0) {
						currentElm->prev->next
						= currentElm->next;
						currentElm->next =
						currentElm->prev;
						ok = 1;
						break;
					}
					currentElm = currentElm->next;
				}
			}
	}
	if (ok == 0)
		printf("Cannot remove '%s': No such file!\n", searchedName);
}
}

void deleteDirectoryFromList(Node **start, Node **last, Node **toBeDeleted)
{
	if ((*start) == (*last) && (*start) == *toBeDeleted) {
		(*start) = NULL;
		(*last) = NULL;
	} else {
		if ((*start) == *toBeDeleted) {
			(*start) = (*start)->next;
			(*start)->prev = NULL;
		} else
			if ((*last) == *toBeDeleted) {
				(*last) = (*last)->prev;
				(*last)->next = NULL;
			} else {
				Node *currentElm;

				currentElm = (*start);
				while (currentElm != NULL) {
					if (currentElm == *toBeDeleted) {
						(currentElm->prev)->next =
						currentElm->next;
						(currentElm->next)->prev =
						currentElm->prev;
						break;
					}
					currentElm = currentElm->next;
				}
			}
	}
}

void printFileList(Node *start)
{
	while (start != NULL) {
		printf("%s ", ((File *)(start->data))->name);
		start = start->next;
	}
}

void printDirectoryList(Node *start)
{
	while (start != NULL) {
		printf("%s ", ((Directory *)(start->data))->name);
		start = start->next;
	}
}

void printFilesTreeFormat(Node *start, int spaces)
{
	int i;

	while (start != NULL) {
		for (i = 1; i <= spaces; i++)
			printf(" ");
		printf("%s\n", ((File *)(start->data))->name);
		start = start->next;
	}
}
