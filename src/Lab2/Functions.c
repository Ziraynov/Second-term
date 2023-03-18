#include "Main.h"

void print_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Ошибка при открытии файла!");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long int size = ftell(file);

    printf("Размер файла '%s' равен %ld байт\n", filename, size);

    fclose(file);
}

char *only_symbols(char *buffer) {
    while (1) {
        int word_len = (int) strlen(buffer);
        word_len--;
        if (buffer[word_len] == ' ' || buffer[word_len] == '.' || buffer[word_len] == ',' ||
            buffer[word_len] == '!' || buffer[word_len] == '?' || buffer[word_len] == -62 || buffer[word_len] == '[' ||
            buffer[word_len] == ']')
            buffer[word_len] = '\0';
        else break;
    }
    return buffer;
}

LIFO *create(LIFO *head, int count, char *word) {
    LIFO *n;
    n = (LIFO *) malloc(2 * sizeof(LIFO));
    n->next = NULL;
    n->words = word;
    n->amount = count;
    if (head == NULL)
        head = n;
    else {
        n->next = head;
        head = n;
    }
    return head;
}

Short *struct_short_words(LIFO *head, int *size, int len, int pop) {

    Short *buffer;
    buffer = (Short *) malloc(1 * sizeof(Short));
    int i = 0;
    LIFO *p = head;
    while (p != NULL) {
        if (strlen(p->words) <= len  && p->amount < pop) {
            buffer = realloc(buffer, (i + 1) * sizeof(Short));
            buffer[i].short_word = (char *) malloc(strlen(p->words) * sizeof(char));
            buffer[i].short_word = p->words;
            i++;
        }
        p = p->next;
    }
    *size = i;
    for (int k = 0; k < i; k++)
        printf("\nShort: %s\n", buffer[k].short_word);
    return buffer;
}

Long *struct_long_words(LIFO *head, int *size, int len, int pop) {
    Long *buffer;
    buffer = (Long *) malloc(1 * sizeof(Long));
    int i = 0;
    LIFO *p = head;
    while (p != NULL) {
        if (strlen(p->words) >= len * 1.5 && p->amount > pop) {
            buffer = realloc(buffer, (i + 1) * sizeof(Long));
            buffer[i].long_word = (char *) malloc(strlen(p->words) * sizeof(char));
            buffer[i].long_word = p->words;
            i++;
        }
        p = p->next;
    }
    *size = i;
    for (int k = 0; k < i; k++)
        printf("\nLong: %s\n", buffer[k].long_word);
    return buffer;
}

//char *return_for_copy(char *line, int i, int *len_d, Long *words) {
/*char *buffer = (char*)malloc(2000 * sizeof(char));
int len;
int flag=0;
char *temp;
if (strstr(line, words[i].short_word) != 0 || strstr(line, words[i].long_word) != 0)
    if ((strstr(line, words[i].short_word) != NULL && strstr(line, words[i].long_word) != NULL &&
         ((int) strstr(line, words[i].short_word) < (int) strstr(line, words[i].long_word))) ||
        (strstr(line, words[i].short_word) != NULL && strstr(line, words[i].long_word) == NULL)) {
        temp = malloc(2000 * sizeof(char));
        buffer = strstr(line, words[i].short_word);
        len =(int)strlen(line) - (int)strlen(buffer);
        strncpy(temp, line, len);
        *len_d += (int) strlen(temp) + (int) strlen(words[i].short_word);
        strcpy(temp, words[i].long_word);
        flag=1;

    } else {
        flag=1;
        buffer = strstr(line, words[i].long_word);
        temp = (char*)malloc(((int)strlen(line)-(int)strlen(buffer))*sizeof (char));
        temp[((int)strlen(line)-(int)strlen(buffer))]='\0';
        len = (int)strlen(line) - (int)strlen(buffer);
        strncpy(temp, line, len);
        *len_d = strlen(temp) + strlen(words[i].long_word);
        len=strlen(temp);
        strcpy(&temp[len], words[i].short_word);
    }
if (flag == NULL)
    return NULL;
return temp;
}*/
void rewrite_file(const char *old_file, const char *new_file, Long *words, Short *words1, int size) {
    FILE *file = fopen(old_file, "r");
    FILE *newfile = fopen(new_file, "w");
    if (file == NULL || newfile == NULL) {
        printf("Ошибка при открытии файла!");
        return;
    }
    char *line= (char*)malloc(2000*sizeof(char));
    while(fgets(line,2000,file)){
        for(int i=0;i<size;i++){











        }








    }

    fclose(file);
    fclose(newfile);

    printf("Файл успешно перезаписан!");

}

void new_file(const char *path, LIFO *head, int len_of_words, int popularity) {
    Long *words;
    Short *words1;
    int sizelong;
    int sizeshort;
    words = struct_long_words(head, &sizelong, len_of_words, popularity);
    words1 = struct_short_words(head, &sizeshort, len_of_words, popularity);
    if (sizelong > sizeshort)
        sizelong = sizeshort;
    else
        sizeshort = sizelong;
    const char *pathnew = "C:/Users/ziray/CLionProjects/Secondterm/src/Lab2/newfile.txt";
    rewrite_file(path, pathnew, words, words1, sizeshort);

}

void printf_stack(LIFO *head, int *all_words, int *several_len) {
    LIFO *p = head;

    while (p != NULL) {
        printf("%s ", p->words);
        (*several_len) += (int) strlen(p->words);
        printf("%d\n", p->amount);
        (*all_words) += p->amount;
        p = p->next;
    }

}

void stack(const char *path, LIFO **head) {
    int count, number_of_uniq_words = 0;
    int all_words = 0, several_len = 0;
    char *word;
    while (1) {
        word = word_for_stack(path, *head);
        if (word == NULL)
            break;
        count = count_word_occurrences(path, word);
        *head = create(*head, count, word);
        number_of_uniq_words++;
    }
    printf_stack(*head, &all_words, &several_len);
    several_len /= number_of_uniq_words;
    printf("\nALL WORDS:%d UNIQ: %d SEV_LEN%d sevpop %d \n", all_words, number_of_uniq_words, several_len,
           all_words / number_of_uniq_words);
    all_words /= number_of_uniq_words;
    new_file(path, *head, several_len, all_words);
}

char *word_for_stack(const char *path, LIFO *head) {
    char *word = (char *) malloc(100 * sizeof(char));
    int flag = 0;
    FILE *file;
    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", path);
        exit(EXIT_FAILURE);
    }
    while (fscanf(file, "%s", word) != EOF) {
        if (feof(file) != 0) {
            word = NULL;
            break;
        }
        word = only_symbols(word);
        LIFO *p = head;
        while (1) {
            if (p == NULL)
                break;
            if (!strcmp(word, p->words)) {
                p = p->next;
                flag = 1;

            } else
                p = p->next;

        }
        if (flag == 0)
            break;
        flag = 0;
    }
    fclose(file);
    return word;
}

int count_word_occurrences(const char *path, char *word) {
    FILE *file;
    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", path);
        exit(EXIT_FAILURE);
    }
    int count = 0, word_len = (int) strlen(word);
    char *buffer = malloc(1000);
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
                buffer[word_len] == '!' || buffer[word_len] == '?' || buffer[word_len] == -62 ||
                buffer[word_len] == '\0' || buffer[word_len] == ':') && j != word_len)
            i++;
        if (i == word_len)
            cnt++;
        buffer += word_len;
        i = 1;
        j = 0;
    }
    return cnt;

}
