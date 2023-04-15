
#include "Main.h"

int main() {
    int x = 1;
    while (x == 1) {
        GetMenuIndex(&x);
        if(x==2)
            break;
        TREE *tree = NULL;
        FILE *data = fopen(path, "r");
        char *word = (char *) calloc(KB, sizeof(char));
        char *get_unswer = (char *) calloc(KB, sizeof(char));
        GetWord(word);
        tree = CreateFromData(tree, data);
        diagram(tree);
        TreePrint(tree, &get_unswer);
        fclose(data);
        CheckUnswer(word, tree, data, get_unswer);
        FreeTree(tree);
        free(word);
    }
    return 0;
}