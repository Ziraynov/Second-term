#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct cacheEntry {
    char* key;//это доменное имя
    char* value;//это IP
    struct cacheEntry* next;
    struct cacheEntry* prev;
    time_t last_used;
}cacheEntryT;
typedef struct cache {
    int size;
    cacheEntryT** entries;
} cache_t;