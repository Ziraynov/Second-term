#include "Header.h"

int main()
{
	setlocale(LC_ALL, "RUS");
	system("chcp 1251 > nul");
	setlocale(LC_ALL, ".utf8");
	const char path[] = { "C:/projects/second term/Lab1/monitors.txt" };
	int key, number = 0;
	monitor* arr = parse_html(&path, &number);
	while (1)
	{
		printf("1. Show\n2. Add\n3. Remove\n4. Sort\n5. Exit\n");
		get_key(&key);
		switch (key)
		{

		case 1:show(arr, number); break;
		case 2:add_word(arr, &number); break;
		case 3:rem(arr, &number); break;
		case 4:sort(arr, number); break;
		case 5:exit(EXIT_SUCCESS);
		}

	}
	return 0;
}

