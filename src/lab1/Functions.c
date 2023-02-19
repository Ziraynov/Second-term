#include "Header.h"
void stop(monitor* array, int* len)
{
	exit(EXIT_SUCCESS);
}
//const char* const monitor_producers[] =
//{
//        [LG] = "LG",
//        [SUMSUNG] = "SUMSUNG",
//        [GigaByte] = "GigaBite",
//        [AOC] = "AOC",
//};

//void add(monitor* array, int* len)
//{
//	
//
//}
//void sort(monitor* array, int* len)
//{
//	
//
//}
//void rem(monitor* array, int* len)
//{
//
//
//}
char* file(char path[])
{
    FILE* fp;
    fp=fopen("C:/projects/second term/Lab1/monitors.html", "r");
	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buffer = calloc(len, 1);
   fread(buffer, 1, len, fp);
	fclose(fp);
	return buffer;
}
int if_letter(char* s)
{
    if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
        return 1;
    return 0;
}

int second_word( char *pre, char *array)
{
    int i = 1,count=0,ret=1,flag=0;
    while (array[i] != '\0') 
    {
        if (if_letter(array[i - 1]) == 0 && if_letter(array[i]) == 1)
        {
            flag = 1;
            int p = i;
            while (1)
            {
                if (pre[count++] != array[p++])
                    ret = 0;
                if (array[p] == ' ')
                    break;
            }

        }
        if (flag)
            break;
        i++;
        count = 0;
}
    return ret;
    
        
        
}
string* split(char* input, char* delimiter) {
    int targetsize = 0;
    string* str = malloc(sizeof(string));


    str->str = NULL;
    str->len = 0;
    char* pos;
    char* oldpos = input;
    int newsize;
    int dlen = strlen(delimiter);
    do {
        pos = strstr(oldpos, delimiter);
        if (pos) {
            newsize = pos - oldpos;
        }
        else {
            newsize = strlen(oldpos);
        }
        char* newstr = malloc(sizeof(char) * (newsize + 1));
        strncpy(newstr, oldpos, newsize);
        newstr[newsize] = '\0';
        oldpos = pos + dlen;
        str->str = realloc(str->str, (targetsize + 1) * sizeof(char*));
        str->str[targetsize++] = newstr;
        str->len++;
    } while (pos != NULL);
    return str;
}
//string* split(char* input, char* delimiter) {
 /*   int targetsize = 0;
    string* array = malloc(sizeof(string));


    array->array = NULL;
    array->len = 0;
    char* pos;
    char* oldpos = input;
    int newsize;
    int dlen = strlen(delimiter);
    do {
        pos = strstr(oldpos, delimiter);
        if (pos) {
            newsize = pos - oldpos;
        }
        else {
            newsize = strlen(oldpos);
        }
        char* newstr = malloc(sizeof(char) * (newsize + 1));
        strncpy(newstr, oldpos, newsize);
        newstr[newsize] = '\0';
        oldpos = pos + dlen;
        array->array = realloc(array->array, (targetsize + 1) * sizeof(char*));
        array->array[targetsize++] = newstr;
        array->len++;
    } while (pos != NULL);
    return array;
}*/
int comp_name(monitor* a, monitor* b) {
    return strcmp(a->name, b->name);
}

int comp_price(monitor* a, monitor* b) {

    return (a->price < b->price) - (a->price > b->price);
}

int comp_producer(monitor* a, monitor* b) {
    return a->producer - b->producer;
}

int comp_producer_matrix(const monitor* a, const monitor* b) {

    if (b->producer < a->producer) {
        return 1;
    }
    else if (a->producer < b->producer) {
        return -1;
    }
    else {
        return (b->producer < a->producer) - (a->producer < b->producer);
    }
}

int comp_name_price(const monitor* a, const monitor* b) {
    if ((a->price > b->price) - (a->price < b->price) != 0) {
        return (a->price > b->price) - (a->price < b->price);
    }
    else {
        return strcmp(a->name, b->name);
    }
}