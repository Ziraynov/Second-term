#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define path "C:/Users/ziray/CLionProjects/Secondterm/src/Lab4/data.txt"
#define KB 1024
#define SPACE " "
typedef struct Tree {

    char *data;
    struct Tree *right;
    struct Tree *left;
} TREE;
void GetUserName(char *Name);
void AddLogs(char *UserUnswer, char *UserName);
void Functions(int *x);
void OpenSite(char *UserName);
void Diagram(TREE *Tree);
void GetMenuIndex(int *x,char *UserName);
void FreeTree(TREE* Tree);
void MakeNewDataBase(char *Quest, char *Word, TREE *Tree, FILE *Data, char *GetUnswer);
void GetQuestion(char *Quest, char *UserName);
void AddNewElementInDataBase(char *Word, TREE *Ttree, FILE *Data, char *getUnswer, char *UserName);
int GetUnswer(char *UserName);
void CheckUnswer(char *Word, TREE *Tree, FILE *Data, char *getUnswer, char *UserName);
void GetWord(char *Word, char *UserName);
void TreePrint(TREE *Tree, char **getUnswer, char *UserName);
TREE* CreateFromData(TREE *Tree, FILE *Data);
