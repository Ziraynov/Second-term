#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <limits.h>
typedef struct lifo{
    char *words;
    int amount;
    struct lifo *next;
}LIFO;
typedef struct{
    char *long_word;
}Long;
typedef struct{
    char *short_word;
}Short;
void print_file_size(const char *filename);
//void changePairOneString(char** str,const LEN* pair,int i);
Long *struct_long_words(LIFO *head,int *size,int len,int pop);
Short *struct_short_words(LIFO *head, int *size,int len,int pop);
void stack(const char *path,LIFO **head);
char *file(const char *path,int *amount);
int found_count_of_word(const char *path,char *word);
int string_string(char *buffer,int word_len,char *word);
int count_word_occurrences(const char* path,char* word);
char *word_for_stack(const char *path,LIFO *head);
LIFO *create(LIFO *head, int count, char *word);

