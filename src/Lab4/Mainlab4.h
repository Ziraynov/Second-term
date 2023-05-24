#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#define path "C:/Users/ziray/CLionProjects/Secondterm/src/Lab4/data.txt"
#define KB 1024
#define SPACE " "


typedef struct Tree {

    char *data;
    struct Tree *right;
    struct Tree *left;
} TREE;
void getUserName(char *Name);
void addLogs(char *UserUnswer, char *UserName);
void functions(int *x);
void openSite(char *UserName);
void diagram(TREE *Tree);
void getMenuIndex(int *x, char *UserName);
void freeTree(TREE* Tree);
void makeNewDataBase(char *Quest, char *Word, TREE *Tree, FILE *Data, char *GetUnswer);
void getQuestion(char *Quest, char *UserName);
void addNewElementInDataBase(char *Word, TREE *Ttree, FILE *Data, char *getUnswer, char *UserName);
int getUn(char *UserName);
void checkUnswer(char *Word, TREE *Tree, FILE *Data, char *getUnswer, char *UserName);
void getWord(char *Word, char *UserName);
void treePrint(TREE *Tree, char **getUnswer, char *UserName);
TREE* createFromData(TREE *Tree, FILE *Data);
