/*struct CASH {
    char* id;
    struct CASH* next;
    struct CASH* prev;
}typedef cash;

struct HASH{
    char* key;
    struct CASH* id;
}typedef hash;*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define path "C://Users//user//CLionProjects//Secondterm//src//Lab5//Domens.txt"
#define file 1
#define KB 1024
#define MaxCacheSize 2
#define MaxLenghtDomain 70
#define MaxLenghtIP 15
#define YES 1
#define NO 0
typedef struct cacheEntry {
    char* key;//это доменное имя
    char* value;//это IP
    struct cacheEntry* next;
    struct cacheEntry* prev;
}cacheEntryT;
typedef struct cache {
    int size;
    cacheEntryT** table;
} cacheT;

FILE *checkFile(char *mode);
int menu(FILE *DNS,cacheT *cache);
cacheT *createCache();
void foundAllIPs(FILE *DNS, cacheT *cache,int mode,char *word);

