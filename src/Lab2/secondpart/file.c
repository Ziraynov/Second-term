#include "file.h"

int if_letter(char *word, int i) {
    if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= '0' && word[i] <= '9'))
        return 0;
    return 1;

}

int if_real_word(char *buffer, char *word) {
    int i;
    if(if_letter(buffer,(int)strlen(word))==0)
        return 0;
    for (i = 0; i < (int) strlen(word); i++)
        if (buffer[i] == word[i])
            i++;
    if (i == (int) strlen(word) && if_letter(buffer, i) == 1)
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

void rewrite_file(const char *old_file, const char *new_file) {

    FILE *file = fopen(old_file, "r");
    FILE *newfile = fopen(new_file, "w");
    if (file == NULL || newfile == NULL) {
        printf("Ошибка при открытии файла!");
        return;
    }
    int j = 0, k = 0, cnt = 1;
    char *word = (char *) calloc(1, sizeof(char));
    char **words_long = (char **) calloc(1, sizeof(char *));
    char **wordss = (char **) calloc(1, sizeof(char *));
    fscanf(file, "%s", word);
    char *buffer=(char*) calloc(atoi(word)+7,sizeof(char));
    fgets(buffer,atoi(word)+6,file);
    word=strtok(buffer," ");
    while(word!=NULL)
    {

        if(cnt%2!=0)
        {
            words_long = realloc(words_long, (j + 1) * sizeof(char*));
            words_long[j++] = word;
        }
        else
        {
            wordss= realloc(wordss, (k + 1) * sizeof(char*));
            wordss[k++] = word;
        }
        word=strtok(NULL," ");
        cnt++;
    }
for(int i=0;i<j;i++)
{
    printf(" LONG %s SHORT %s\n",words_long[i],wordss[i]);
}

    char *line = (char *) calloc(1601, sizeof(char));
    while (fgets(line, 1600, file)) {

        for (int i = 0; i < j; i++) {
            buffer = new_str(line, words_long[i], wordss[i], i);
        }
        fputs(buffer, newfile);
    }
    fclose(file);
    fclose(newfile);
    printf("Файл успешно перезаписан!\n");

}

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

int main() {

    const char *path1 = "C:/Users/ziray/CLionProjects/Secondterm/src/Lab2/newfile.txt";
    const char *path2 = "C:/Users/ziray/CLionProjects/Secondterm/src/Lab2/secondpart/newone.txt";
    rewrite_file(path1, path2);
    print_file_size(path2);
    return 0;
}