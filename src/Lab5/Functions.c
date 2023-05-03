#include "Main.h"
unsigned long hash_function(char* key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
