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
int found_count_of_word(const char *path,char *word);
int string_string(char *buffer,int word_len,char *word);
int count_word_occurrences(const char* path,char* word);
char *word_for_stack(const char *path,LIFO *head);

