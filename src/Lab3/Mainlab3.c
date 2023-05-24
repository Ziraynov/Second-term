#include "Mainlab3.h"

int main() {
    char *path;
    path = (char *) calloc(1001, sizeof(char));
    printf("Input path of your bmp file: ");
    scanf("%s",path);
    //gets_s(path, 100);
    check_path(path);
    printf("\n");
    bmpInfo *info=(bmpInfo*) calloc(1,sizeof(bmpInfo));
    get_file_info(path,info);
    unsigned offset=info->offset;
    get_pixels(path,info,offset);
    free(info);

    return 0;
}
