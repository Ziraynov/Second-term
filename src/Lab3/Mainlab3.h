#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef struct {
    unsigned int size;
    unsigned short reversed1;
    unsigned short reversed2;
    unsigned int offset;
    unsigned int Size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelPerMeter;
    int yPixelPerMeter;
    unsigned int totalColors;
    unsigned int importantColor;
} bmpInfo;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixels;

void check_path(const char *path);

void check(double *x);

void convert_negative(int height, int width, pixels **ptrs);

void convert_black_white(int height, int width, pixels **ptrs);

void gamma_correction(int height, int width, pixels **ptrs);

void menu(int height, int width, pixels **ptrs,const bmpInfo *info);


void get_file_info(const char *path,bmpInfo *info);

void get_pixels(const char *path,bmpInfo *info,unsigned int offset);

void writeBMP(const char *fileName, const bmpInfo *info,pixels **ptrs);







