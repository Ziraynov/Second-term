#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
typedef stuct lifo{
    char *words;
    struct lifo *next;
}LIFO;
void stack(const char *path);