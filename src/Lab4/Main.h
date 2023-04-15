#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define path "C:/Users/ziray/CLionProjects/Secondterm/src/Lab4/data.txt"
#define KB 1024
#define DOT_PATH "C:\\Users\\ziray\\Desktop\\Graphviz\\bin\\dot"

typedef struct Tree {

    char *data;
    struct Tree *right;
    struct Tree *left;
} TREE;
void diagram(TREE *node);
void GetMenuIndex(int *x);
void FreeTree(TREE* tree);
void MakeNewDataBase(char *quest,char *word,TREE *tree,FILE *data,char *get_unswer);
void GetQuestion(char *quest);
void AddNewElementInDataBase(char *word,TREE *tree,FILE *data,char *get_unswer);
int GetUnswer();
void CheckUnswer(char *word,TREE *tree,FILE *data,char *get_unswer);
void GetWord(char *word);
void TreePrint(TREE *tree,char **get_unswer);
TREE* CreateFromData(TREE *tree, FILE *data);
