
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define path "C://Users//user//CLionProjects//Secondterm//src//Lab5//Domens.txt"
#define file 1
#define KB 1024
#define MaxCacheSize 3
#define MaxLenghtDomain 70
#define MaxLenghtIP 15
#define YES 1
#define NO 0
typedef struct cacheEntry {
    char* domain;
    char* value;//это IP
    struct cacheEntry* next;
    struct cacheEntry* prev;
}cacheEntryT;
typedef struct cache {

    cacheEntryT* table;
} cacheT;

FILE *checkFile(char *mode);
int menu(FILE *DNS,cacheT **cache,cacheEntryT **Head,cacheEntryT **Tail);
cacheT *createCache();
char *getFromFile(char *word, FILE *DNS,int mode, cacheT **cache, cacheEntryT **Head, cacheEntryT **Tail);
void freCache(cacheT **cache,cacheEntryT **Head,cacheEntryT **Tail);
