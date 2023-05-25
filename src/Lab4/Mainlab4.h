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
void addLogs(const char *UserUnswer,const char *UserName);
void functions(int *x);
void openSite(const char *UserName);
void diagram(TREE *Tree);
void getMenuIndex(int *x, const char *UserName);
void freeTree(TREE* Tree);
void makeNewDataBase(char *Quest, char *Word, TREE *Tree, FILE *Data, const char *GetUnswer);
void getQuestion(char *Quest, const char *UserName);
void addNewElementInDataBase(char *Word, TREE *Ttree, FILE *Data,const char *getUnswer,const char *UserName);
int getUn(const char *UserName);
void checkUnswer(char *Word, TREE *Tree, FILE *Data,const  char *getUnswer,const  char *UserName);
void getWord(char *Word, const char *UserName);
void treePrint(TREE *Tree, const char **getUnswer,const  char *UserName);
TREE* createFromData(TREE *Tree, FILE *Data);
