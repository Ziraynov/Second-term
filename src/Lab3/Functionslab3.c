#include "Mainlab3.h"

void check_path(const char *path) {
    FILE *file = NULL;
    if (strstr(path, ".bmp") == 0 || fopen_s(&file, path, "rb") != 1) {
        if (file != NULL) {
            fclose(file);
            printf("Error input. Rerun program!");
            exit(1);
        } else
            exit(1);

    } else
        printf("The file on this path:\"%s\" is recognized, suitable.", path);
}

void check_bmp(unsigned char *bm) {
    if (strstr((char *) bm, "BM") == NULL) {
        printf("FILE ERROR");
        exit(1);
    }
}

void get_file_info(const char *path, bmpInfo *info) {
    FILE *file;
    fopen_s(&file, path, "rb");
    if (file == NULL) {
        printf("FILE ERROR");
        exit(1);
    }
    unsigned char *bm = calloc(2, sizeof(unsigned char));
    fread(bm, sizeof(unsigned short), 1, file);
    check_bmp(bm);
    fread(info, sizeof(bmpInfo), 1, file);
    fclose(file);
}

void get_pixels(const char *path, bmpInfo *info, unsigned int offset) {
    int width = info->width;
    int height = info->height;
    bmpInfo a = *info;
    pixels **ptrs = (pixels **) calloc(height, sizeof(pixels *));
    for (int i = 0; i < height; i++) {
        ptrs[i] = calloc(width, sizeof(pixels));
    }
    FILE *file;
    fopen_s(&file, path, "rb");
    if (file == NULL) {
        printf("FILE ERROR");
        exit(1);
    }
    fseek(file, (long) offset, SEEK_SET);
    int row_padding = (4 - (width % 4)) % 4;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fread(&ptrs[i][j], sizeof(pixels), 1, file);
        }
        if (row_padding != 0)
            fseek(file, row_padding * 24, SEEK_CUR);
    }
    *info = a;
    fclose(file);
    menu(height, width, ptrs, info);
    free(ptrs);
    ptrs=NULL;
}


void convert_negative(int height, int width, pixels **ptrs) {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            ptrs[i][j].b = 255 - ptrs[i][j].b;
            ptrs[i][j].r = 255 - ptrs[i][j].r;
            ptrs[i][j].g = 255 - ptrs[i][j].g;
        }
}

void convert_black_white(int height, int width, pixels **ptrs) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            int b = (int) ptrs[i][j].b;
            int g = (int) ptrs[i][j].g;
            int r = (int) ptrs[i][j].r;
            int sum = (r + b + g) / 3;
            ptrs[i][j].b = (unsigned char) sum;
            ptrs[i][j].g = (unsigned char) sum;
            ptrs[i][j].r = (unsigned char) sum;
        }
    }
}

void gamma_correction(int height, int width, pixels **ptrs) {
    float gamma;
    printf("Input a value of gamma:");
    scanf_s("%f", &gamma);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double r = pow((double) ptrs[i][j].r / 255.0, (double) 1 / (double) gamma) * 255.0;
            double g = pow((double) ptrs[i][j].g / 255.0, (double) 1 / (double) gamma) * 255.0;
            double b = pow((double) ptrs[i][j].b / 255.0, (double) 1 / (double) gamma) * 255.0;
            ptrs[i][j].r = (unsigned char) r;
            ptrs[i][j].g = (unsigned char) g;
            ptrs[i][j].b = (unsigned char) b;
        }
    }
}

void new(int height, int width, FILE *newfile, pixels **ptrs) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fwrite(&ptrs[i][j], sizeof(pixels), 1, newfile);
        }
    }

    int padding = (4 - (width * 3) % 4) % 4;
    for (int j = 0; j < padding; j++) {
        fputc(0x00, newfile);
    }
}

void writeBMP(const char *fileName, const bmpInfo *info, pixels **ptrs) {
    FILE *newfile;
    fopen_s(&newfile, fileName, "wb");
    if (newfile == NULL) {
        printf("Error: Failed to open output file.");
        return;
    }
    int width = info->width;
    int height = info->height;
    unsigned char x = 'B';
    fwrite(&x, sizeof(char), 1, newfile);
    x = 'M';
    fwrite(&x, sizeof(char), 1, newfile);
    fwrite(info, sizeof(bmpInfo), 1, newfile);
    new(height, width, newfile, ptrs);
    fclose(newfile);
}

int check_for_menu(int x) {
    while (scanf_s("%d", &x) != 1) {
        rewind(stdin);
        fprintf(stderr, "ERROR!");
    }
    return x;
}

void ed2(int i, int j, int sev_red, int sev_blue, int sev_green, pixels **ptrs, pixels **pix) {
    for (int k = -1; k < 2; k++)
        for (int p = -1; p < 2; p++) {
            sev_red += ptrs[i + k][j + p].r;
            sev_green += ptrs[i + k][j + p].g;
            sev_blue += ptrs[i + k][j + p].b;
        }
    pix[i - 1][j - 1].r = (unsigned char) sev_red / 9;
    pix[i - 1][j - 1].b = (unsigned char) sev_blue / 9;
    pix[i - 1][j - 1].g = (unsigned char) sev_green / 9;
}

void med(int height, int width, pixels **ptrs, pixels **pix) {

    for (int i = 1; i < height - 1; i++)
        for (int j = 1; j < width - 1; j++) {
            int sev_red = 0;
            int sev_blue = 0;
            int sev_green = 0;
            ed2(i, j, sev_red, sev_blue, sev_green, ptrs, pix);
        }
}

void median_filtration(int height, int width, pixels **ptrs) {
    pixels **pix = (pixels **) calloc(height - 2, sizeof(pixels *));
    for (int i = 0; i < height - 2; i++) {
        pix[i] = calloc(width - 2, sizeof(pixels));
    }
    med(height, width, ptrs, pix);
    for (int i = 1; i < height - 1; i++)
        for (int j = 1; j < width - 1; j++)
            ptrs[i][j] = pix[i - 1][j - 1];

free(pix);
}

void menu(int height, int width, pixels **ptrs,const bmpInfo *info) {
    printf("1)Black and White\n2)Negative\n3)Median Filtration\n4)Gamma-correction\n");
    int key = 0;
    key = check_for_menu(key);
    switch (key) {
        case 1:
            convert_black_white(height, width, ptrs);
            break;
        case 2:
            convert_negative(height, width, ptrs);
            break;
        case 3:
            median_filtration(height, width, ptrs);
            break;
        case 4:
            gamma_correction(height, width, ptrs);
            break;
        default:
            return;
    }
    writeBMP("C:\\Users\\user\\CLionProjects\\Secondterm\\src\\Lab3\\new.bmp", info, ptrs);
    for (int i = 0; i < height; i++) {
        free(ptrs[i]);
    }
    free(ptrs);
}