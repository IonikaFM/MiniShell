#ifndef __MAIN_H__
#define __MAIN_H__

#define CREATEFS 6953402479289
#define DELETEFS 6953426453624
#define TOUCH 210729236360
#define MKDIR 210720772860
#define LS 193498414
#define PWD 6385598746
#define CD 5863276
#define TREE 210729326719
#define RM 5863780
#define RMDIR 210726774339

const unsigned long hash(const char *str);

void createFs(Directory **root);

void tree(Directory *currentParent, Node *files, int i);

void rmdir(Directory **parent);

void verifyIfExists(char *searchedName, Node **toBeDeleted, int *exists);

void doOperation(void);

#endif /*__MAIN_H__*/
