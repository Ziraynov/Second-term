#include "Main.h"

cacheT *createCache() {
    cacheT *cache = malloc(sizeof(cacheT));
    cache->size = MaxCacheSize;
    cache->table = (cacheEntryT **) calloc(MaxCacheSize, sizeof(cacheEntryT *));
    return cache;
}

unsigned long hashFunction(char *key) {
    unsigned long hash = MaxCacheSize;
    int c;
    while ((c = (int) (*key++)))
        hash = ((hash << 5) + hash) + c;
    return hash % MaxCacheSize;
}

void addToCache(cacheT *table, char *domain, const char *IP) {
    unsigned int hash = hashFunction(domain);
    cacheEntryT *entry = malloc(sizeof(cacheEntryT));
    entry->key = strdup(domain);
    entry->value = strdup(IP);
    int count = 0;
    if (table->table[hash] != NULL) {
        cacheEntryT *current = table->table[hash];
        while (current != NULL) {
            count++;
            if (count >= MaxCacheSize - 1 && current->next != NULL) {
                free(current->next);
                current->next = NULL;
                break;
            }
            current = current->next;
        }
    }
    entry->prev = NULL;
    entry->next = table->table[hash];
    if (table->table[hash] != NULL) {
        table->table[hash]->prev = entry;
    }
    table->table[hash] = entry;
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

int checkInFIle(FILE *DNS, char *word) {
    fseek(DNS, 0, SEEK_SET);
    char *str = (char *) calloc(KB, sizeof(char));
    while (fgets(str, KB - 1, DNS) != NULL) {
        if (strstr(str, word) != NULL)
            return 1;
    }
    return 0;
}

int validDomain(FILE *DNS, char *word) {
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

int fisrtLetter(char *str) {
    if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z'))
        return 1;
    return 0;
}

int checkNumbers(char *str) {
    if (fisrtLetter(str) == 1)
        return 0;
    if (atoi(str) >= 0 && atoi(str) <= 255)
        return 1;
    return 0;
}

int findDotsNumbers(char *IP) {
    int count = 1;
    if (checkNumbers(strtok(IP, ".")) == 0)
        return 0;
    while (checkNumbers(strtok(NULL, ".")) != 0) {
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
    fclose(DNS);
}

void add(FILE *DNS, cacheT *cache) {
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
    if (validIP(DNS, str) == 0)
        printf("This IP is not valid or we already have it.\n");
    else if (validIP(DNS, str) == 1) {
        putInFile(word, IP, DNS, 0);
        addToCache(cache, word, IP);
    } else {
        if (validIP(DNS, str) == 2) {
            putInFile(word, IP, DNS, 1);
            addToCache(cache, word, IP);
        }
    }
}

char *getFromCache(cacheT *cache, char *key) {
    unsigned long hash = hashFunction(key) % cache->size;

    cacheEntryT *entry = cache->table[hash];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            //printf("That's your IP(got by cache): %s\n", entry->value);
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;

}

char *getFromFile(char *word, FILE *DNS, cacheT *cache, int mode) {
    fseek(DNS, 0, SEEK_SET);
    char *str = (char *) calloc(KB, sizeof(char));
    char *str2 = (char *) calloc(KB, sizeof(char));
    do {
        fscanf(DNS, "%s", str);
        for (int i = 0; i <= 2; i++)
            fscanf(DNS, "%s", str2);
    } while (strcmp(str, word) != 0 && feof(DNS) == 0);
    if (strcmp(str, word) == 0 && mode == YES) {
        addToCache(cache, word, str2);
        return str2;
    } else
        return NULL;
}

void fileIP(FILE *DNS, cacheT *cache, char *word) {
    if (getFromFile(word, DNS, cache, YES) != NULL)
        printf("That's your IP: %s\n", getFromFile(word, DNS, cache, NO));
    else
        printf("Not valid IP.\n");
}

void dontCare(cacheT *cache, char *word, FILE *DNS) {
    if (getFromCache(cache, word) == NULL) {
        fileIP(DNS, cache, word);
    } else
        printf("That's your IP(got by cache): %s\n", getFromCache(cache, word));
}

void getIpByDomain(FILE *DNS, cacheT *cache) {
    printf("Enter a domain:");
    char *word = (char *) calloc(KB, sizeof(char *));
    getWord(word);
    printf("You want valid IP or you dont care? Write \"1\" if vaild. \"0\" if dont care.\n");
    int x;
    getIndex(&x, 1, 0);
    if (x == 0)
        dontCare(cache, word, DNS);
    else
        foundAllIPs(DNS, cache, 0, word);
}

void showCache(cacheT *cache) {
    printf("Cache Table:\n");
    for (int i = 0; i < cache->size; i++) {
        cacheEntryT *current = cache->table[i];
        if (current != NULL) {
            while (current != NULL) {
                printf("    %s -> %s\n", current->key, current->value);
                current = current->next;
            }
        }
    }


}

void freeCache(cacheT *cache) {
    for (int i = 0; i < cache->size; i++) {
        cacheEntryT *current = cache->table[i];
        while (current != NULL) {
            cacheEntryT *next = current->next;
            free(current->value);
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(cache->table);
    free(cache);

}

void allIPs(cacheT *cache, char *word, FILE *DNS, char **IP, int mode) {
    do {
        if (getFromCache(cache, word) == NULL) {
            *IP = strdup(getFromFile(word, DNS, cache, YES));
        } else
            *IP = strdup(getFromCache(cache, word));
        if (mode == YES)
            printf("Your IP: %s\n", *IP);
        char *str = strdup(*IP);
        if ((int) strlen(str) != MaxLenghtIP && findDotsNumbers(str) != 1)
            word = strdup(*IP);
    } while ((int) strlen(*IP) != MaxLenghtIP && findDotsNumbers(*IP) != 1);
}

void foundAllIPs(FILE *DNS, cacheT *cache, int mode, char *word) {
    printf("Enter a domain:");
    if (mode == YES)
        getWord(word);
    char *IP = NULL;
    allIPs(cache, word, DNS, &IP, mode);
    if (mode == NO)
        printf("Your IP: %s\n", IP);
}

int menu(FILE *DNS, cacheT *cache) {
    int x;
    printf("------Menu------\n1. Add.\n2. Found IP by domain.\n3. Found all IPs.\n4. Show cache.\n5. Free cache.\n6. Close program.\nEnter your choice:");
    getIndex(&x, 1, 6);
    switch (x) {
        case 1:
            add(DNS, cache);
            return 1;
        case 2:
            getIpByDomain(DNS, cache);
            return 2;
        case 3:
            foundAllIPs(DNS, cache, YES, "1");
            return 3;
        case 4:
            showCache(cache);
            return 4;
        case 5:
            freeCache(cache);
            return 5;
        default:
            break;
    }
    return 0;
}
