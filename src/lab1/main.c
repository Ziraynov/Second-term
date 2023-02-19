#include "Header.h"

void get_key(int* key)
{
	while (!scanf_s("%d", key) || *key > 5 || *key <= 0 || getchar() != '\n') 
	{
		rewind(stdin);
		printf("Error,try againg");

	}
}

monitor* parse_html(char* path, int* len) {

    char* doc = file(path);
    string* str = split(doc, "catalog-result__item_data");

    *len = str->len - 1;
    monitor* arr = calloc(*len, sizeof(monitor));

    for (int i = 1; i < str->len; i++) {

        //arr[i - 1].name = split(split(split(str->str[i], "class=\"result__name\">")->str[1], "<")->str[0]);
        arr[i - 1].name = split(split(str->str[i], "data-name=\"")->str[1], "\"")->str[0];

        if (second_word("LG", arr[i - 1].name)) {
            arr[i - 1].producer = LG;
        }
        else if (second_word("Samsung", arr[i - 1].name)) {
            arr[i - 1].producer = Samsung;
        }
        else if (second_word("AOC", arr[i - 1].name)) {
            arr[i - 1].producer = AOC;
        }
        else if (second_word("GigaByte", arr[i - 1].name)) {
           arr[i - 1].producer = GigaByte;
        }
        else if (second_word("Philips", arr[i - 1].name)) {
            arr[i - 1].producer = Philips;
        }
        else if (second_word("BenQ", arr[i - 1].name)) {
            arr[i - 1].producer = BenQ;
        }
        else if (second_word("HP", arr[i - 1].name)) {
            arr[i - 1].producer = HP;
        }
        else if (second_word("Asus", arr[i - 1].name)) {
            arr[i - 1].producer = Asus;
        }
        else {
            arr[i - 1].producer = Huawei;
        }
        arr[i - 1].matrix = split(split(str->str[i], "Type of matrix</td><td class='result__attr_val  cr-result__attr_odd'>")->str[1], "</td>")->str[0];
        arr[i - 1].price = atof(split(split(str->str[i], "data-price=\"")->str[1], "\" data - producer_name")->str[0]);

    }
    return arr;

};
const char* const monitor_producers[] =
{
        [LG] = "LG",
        [Samsung] = "Samsung",
        [GigaByte] = "GigaBite",
        [AOC] = "AOC",
        [Huawei]="Huawei",
        [Philips]="Philips",
        [BenQ]="BenQ",
        [HP]="HP",
        [Asus]="Asus"
};
void show(monitor* array, int len)
{
    for (int i = 0; i < len; i++) {

        printf("%d. %s Price: %.2fBYN. Matrix: %s Producer: %s.\n", i + 1, array[i].name, array[i].price,
            array[i].matrix,
            monitor_producers[array[i].producer]);
    }
}
void sort(monitor* arr, int len) {
    printf("1. Name\n2. Price\n3. Producers\n4. Name and Price\n5. Producer and Matrix\n0. Exit\n");
    int inp;
    while (!scanf("%d", &inp) || inp > 5 || inp < 0 || getchar() != '\n') {
        printf("Wrong input! Enter again:");
        rewind(stdin);
    }
    if (inp == 0) return;
    if (inp == 1) qsort(arr, len, sizeof(monitor), (int (*)(const void*, const void*)) comp_name);
    if (inp == 2) qsort(arr, len, sizeof(monitor), (int (*)(const void*, const void*)) comp_price);
    if (inp == 3) qsort(arr, len, sizeof(monitor), (int (*)(const void*, const void*)) comp_producer);
    if (inp == 4) qsort(arr, len, sizeof(monitor), (int (*)(const void*, const void*)) comp_name_price);
    if (inp == 5) qsort(arr, len, sizeof(monitor), (int (*)(const void*, const void*)) comp_producer_matrix);


}
void add(monitor* arr, int* len) {
    char* it = malloc(0);
    printf("Input item [name/producer/matrix/price]: ");
    rewind(stdin);
    gets(it);


    string* str = split(it, "/");

    if (str->len < 4) {
        printf("Not enough data\n");
        return;
    }
    ++(*len);
    
    arr[*len - 1].name = str->str[0];
    /*if (startswith("Autographed ", str->str[0])) {
        arr[*len - 1]. = autographed;
    }
    else if (startswith("Inscribed ", str->str[0])) {
        arr[*len - 1].quality = inscribed;
    }
    else if (startswith("Corrupted ", str->str[0])) {
        arr[*len - 1].quality = corrupted;
    }
    else {
        arr[*len - 1].quality = unique;
    }*/if (second_word("LG", arr[0].name)) {
        arr[*len - 1].producer = LG;
    }
    else if (second_word("Samsung", arr[0].name)) {
        arr[*len].producer = Samsung;
    }
    else if (second_word("AOC", arr[0].name)) {
        arr[*len-1 ].producer = AOC;
    }
    else if (second_word("GigaByte", arr[0].name)) {
        arr[*len-1].producer = GigaByte;
    }
    else if (second_word("Philips", arr[0].name)) {
        arr[*len - 1].producer = Philips;
    }
    else if (second_word("BenQ", arr[0].name)) {
        arr[*len - 1].producer = BenQ;
    }
    else if (second_word("HP", arr[0].name)) {
        arr[*len - 1].producer = HP;
    }
    else if (second_word("Asus", arr[0].name)) {
        arr[*len].producer = Asus;
    }
    else {
        arr[*len-1].producer = Huawei;
    }
        arr[*len - 1].matrix = str->str[1];
        arr[*len - 1].price = atof(str->str[2]);
    
}
void rem(monitor* arr, int* len) {
    char* name = malloc(0);
    printf("Input name: ");
    rewind(stdin);
    gets(name);

    for (int i = 0; i < *len; i++) {
        if (!strcmp(arr[i].name, name)) {

            for (int j = i; j < *len - 1; j++) {
                arr[j] = arr[j + 1];
            }
            (*len)--;
            break;
        }
    }
}
int main()
{setlocale(LC_ALL,"RUS");
system("chcp 1251 > nul");
    setlocale(LC_ALL, ".utf8");
	const char path = "C:\projects\second term\Lab1\monitors.html";
	int key,len;
    monitor* arr = parse_html("C:/projects/second term/Lab1/monitors.html", &len);
	while (1)
	{
		printf("1. Show\n2. Add\n3. Remove\n4. Sort\n5. Exit\n");
		get_key(&key);
		/*void (*tasks[5]) (monitor*,int*) = { show, add, rem, sort,stop};
		((*tasks[key-1])(array,&len));*/
        if (key == 5) return 1;
        else if (key == 1) show(arr, len);
        else if (key == 2) add(arr, &len);
        else if (key == 3) rem(arr, &len);
        else if (key == 4) sort(arr, len);
		
	}
}