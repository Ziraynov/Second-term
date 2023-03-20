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

int if_letter(char *word, int i) {
    if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= '0' && word[i] <= '9'))
        return 0;
    return 1;

}

char *only_symbols(char *buffer) {
    int word_len = (int) strlen(buffer);
    int i = 0, flag = 0, priority = 0;

    while (if_letter(buffer, i) != 0 || if_letter(buffer, word_len - 1) != 0) {

        if (if_letter(buffer, i) != 0) {
            flag = 1;
            priority = 1;
        }
        if (if_letter(buffer, word_len - 1) != 0)
            flag = 2;

        if (flag == 1 || priority == 1)
            while (if_letter(buffer, i) != 0) {
                for (int k = 0; k < word_len - 1; k++)
                    buffer[k] = buffer[k + 1];
                // buffer = (char *) realloc(buffer, --word_len * sizeof(char));
                buffer[word_len--] = '\0';

            }
        if (flag == 2)
            while (if_letter(buffer, word_len - 1) != 0) {
                buffer[--word_len] = '\0';
            }
    }
    buffer[word_len] = '\0';
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

short_words *struct_short_words(LIFO *head, int *size, int len, int pop) {

    short_words *buffer;
    buffer = (short_words *) calloc(1, sizeof(short_words));
    int i = 0;
    LIFO *p = head;
    while (p != NULL) {
        if (strlen(p->words) < len && p->amount < pop) {
            buffer = (short_words *) realloc(buffer, (i + 1) * sizeof(short_words));
            buffer[i].short_word = (char *) calloc(((int) strlen(p->words) + 1), sizeof(char));
            buffer[i].short_word = p->words;
            i++;
        }
        p = p->next;
    }
    *size = i;
    return buffer;
}

long_words *struct_long_words(LIFO *head, int *size, int len, int pop) {
    long_words *buffer;
    buffer = (long_words *) calloc(1, sizeof(long_words));
    int i = 0;
    LIFO *p = head;
    while (p != NULL) {
        if (strlen(p->words) > len && p->amount > pop) {
            buffer = (long_words *) realloc(buffer, (i + 1) * sizeof(long_words));
            buffer[i].long_word = (char *) calloc(((int) strlen(p->words) + 1), sizeof(char));
            buffer[i].long_word = p->words;
            i++;
        }
        p = p->next;
    }
    *size = i;

    return buffer;
}

int if_real_word(char *buffer, char *word) {
    int i,k=0;
    char *word1=(char*) calloc(100,sizeof(char));
    char *chek_symbol=(char*) calloc(100,sizeof(char));
    while (strcmp(chek_symbol," ")!=0){
        strncat(word1,&buffer[k++],1);
    strncpy(chek_symbol,&buffer[k],1);
    }
    word1=only_symbols(word1);
    if((int) strlen(word1)!=(int)strlen(word))
        return 0;
    for (i = 0; i < (int) strlen(word); i++)
        if (word1[i] == word[i])
            i++;
    if (i == (int) strlen(word)+1)
        return 1;
    return 0;

}

char *long_to_short(char *buffer, char *longword, char *shortword) {
    char *newbuffer = (char *) calloc((int) strlen(buffer) + 100, sizeof(char));
    while (strstr(buffer, longword)) {
        char *start_of_longw;
        start_of_longw = strstr(buffer, longword);
        int len = ((int) strlen(buffer) - (int) strlen(start_of_longw));
        if (if_real_word(start_of_longw, longword) == 1) {
            strncat(newbuffer, buffer, len);
            strcat(newbuffer, shortword);
            buffer += len + (int) strlen(longword);
        } else {
            strncat(newbuffer, buffer, len);
            strcat(newbuffer, longword);
            buffer += len + (int) strlen(longword);
        }
    }
    strncat(newbuffer, buffer, strlen(buffer));
    return newbuffer;
}

char *short_to_long(char *buffer, char *longword, char *shortword) {
    char *newbuffer = (char *) calloc((int) strlen(buffer) + 100, sizeof(char));
    while (strstr(buffer, shortword) != 0) {
        char *start_of_shortw;
        start_of_shortw = strstr(buffer, shortword);
        int len = ((int) strlen(buffer) - (int) strlen(start_of_shortw));
        if (if_real_word(start_of_shortw, shortword) == 1) {
            strncat(newbuffer, buffer, len);
            strncat(newbuffer, longword, (int) strlen(longword));
            buffer += len + (int) strlen(shortword);
        } else {
            strncat(newbuffer, buffer, len);
            strcat(newbuffer, shortword);
            buffer += len + (int) strlen(shortword);
        }

    }
    strncat(newbuffer, buffer, (int) strlen(buffer));
    return newbuffer;
}

char *replace_words(char *buffer, char *lw, char *sw) {
    char *newbuffer = (char *) calloc((int) strlen(buffer) + 100, sizeof(char));
    while (strstr(buffer, lw) != NULL || strstr(buffer, sw) != NULL) {

        if (((int)strstr(buffer, lw) < (int)strstr(buffer, sw)) && strstr(buffer, lw)!=0 || ( strstr(buffer, sw)==NULL  && strstr(buffer,lw)!=0)) {
            char *start_of_longw;
            start_of_longw = strstr(buffer, lw);
            int len = ((int) strlen(buffer) - (int) strlen(start_of_longw));
            if (if_real_word(start_of_longw, lw) == 1) {
                strncat(newbuffer, buffer, len);
                strcat(newbuffer, sw);
                buffer += len + (int) strlen(lw);
            } else {
                strncat(newbuffer, buffer, len);
                strcat(newbuffer, lw);
                buffer += len + (int) strlen(lw);
            }
        } if (((int)strstr(buffer, sw) < (int)strstr(buffer, lw)) && strstr(buffer, sw)!=0  || (strstr(buffer, lw)==NULL && strstr(buffer, sw)!=NULL )) {
            char *start_of_shortw;
            start_of_shortw = strstr(buffer, sw);
            int len = ((int) strlen(buffer) - (int) strlen(start_of_shortw));
            if (if_real_word(start_of_shortw, sw) == 1) {
                strncat(newbuffer, buffer, len);
                strncat(newbuffer, lw, (int) strlen(lw));
                buffer += len + (int) strlen(sw);
            } else {
                strncat(newbuffer, buffer, len);
                strcat(newbuffer, sw);
                buffer += len + (int) strlen(sw);
            }

        }
    }
    strncat(newbuffer, buffer, (int) strlen(buffer));
    return newbuffer;
}

char *new_str(char *buffer, char *longword, char *shortword, int i) {
    char *newbuffer;
    if (strstr(buffer, longword) != NULL && strstr(buffer, shortword) != NULL) {
        newbuffer = replace_words(buffer, longword, shortword);
        return newbuffer;
    }
    if (strstr(buffer, longword) != NULL && strstr(buffer, shortword) == NULL) {

        newbuffer = long_to_short(buffer, longword, shortword);
        return newbuffer;

    }
    if (strstr(buffer, shortword) != NULL && strstr(buffer, longword) == NULL) {

        newbuffer = short_to_long(buffer, longword, shortword);
        return newbuffer;
    }

    return buffer;
}

void rewrite_file(const char *old_file, const char *new_file, long_words *words, short_words *words1, int size) {

    FILE *file = fopen(old_file, "r");
    FILE *newfile = fopen(new_file, "w");
    if (file == NULL || newfile == NULL) {
        printf("Ошибка при открытии файла!");
        return;
    }
    int amount = 0;
    for (int i = 0; i < size; i++)
        amount += 2 + (int) strlen(words[i].long_word) + (int) strlen(words1[i].short_word);
    char *am = (char *) calloc(1, sizeof(char));
    itoa(amount, am, 10);
    fputs(am, newfile);
    fputs(" ", newfile);
    for (int i = 0; i < size; i++) {
        fputs(" ", newfile);
        fputs(words[i].long_word, newfile);
        fputs(" ", newfile);
        fputs(words1[i].short_word, newfile);
    }
    fputs("\n", newfile);
    char *line = (char *) calloc(1601, sizeof(char));
    char *buffer;
    while (fgets(line, 1600, file)) {
        buffer = line;
        for (int i = 0; i < size; i++) {
            buffer = new_str(buffer, words[i].long_word, words1[i].short_word, i);
        }
        fputs(buffer, newfile);
    }
    fclose(file);
    fclose(newfile);
    printf("Файл успешно перезаписан!\n");

}

void free_stack(LIFO **head) {
    while (*head) {
        *head = (*head)->next;
        *head = (LIFO *) realloc(*head, 0 * sizeof(LIFO));
    }
}

int profit(LIFO *head, char *longword, char *shortword) {
    int amountl = 0, amounts = 0;
    LIFO *p = head;
    while (p != NULL) {
        if (strcmp(longword, p->words) == 0)
            amountl = p->amount;
        if (strcmp(shortword, p->words) == 0)
            amounts = p->amount;
        p = p->next;
    }
    return (int) strlen(longword) * amountl - (int) strlen(shortword) * amounts;
}

int amountlw(LIFO *head, char *lw) {
    while (head != NULL) {
        if (strcmp(lw, head->words) == 0)
            return head->amount;
        head = head->next;
    }
}

int amountsw(LIFO *head, char *sw) {
    while (head != NULL) {
        if (strcmp(sw, head->words) == 0)
            return head->amount;
        head = head->next;
    }
}

void new_file(const char *path, LIFO *head, int len_of_words, int popularity) {
    long_words *words;
    short_words *words1;
    int sizelong;
    int sizeshort;
    words = struct_long_words(head, &sizelong, len_of_words, popularity);
    words1 = struct_short_words(head, &sizeshort, len_of_words, popularity);
    if (sizelong > sizeshort)
        sizelong = sizeshort;
    else
        sizeshort = sizelong;
    int prof, amountl, amounts;
    for (int i = 0; i < sizeshort; i++) {
        prof = profit(head, words[i].long_word, words1[i].short_word);
        amountl = amountlw(head, words[i].long_word);
        amounts = amountsw(head, words1[i].short_word);
        printf(" LONG %s am %d SHORT %s am %d PROFIT %d \n", words[i].long_word, amountl, words1[i].short_word, amounts,
               prof);
    }
    const char *pathnew = "C:/Users/ziray/CLionProjects/Secondterm/src/Lab2/newfile.txt";
    free_stack(&head);
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
    int fpos1 = 0;
    while (1) {
        word = word_for_stack(path, *head, &fpos1);
        if (word == NULL)
            break;
        count = count_word_occurrences(path, word, &fpos1);
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

char *word_for_stack(const char *path, LIFO *head, int *fpos) {
    char *word = (char *) malloc(100 * sizeof(char));
    int flag = 0;
    FILE *file;
    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", path);
        exit(EXIT_FAILURE);
    }
    fseek(file, *fpos, SEEK_SET);
    while (fscanf(file, "%s", word) != EOF) {
        for (int i = 0; i < (int) strlen(word); i++) {
            if (if_letter(word, i) == 0)
                break;
            if (i == (int) strlen(word) - 1)
                flag = 2;
        }
        if (flag == 2) {
            flag = 0;
            *fpos = ftell(file);
            continue;
        }
        word = only_symbols(word);
        LIFO *p = head;
        while (p != NULL) {
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
    *fpos = ftell(file);
    if (feof(file) != 0)
        word = NULL;
    fclose(file);
    return word;
}

int count_word_occurrences(const char *path, char *word, int *fpos) {
    FILE *file;
    if ((file = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", path);
        exit(EXIT_FAILURE);
    }
    int flag = 0;
    fseek(file, *fpos, SEEK_SET);
    int count = 1, word_len = (int) strlen(word);
    char *buffer = (char *) calloc(100, sizeof(char));
    while (fscanf(file, "%s", buffer) != EOF) {
        if (feof(file) != 0)
            break;
        for (int i = 0; i < (int) strlen(buffer); i++) {
            if (if_letter(buffer, i) == 0)
                break;
            if (i == (int) strlen(buffer) - 1)
                flag = 2;
        }
        if (flag == 2) {
            flag = 0;
            continue;
        }
        buffer = only_symbols(buffer);
        count += string_string(buffer, word_len, word);
    }
    fclose(file);
    return count;
}

int string_string(char *buffer, int word_len, char *word) {
    int i = 0;
    while (buffer[i] == word[i] && (word[i] != '\0' || buffer[i] != '\0'))
        i++;
    if (i == word_len)
        return 1;
    else return 0;
}

