#include "file.h"

int if_letter(const char *word, int i, int key) {
    if (key == 0 && (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') ||
        (word[i] >= '0' && word[i] <= '9'))
        return 0;
    if (key == 1 && (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') ||
        (word[i] >= '0' && word[i] <= '9') || word[i] == -103)
        return 0;
    return 1;

}

void check (char *buffer,int i,int *flag,int priority,int word_len)
{
    if (if_letter(buffer, i,1) != 0) {
        *flag = 1;
        priority = 1;
    }
    if (if_letter(buffer, word_len - 1,1) != 0)
        *flag = 2;

    if (*flag == 1 || priority == 1)
        while (if_letter(buffer, i,1) != 0) {
            for (int k = 0; k < word_len - 1; k++)
                buffer[k] = buffer[k + 1];
            buffer[word_len--] = '\0';

        }
}
char *only_symbols(char *buffer) {
    int word_len = (int) strlen(buffer);
    int i = 0;
    int flag = 0;
    int priority = 0;

    while (if_letter(buffer, i,1) != 0 || if_letter(buffer, word_len - 1,1) != 0) {

        check(buffer,i,&flag,priority,word_len);
        if (flag == 2)
            while (if_letter(buffer, word_len - 1,1) != 0) {
                buffer[--word_len] = '\0';
            }
    }
    buffer[word_len] = '\0';
    return buffer;
}
int if_real_word(const char *buffer,const char *word) {
    int k = 0;
    char *word1 = (char *) calloc((int) strlen(buffer), sizeof(char));
    char *chek_symbol = (char *) calloc((int) strlen(buffer), sizeof(char));
    while (strcmp(chek_symbol, " ") != 0) {
        if (strcmp(chek_symbol, "\n") == 0) { break; }

        strncat_s(word1, 1, &buffer[k],2);
        k++;
        strncpy_s(chek_symbol, 1, &buffer[k],2);
    }
    if (word1[(int) strlen(word1)] == '\n')
        word1[(int) strlen(word1)] = '\0';
    word1 = only_symbols(word1);
    if ((int) strlen(word1) != (int) strlen(word))
        return 0;
    k = 0;
    for (int i = 0; i < (int) strlen(word); i++)
        if (word1[i] == word[i])
            k++;
    if (k == (int) strlen(word))
        return 1;
    return 0;

}



char *long_to_short(const char *buffer,const char *longword,const char *shortword) {
    char *newbuffer = (char *) calloc((int) strlen(buffer) + 100, sizeof(char));
    while (strstr(buffer, longword)) {
        const char *start_of_longw;
        start_of_longw = strstr(buffer, longword);
        int len = ((int) strlen(buffer) - (int) strlen(start_of_longw));
        if (if_real_word(start_of_longw, longword) == 1 && if_letter(buffer, len - 1,1) == 1) {
            strncat_s(newbuffer, len, buffer,len-1);
            strcat_s(newbuffer, 10000,shortword);
            buffer += len + (int) strlen(longword);
        } else {
            strncat_s(newbuffer, len, buffer,len-1);
            strcat_s(newbuffer, 10000,longword);
            buffer += len + (int) strlen(longword);
        }
    }
    strncat_s(newbuffer,strlen(buffer) ,buffer, strlen(buffer)-1);
    return newbuffer;
}

char *short_to_long(const char *buffer,const  char *longword,const char *shortword) {
    char *newbuffer = (char *) calloc((int) strlen(buffer) + 100, sizeof(char));
    while (strstr(buffer, shortword) != 0) {
        const   char *start_of_shortw;
        start_of_shortw = strstr(buffer, shortword);
        int len = ((int) strlen(buffer) - (int) strlen(start_of_shortw));
        if (if_real_word(start_of_shortw, shortword) == 1 && if_letter(buffer, len - 1,1) == 1) {
            strncat_s(newbuffer, len,buffer, len-1);
            strncat_s(newbuffer,(int) strlen(longword) ,longword, (int) strlen(longword)-1);
            buffer += len + (int) strlen(shortword);
        } else {
            strncat_s(newbuffer,len, buffer, len-1);
            strcat_s(newbuffer, 10000,shortword);
            buffer += len + (int) strlen(shortword);
        }

    }
    strncat_s(newbuffer,(int) strlen(buffer), buffer, (int) strlen(buffer)-1);
    return newbuffer;
}
char *replace_words(const char *buffer,const  char *lw,const char *sw) {
    char *newbuffer = (char *) calloc((int) strlen(buffer) + 100, sizeof(char));
    while (strstr(buffer, lw) != NULL || strstr(buffer, sw) != NULL) {

        if (((int*) strstr(buffer, lw) < (int*) strstr(buffer, sw)) && strstr(buffer, lw) != 0 ||
            (strstr(buffer, sw) == NULL && strstr(buffer, lw) != NULL)) {
            const char *start_of_longw;
            start_of_longw = strstr(buffer, lw);
            int len = ((int) strlen(buffer) - (int) strlen(start_of_longw));
            if (if_real_word(start_of_longw, lw) == 1 && if_letter(buffer, len - 1,1) == 1) {
                strncat_s(newbuffer, len,buffer, len-1);
                strcat_s(newbuffer,10000, sw);
                buffer += len + (int) strlen(lw);
            } else {
                strncat_s(newbuffer, len,buffer, len-1);
                strcat_s(newbuffer,100000, lw);
                buffer += len + (int) strlen(lw);
            }
        }
        if (((int*) strstr(buffer, sw) < (int*) strstr(buffer, lw)) && strstr(buffer, sw) != 0 ||
            (strstr(buffer, lw) == NULL && strstr(buffer, sw) != NULL)) {
        const    char *start_of_shortw;
            start_of_shortw = strstr(buffer, sw);
            int len = ((int) strlen(buffer) - (int) strlen(start_of_shortw));
            if (if_real_word(start_of_shortw, sw) == 1 && if_letter(buffer, len - 1,1) == 1) {
                strncat_s(newbuffer,len, buffer, len);
                strncat_s(newbuffer, (int) strlen(lw),lw, (int) strlen(lw));
                buffer += len + (int) strlen(sw);
            } else {
                strncat_s(newbuffer, len,buffer, len);
                strcat_s(newbuffer,10000, sw);
                buffer += len + (int) strlen(sw);
            }

        }
    }
    strncat_s(newbuffer,(int) strlen(buffer), buffer, (int) strlen(buffer));
    return newbuffer;
}

const char *new_str(const char *buffer,const  char *longword,const char *shortword) {
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

void decomprassing(const char *old_file, const char *new_file) {

    FILE *file;
    fopen_s(&file,old_file, "r");
    FILE *newfile;
    fopen_s(&newfile,new_file, "w");
    if (file == NULL || newfile == NULL) {
        printf("Ошибка при открытии файла!");
        return;
    }
    int j = 0;
    int k = 0;
    int cnt = 1;
    char *word = (char *) calloc(2, sizeof(char));
    char **words_long = (char **) calloc(2, sizeof(char *));
    char **wordss = (char **) calloc(2, sizeof(char *));
    fscanf_s(file, "%s", word);
    const char *buffer = (char *) calloc(atoi(word) + 10, sizeof(char));
    fgets((char*)buffer, atoi(word) + 9, file);
    word = (char*)strtok_r((char*)buffer, " ",(char**)&buffer);
    while (word != NULL) {
        if (strcmp(&word[(int) strlen(word) - 1], "\n") == 0)
            word[(int) strlen(word) - 1] = '\0';
        if (cnt % 2 != 0) {
            words_long = realloc(words_long, (j + 1) * sizeof(char *));
            words_long[j++] = word;
        } else {
            wordss = realloc(wordss, (k + 1) * sizeof(char *));
            wordss[k++] = word;
        }
        word = (char*)strtok_r(NULL, " ",NULL);
        cnt++;
    }
    for (int i = 0; i < j; i++) {
        printf(" LONG %s SHORT %s\n", words_long[i], wordss[i]);
    }

    char *line = (char *) calloc(5001, sizeof(char));
    while (fgets(line, 5000, file)) {
        buffer = line;
        for (int i = 0; i < j; i++) {
            buffer = new_str(buffer, words_long[i], wordss[i]);
        }
        fputs(buffer, newfile);
    }
    fclose(file);
    fclose(newfile);
    printf("Файл успешно перезаписан!\n");

}

void print_file_size(const char *filename) {
    FILE *file;
    fopen_s(&file,filename, "rb");

    if (file == NULL) {
        printf("Ошибка при открытии файла!");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long int size = ftell(file);

    printf("Размер файла '%s' равен %ld байт\n", filename, size);

    fclose(file);
}

int main() {
    const char *path = "C:/Users/ziray/CLionProjects/Secondterm/src/Lab2/book.txt";
    const char *path1 = "C:/Users/ziray/CLionProjects/Secondterm/src/Lab2/newfile.txt";
    const char *path2 = "C:/Users/ziray/CLionProjects/Secondterm/src/Lab2/secondpart/newone.txt";
    decomprassing(path1, path2);
    print_file_size(path);
    print_file_size(path2);
    return 0;
}