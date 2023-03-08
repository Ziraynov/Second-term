#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
typedef struct lifo{
    char *words;
    int amount;
    struct lifo *next;
}LIFO;
void stack(const char *path,LIFO **head);
char *file(const char *path,int *amount);
char *memory_for_word(char* word);
