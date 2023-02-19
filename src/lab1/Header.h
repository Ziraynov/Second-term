#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//void show(monitor* array, int* len);
//void add(monitor* array, int* len);
//void stop(monitor* array, int* len);
//void rem(monitor* array, int* len);
//void sort(monitor* array, int* len);
typedef enum {
	LG, Samsung,GigaByte,AOC, Huawei, Philips, BenQ, HP,Asus

}producer_of_monitor;
typedef struct {
	char* name;
	char* matrix;
	double price;
	producer_of_monitor producer;
}monitor;
typedef struct {
	int len;
	char** str;
}string;
char* file(char path[]);
int second_word(const char* pre,const char* string);
string* split(char* input, char* delimiter);

int comp_name(monitor* a, monitor* b);

int comp_price(monitor* a, monitor* b);

int comp_producer(monitor* a, monitor* b);

int comp_producer_matrix(const monitor* a, monitor* b);

int comp_name_price(const monitor* a, const monitor* b);

