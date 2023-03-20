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
    char *short_word;
}short_words;
typedef struct{
    char *long_word;
}long_words;
void rewrite_file(const char *old_file, const char *new_file, long_words *words, short_words *words1, int size) ;

void print_file_size(const char *filename);
long_words *struct_long_words(LIFO *head,int *size,int len,int pop);
short_words *struct_short_words(LIFO *head, int *size,int len,int pop);
void stack(const char *path,LIFO **head);
int string_string(char *buffer,int word_len,char *word);
int count_word_occurrences(const char* path,char* word,int *fpos);
char *word_for_stack(const char *path,LIFO *head,int *fpos);
LIFO *create(LIFO *head, int count, char *word);

