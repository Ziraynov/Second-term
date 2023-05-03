#include "Main.h"

int main() {
    FILE *DNS;
    DNS = checkFile("r+");
    cacheT *cache = createCache();
    int x = menu(DNS, cache);
    while (x != 0) {
        x = menu(DNS, cache);
        DNS = checkFile("r+");
        if (x == 5)
             cache = createCache();
    }
    fclose(DNS);
    return 0;
}