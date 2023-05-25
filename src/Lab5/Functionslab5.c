#include "Mainlab5.h"

cacheT *createCache() {
    cacheT *cache = malloc(sizeof(cacheT));
    cache->table = (cacheEntryT *) calloc(MaxCacheSize, sizeof(cacheEntryT));
    for (int i = 0; i < MaxCacheSize; i++) {
        cache->table[i].domain = NULL;
    }
    return cache;
}

void freCache(cacheT **cache, cacheEntryT **Head, cacheEntryT **Tail) {
    while (*Head != NULL) {
        cacheEntryT *tmp=*Head;
        free(tmp);
        *Head = (*Head)->next;
        *Tail = NULL;
    }
    free((*cache)->table);
    free(*cache);

}

unsigned long hashFunction4(const char *str) {
    unsigned int hashval = 0;
    for (; *str != '\0'; str++) {
        hashval += *str;
    }
    return hashval % MaxCacheSize;
}

unsigned long hashFunction2(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = hash * 131 + (*str++);
    }
    return hash % MaxCacheSize;
}

unsigned long hashFunction3(const char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = (int) (*str++)))
        hash = hash * 33 + c; /* hash * 33 + c */

    return hash % MaxCacheSize;
}

unsigned long hashFunction1(const char *str) {
    unsigned int hash = 0;
    int len = (int) strlen(str);
    for (int i = 0; i < len; i++) {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash % MaxCacheSize;
}

unsigned long hashFunction(const char *key) {
    unsigned long hash = MaxCacheSize;
    char *str = strdup(key);
    int c;
    while ((c = (int) (*str++)))
        hash = ((hash << 5) + hash) + c;
    return hash % MaxCacheSize;
}

void moveToTop(cacheEntryT **Head, const char *domain) {
    if (strcmp((*Head)->domain, domain) == 0)
        return;
    else {
        cacheEntryT *current = *Head;
        while (strcmp(current->domain, domain) != 0) {
            current = current->next;
        }
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }

        current->prev = NULL;
        current->next = *Head;
        (*Head)->prev = current;
        *Head = current;

    }

}

int addList(cacheT **table, unsigned long hash, const char *domain, const char *IP, cacheEntryT **Head,
            cacheEntryT **Tail) {
    if ((*table)->table[hash].domain == NULL) {
        (*table)->table[hash].domain = strdup(domain);
        (*table)->table[hash].value = strdup(IP);
        (*table)->table[hash].next = NULL;
        (*table)->table[hash].prev = NULL;
        if (*Head == NULL) {
            *Head = &(*table)->table[hash];
            *Tail = &(*table)->table[hash];
        } else {
            (*table)->table[hash].next = *Head;
            (*Head)->prev = &(*table)->table[hash];
            *Head = &(*table)->table[hash];
        }
        return 1;
    } else {
        if (strcmp((*table)->table[hash].domain, domain) == 0) {
            moveToTop(Head, domain);
            return 1;
        }
    }
    return 0;
}

int
removeLate(cacheT **table, unsigned long hash, const char *str, const char *domain, const char *IP, cacheEntryT **Head,
            unsigned long x, unsigned long y) {
    if ((*table)->table[hash].next == NULL && str != NULL && (x == y)) {
        (*table)->table[hash].domain = strdup(domain);
        (*table)->table[hash].value = strdup(IP);
        moveToTop(Head, domain);
        return 1;
    }
    return 0;
}

void addToCache(cacheT **table, const char *domain, const char *IP, cacheEntryT **Head, cacheEntryT **Tail) {
    unsigned int hash = hashFunction(domain);
    unsigned int hash1 = hashFunction1(domain);
    unsigned int hash3 = hashFunction3(domain);
    unsigned int hash2 = hashFunction3(domain);
    unsigned int hash4 = hashFunction4(domain);

    const char *str = NULL;
    int flag;
    flag = addList(table, hash, domain, IP, Head, Tail);
    if (flag == 0) {
        flag = addList(table, hash1, domain, IP, Head, Tail);
        if (flag != 1) {
            flag = addList(table, hash2, domain, IP, Head, Tail);
        }
        if (flag != 1) {
            flag = addList(table, hash3, domain, IP, Head, Tail);
        }
        if (flag != 1) {
            flag = addList(table, hash4, domain, IP, Head, Tail);
        }
    }
    if (flag == 1)
        return;
    int count = 0;
    cacheEntryT *tmp = *Head;
    while (count != MaxCacheSize && tmp != NULL) {
        count++;
        if (count == MaxCacheSize)
            str = tmp->domain;
        tmp = tmp->next;

    }
    if (count == MaxCacheSize) {

        flag = removeLate(table, hash, str, domain, IP, Head,  hashFunction(str), hashFunction(domain));
        if (flag != 1)
            flag = removeLate(table, hash1, str, domain, IP, Head,  hashFunction1(str), hashFunction1(domain));
        if (flag != 1)
            flag = removeLate(table, hash3, str, domain, IP, Head,  hashFunction3(str), hashFunction3(domain));
        if (flag != 1)
            flag = removeLate(table, hash2, str, domain, IP, Head,  hashFunction2(str), hashFunction2(domain));
        if (flag != 1)
            flag = removeLate(table, hash4, str, domain, IP, Head,  hashFunction4(domain), hashFunction4(domain));
        for (int i = 0; i < MaxCacheSize; i++) {
            if (flag == 1)
                break;
            flag = removeLate(table, i, str, domain, IP, Head,  hashFunction4(domain), hashFunction4(domain));
        }
    }

}

FILE *checkFile(char *mode) {
    if (fopen(path, mode) != NULL)
        return fopen(path, mode);
    else
        exit(file);
}

void getIndex(int *x, int a, int b) {
    while (!scanf("%d", x) && getchar() != '\n' && (*x <= a || *x >= b)) {
        printf("Error input, try againg!");
        rewind(stdin);
    }
}

void getWord(char *word) {
    scanf("%s", word);
}

int checkInFIle(FILE *DNS, const char *word) {
    fseek(DNS, 0, SEEK_SET);
    char *str = (char *) calloc(KB, sizeof(char));
    while (fgets(str, KB - 1, DNS) != NULL) {
        if (strstr(str, word) != NULL)
            return 1;
    }
    return 0;
}

int validDomain(FILE *DNS, const char *word) {
    if ((int) strlen(word) <= MaxLenghtDomain && checkInFIle(DNS, word) == 0)
        return 1;
    return 0;
}

void errorDomain(char **word) {
    int x;
    printf("Your domain is already in database,or not valid.Do you wanna try again?\nEnter 1 if \"yes\" or 0 if \"not\":");
    getIndex(&x, 0, 1);
    if (x == 1) {
        printf("Enter new domain:");
        getWord(*word);
    } else
        *word = NULL;
}

int fisrtLetter(const char *str) {
    if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z'))
        return 1;
    return 0;
}

int checkNumbers(const char *str) {
    if (fisrtLetter(str) == 1)
        return 0;
    if (atoi(str) >= 0 && atoi(str) <= 255)
        return 1;
    return 0;
}

int findDotsNumbers(char *IP) {
    int count = 1;
    char *str=(char*) calloc(KB,sizeof(char));
    strtok_r(IP, ".", &str);
    if (checkNumbers(str) == 0)
        return 0;
    strtok_r(IP, ".", &str);
    while (checkNumbers(str) != 0) {
        count++;
        if (count == 4)
            return 1;
    }
    return 0;
}

int existingDomainIP(FILE *DNS, char *IP) {
    fseek(DNS, 0, SEEK_SET);
    char *str = (char *) calloc(KB, sizeof(char));
    while (feof(DNS) == 0) {
        fscanf(DNS, "%s", str);
        if (strcmp(str, IP) == 0)
            return 1;
        for (int i = 0; i <= 2; i++)
            fscanf(DNS, "%s", str);

    }
    return 0;
}

int validIP(FILE *DNS, char *IP) {

    if ((int) strlen(IP) == MaxLenghtIP && findDotsNumbers(IP) == 1)
        return 1;
    if (existingDomainIP(DNS, IP) == 1)
        return 2;

    return 0;
}

void putInFile(char *word, char *IP, FILE *DNS, int mode) {
    if (DNS != NULL)
        fclose(DNS);
    DNS = checkFile("a+");
    fputs(word, DNS);
    fputs(" IN ", DNS);
    if (mode == 0)
        fputs(" A ", DNS);
    else
        fputs("CNAME ", DNS);
    fputs(IP, DNS);
    fputs("\n", DNS);
    if(DNS!=NULL)
    fclose(DNS);
}

void add(FILE *DNS, cacheT **cache, cacheEntryT **Head, cacheEntryT **Tail) {
    char *word = (char *) calloc(KB, sizeof(char));
    char *IP = (char *) calloc(KB, sizeof(char));
    printf("Enter your domain:");
    getWord(word);
    if (validDomain(DNS, word) == 0)
        errorDomain(&word);
    if (word == NULL)
        return;
    printf("Enter your IP:");
    getWord(IP);
    char *str = strdup(IP);
    char *str2 = strdup(IP);
    char *str3 = strdup(IP);
    if (validIP(DNS, str) == 0)
        printf("This IP is not valid or we already have it.\n");
    else if (validIP(DNS, str2) == 1) {
        putInFile(word, IP, DNS, 0);
        addToCache(cache, word, IP, Head, Tail);
    } else {
        if (validIP(DNS, str3) == 2) {
            putInFile(word, IP, DNS, 1);
            getFromFile(word, DNS, YES, cache, Head, Tail);
        }
    }
}

char *get(cacheT *cache, char *key, unsigned long hash) {
    if (cache->table[hash].domain != NULL) {
        if (strcmp(cache->table[hash].domain, key) == 0)
            return cache->table[hash].value;
    }
    return NULL;
}

char *getFromCache(cacheT *cache, char *key) {
    unsigned long hash = hashFunction(key);
    unsigned long hash1 = hashFunction1(key);
    unsigned long hash3 = hashFunction3(key);
    unsigned long hash2 = hashFunction2(key);
    unsigned long hash4 = hashFunction4(key);

    if (get(cache, key, hash) != NULL)
        return get(cache, key, hash);
    if (get(cache, key, hash1) != NULL)
        return get(cache, key, hash);
    if (get(cache, key, hash2) != NULL)
        return get(cache, key, hash2);
    if (get(cache, key, hash3) != NULL)
        return get(cache, key, hash3);
    if (get(cache, key, hash4) != NULL)
        return get(cache, key, hash4);
    for (int i = 0; i < MaxCacheSize; i++) {
        if (get(cache, key, i) != NULL)
            return get(cache, key, i);
    }
    return NULL;

}

char *getFromFile(char *word, FILE *DNS, int mode, cacheT **cache, cacheEntryT **Head, cacheEntryT **Tail) {
    fseek(DNS, 0, SEEK_SET);
    char *str = (char *) calloc(KB, sizeof(char));
    char *str2 = (char *) calloc(KB, sizeof(char));
    do {
        fscanf(DNS, "%s", str);
        for (int i = 0; i <= 2; i++)
            fscanf(DNS, "%s", str2);
    } while (strcmp(str, word) != 0 && feof(DNS) == 0);
    if (validIP(DNS, strdup(str2)) != 1)
        str2 = getFromFile(str2, DNS, NO, cache, Head, Tail);
    if (mode == 1)
        addToCache(cache, word, str2, Head, Tail);
    return str2;

}

void foundIP(FILE *DNS, cacheT **cache, char *word, cacheEntryT **Head, cacheEntryT **Tail) {
    char *str1 = getFromCache(*cache, word);
    if (str1 != NULL) {
        printf("Your IP(got by cache):%s\n", str1);
        addToCache(cache, word, getFromCache(*cache, word), Head, Tail);
    } else {
        char *str = getFromFile(word, DNS, YES, cache, Head, Tail);
        if (str == NULL) {
            printf("Not exist, or not valid domain\n");
        } else
            printf("Your IP:%s\n", str);

    }

}

void getIpByDomain(FILE *DNS, cacheT **cache, cacheEntryT **Head, cacheEntryT **Tail) {
    printf("Enter a domain:");
    char *word = (char *) calloc(KB, sizeof(char *));
    getWord(word);
    if (validDomain(DNS, word) == 1 || validIP(DNS, strdup(word)) == 1) {
        printf("Error domain!\n");
        return;
    }
    foundIP(DNS, cache, word, Head, Tail);
}


void showCache(cacheEntryT *Head) {
    printf("Cache Table:\n");
    while (Head != NULL) {
        printf("Domain: %s------>IP:%s   ", Head->domain, Head->value);
        printf("\n");
        Head = Head->next;

    }
}

int findIpInFile(FILE *DNS, char *IP) {
    char *word = (char *) calloc(KB, sizeof(char *));
    if (validIP(DNS, strdup(IP)) == 2 || validIP(DNS, strdup(IP)) == 0)
        return 0;
    fseek(DNS, 0, SEEK_SET);
    while (feof(DNS) == 0) {
        fscanf(DNS, "%s", word);
        if (strcmp(IP, word) == 0)
            return 1;
    }
    return 0;
}

void foundAllDomains(FILE *DNS) {
    char *word = (char *) calloc(KB, sizeof(char *));
    char *buffer = (char *) calloc(KB, sizeof(char *));
    printf("Enter your IP:");
    getWord(word);
    if (findIpInFile(DNS, word) == 1) {
        fseek(DNS, 0, SEEK_SET);
        while (fgets(buffer, KB - 1, DNS) != NULL) {

            if (strstr(buffer, word) != NULL) {
                strtok(buffer, " ");
                printf("Domain:%s\n", buffer);
                word = strdup(buffer);
            }
        }
    } else
        printf("We don't have this ip in File.\n");
}

int menu(FILE *DNS, cacheT **cache, cacheEntryT **Head, cacheEntryT **Tail) {
    int x;
    printf("------Menu------\n1. Add.\n2. Found IP by domain.\n3. Found all Domains.\n4. Show cache.\n5. Close program.\nEnter your choice:");
    getIndex(&x, 1, 6);
    switch (x) {
        case 1:
            add(DNS, cache, Head, Tail);
            return 1;
        case 2:
            getIpByDomain(DNS, cache, Head, Tail);
            return 2;
        case 3:
            foundAllDomains(DNS);
            return 3;
        case 4:
            showCache(*Head);
            return 4;
        case 5:
            return 0;
        default:
            break;
    }
    return 0;
}

