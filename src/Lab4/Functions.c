#include "Main.h"

void GetMenuIndex(int *x) {
    printf("Enter 1, if you wanna play. Enter 2,if you wanna end.");
    printf("Entre your choice:");
    while (scanf_s("%d", x) != 1 || getchar() != '\n' || ((*x) != 1 && (*x) != 2)) {
        printf("Error,try againg\n");
        rewind(stdin);
    }
    printf("\n");
}

void GetWord(char *word) {
    printf("Input your word:");
    fgets(word, KB - 1, stdin);
    rewind(stdin);
}

void GetQuestion(char *quest) {
    fgets(quest, KB - 1, stdin);
    rewind(stdin);
}

void MakeNewDataBase(char *quest, char *word, TREE *tree, FILE *data, char *get_unswer) {
    if (tree != NULL) {
        int flag = 0;
        if (strcmp(tree->data, get_unswer) == 0 || strcmp(tree->data, get_unswer) == 0) {
            fputs(quest, data);
            flag = 1;
        }
        fputs(tree->data, data);
        if (flag == 1)
            fputs("#\n", data);
        MakeNewDataBase(quest, word, tree->left, data, get_unswer);
        fputs("#\n", data);
        if (flag == 1) {
            fputs(word, data);
            fputs("#\n", data);
            flag = 0;
        }

        MakeNewDataBase(quest, word, tree->right, data, get_unswer);
    }


}

void AddNewElementInDataBase(char *word, TREE *tree, FILE *data, char *get_unswer) {
    printf("So, what differences between my answer and your gues?Enter your question:\n ");
    char *quest = (char *) calloc(KB, sizeof(char));
    GetQuestion(quest);
    data = fopen(path, "w");
    MakeNewDataBase(quest, word, tree, data, get_unswer);
    fputs("#", data);
    fclose(data);

}

void CheckUnswer(char *word, TREE *tree, FILE *data, char *get_unswer) {
    printf("↑↑↑↑↑↑This this the answer↑↑↑↑↑↑\n");
    printf("You guessed: %sThis is a right unswer?\n", word);
    if (GetUnswer() == 0)
        AddNewElementInDataBase(word, tree, data, get_unswer);

}

int GetUnswer() {
    printf("Input your unswer(Y/N)");
    char *str = (char *) calloc(KB, sizeof(char));
    fgets(str, KB - 1, stdin);
    rewind(stdin);
    while ((int) strlen(str) != 2) {
        printf("Error, try againg!");
        fgets(str, KB - 1, stdin);
    }
    if (strstr(str, "Y") != 0 || strstr(str, "y") != 0) {
        return 1;
    } else
        return 0;

}

void TreePrint(TREE *tree, char **get_unswer) {
    if (tree != NULL) {
        printf("%s", tree->data);
        if (tree->left == NULL && tree->right == NULL)
            (*get_unswer) = tree->data;
        if (tree->left != NULL || tree->right != NULL) {
            int flag = GetUnswer();
            if (flag == 0)
                TreePrint(tree->left, get_unswer);
            if (flag == 1)
                TreePrint(tree->right, get_unswer);

        }
    }

}

TREE *CreateFromData(TREE *tree, FILE *data) {
    if (feof(data) == 1) {
        return NULL;
    }

    char *str = (char *) calloc(KB, sizeof(char));
    fgets(str, KB - 1, data);
    if (strstr(str, "#") != 0) {
        return NULL;
    }
    tree = (TREE *) calloc(1, sizeof(TREE));
    tree->data = str;
    tree->left = NULL;
    tree->right = NULL;
    tree->left = CreateFromData(tree->left, data);
    tree->right = CreateFromData(tree->right, data);
    return tree;
}

void FreeTree(TREE *tree) {
    if (tree->right == NULL || tree->left == NULL) {
        free(tree->data);
        free(tree);
        return;
    }

    FreeTree(tree->left);
    FreeTree(tree->right);

    free(tree->data);
    free(tree);
}

void dot(TREE *node, FILE *fp) {

    if (node) {
        if (node->right != NULL) fprintf(fp, "\"%s\"-> \"%s\"\n", node->data, node->right->data);
        dot(node->right, fp);
        if (node->left != NULL) fprintf(fp, "\"%s\"-> \"%s\"\n", node->data, node->left->data);
        dot(node->left, fp);
    }

}

void diagram(TREE *node) {
    FILE *fp = fopen("../src/lab4/tree.dot", "w");
    fputs("digraph G {\n", fp);
    dot(node, fp);
    fputs("}\n", fp);
    fclose(fp);
}