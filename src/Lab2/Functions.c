#include "Main.h"
void stack (const char *path,LIFO **head){
LIFO* buffer=malloc(sizeof(LIFO));
int amount;
char *word=file(path,&amount);
word=file(path,&amount);
if(!buffer)
{
    buffer->next=*head;
    buffer->amount=amount;
    buffer->words=memory_for_word(word);
    buffer->words=word;
    *head=buffer;
}

}
char *memory_for_word(char* word)
{
    char * word_len;
    word_len=(char*) calloc(strlen(word),sizeof(char));
    return word_len;
}
char *file(const char *path,int *amount){
    FILE* fp= fopen("path","r+");

    fclose(fp);
    return arr;
};
