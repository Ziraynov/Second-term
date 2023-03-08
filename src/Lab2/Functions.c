#include "Main.h"

char *word_for_stack(const char *path);

void stack(const char *path, LIFO **head) {
    LIFO *buffer = malloc(sizeof(LIFO));
    int num = 0, count;
    char *word;
    printf("123");
    word = word_for_stack(path,&head);

    LIFO *n;
    n = (LIFO *) malloc(sizeof(LIFO));
    n->next = NULL;
    n->words = word;
    n->amount=count;
    if (head == NULL)
        head = n;
    else {
        n->next = head;
        head = n;
    }
}

char *word_for_stack(const char *path,LIFO *head) {
    char *word;
    FILE *file;
    if ((file = fopen(file, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", file);
        exit(EXIT_FAILURE);
    }

    while(fscanf(file,"%s",word)!=EOF) {

        LIFO *p = head;
        while (p != NULL)
        {
            if(word==p->words)
            p = p->next;
            else break;
        }
    }
    return word;
}

char *memory_for_word(char *word) {
    char *word_len;
    word_len = (char *) calloc((int) strlen(word), sizeof(char));
    return word_len;
}

int count_word_occurrences(const char *path, char *word) {
    FILE *file;
    int count = 0, word_len = (int) strlen(word);
    char *buffer = malloc(1000);
    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", path);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, 1000, file) != NULL) {
        count += string_string(buffer, word_len, word);
    }

    fclose(file);

    return count;
}

int string_string(char *buffer, int word_len, char *word) {
    int i = 1, j = 0, cnt = 0;
    while (strstr(buffer, word) != NULL) {
        buffer = strstr(buffer, word);
        while (buffer[j] == word[j++] &&
               (buffer[word_len] == ' ' || buffer[word_len] == '.' || buffer[word_len] == ',' ||
                buffer[word_len] == '!' || buffer[word_len] == '?' || buffer[word_len] == -62) && j != word_len)
            i++;
        if (i == word_len)
            cnt++;
        buffer += word_len;
        i = 1;
        j = 0;
    }
    return cnt;

}
